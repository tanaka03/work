//============================
//
// エフェクト設定
// Author:hamada ryuuga
//
//============================

#include "effect.h"
#include "hamada.h"
#include "manager.h"
#include "utility.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CEffect::CEffect(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CEffect::~CEffect()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CEffect::Init()
{
	m_life = 100;

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CEffect::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CEffect::Update()
{

	//動き
	CEffect::move();

	C3dpolygon::Update();

}

//------------------------------------
// 描画
//------------------------------------
void CEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	//Ｚ軸で回転しますちなみにm_rotつかうとグルグル回ります
	//m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);
	C3dpolygon::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CEffect *CEffect::Create(D3DXVECTOR3 Move)
{
	CEffect * pObject = nullptr;
	pObject = new CEffect(PRIORITY_POPEFFECT);

	if (pObject != nullptr)
	{
		float Mode= FloatRandom(10, 1);
		float Speed = FloatRandom(3, 0);
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_NONE);//テクスチャ選択
		pObject->SetSize(D3DXVECTOR3(10.0f, 2.0f*10.0f, 0.0f));//サイズ設定
		//pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//座標設定
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//色設定
		if (Move.y <= 0.0f) 
		{
			Move.y = -Move.y;
		}
		pObject->SetMove(D3DXVECTOR3(Move.x, Move.y, Move.z));//moveの設定
		pObject->SetLife(IntRandom(130, 10));
		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * CEffect::GetPos() const
{
	return &m_pos;
}

void CEffect::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}
//------------------------------------
// 動き系統
//------------------------------------
void CEffect::move()
{
	m_pos += m_move;
	//動き入れたいときはここに	SetMove()で変えれるよ
	m_life--;
	
	if (m_life <= 0)
	{
		Uninit();
	}
	
	
}


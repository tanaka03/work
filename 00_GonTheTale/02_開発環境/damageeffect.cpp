//============================
//
// エフェクト設定
// Author:hamada ryuuga
//
//============================

#include "damageeffect.h"
#include "hamada.h"
#include "manager.h"
#include "utility.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CDamageEffect::CDamageEffect(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CDamageEffect::~CDamageEffect()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CDamageEffect::Init()
{
	m_life = 100;

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CDamageEffect::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CDamageEffect::Update()
{

	//動き
	CDamageEffect::move();

	C3dpolygon::Update();

}

//------------------------------------
// 描画
//------------------------------------
void CDamageEffect::Draw()
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
CDamageEffect *CDamageEffect::Create(D3DXVECTOR3 Move)
{
	CDamageEffect * pObject = nullptr;
	pObject = new CDamageEffect(PRIORITY_POPEFFECT);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_ATTACK);//テクスチャ選択
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));//サイズ設定
		pObject->SetPos(D3DXVECTOR3(0.0f, 150.0f, 0.0f));//座標設定
		pObject->SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));//色設定
		if (Move.y <= 0.0f) 
		{
			Move.y = -Move.y;
		}
		//pObject->SetMove(D3DXVECTOR3(Move.x, Move.y, Move.z));//moveの設定
		//pObject->SetLife(IntRandom(130, 10));
		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		pObject->SetAnimation(5, 1, 5, 0, false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}

	return pObject;
}

//------------------------------------
// 動き系統
//------------------------------------
void CDamageEffect::move()
{
	//m_pos += m_move;
	//動き入れたいときはここに	SetMove()で変えれるよ
	m_life--;
	
	if (m_life <= 0)
	{
		Uninit();
	}
	
	
}


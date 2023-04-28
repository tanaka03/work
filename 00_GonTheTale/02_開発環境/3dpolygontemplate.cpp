//============================
//
//説明設定
// Author:hamada ryuuga
//
//============================

#include "3dpolygontemplate.h"
#include "hamada.h"
#include "manager.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CTest3d::CTest3d(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CTest3d::~CTest3d()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CTest3d::Init()
{

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CTest3d::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CTest3d::Update()
{
	
	//動き
	CTest3d::move();
	
	C3dpolygon::Update();
	
}

//------------------------------------
// 描画
//------------------------------------
void CTest3d::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

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
CTest3d *CTest3d::Create()
{
	CTest3d * pObject = nullptr;
	pObject = new CTest3d(PRIORITY_BG);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_GON);//テクスチャ選択
		pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));//サイズ設定
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 10200.0f));//座標設定
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//色設定
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//moveの設定

		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		pObject->SetAnimation(7, 1, 0, 0, false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * CTest3d::GetPos() const
{
	return &m_pos;
}

void CTest3d::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}



//------------------------------------
// 動き系統
//------------------------------------
void CTest3d::move()
{
	//動き入れたいときはここに	SetMove()で変えれるよ

	m_pos += m_move;
}


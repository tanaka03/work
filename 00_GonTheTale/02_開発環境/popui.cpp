//============================
//
// Ui設定
// Author:hamada ryuuga
//
//============================

#include "popui.h"
#include "hamada.h"
#include "manager.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CPopUi::CPopUi(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CPopUi::~CPopUi()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CPopUi::Init()
{

	C3dpolygon::Init();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	Size(50.0f, 50.0f, 50.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetSize(Size);
	SetTexture(CTexture::TEXTURE_NONE);//テクスチャ選択
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//座標設定
	SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//色設定
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//moveの設定
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CPopUi::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CPopUi::Update()
{

	//動き
	CPopUi::move();

	C3dpolygon::Update();

}

//------------------------------------
// 描画
//------------------------------------
void CPopUi::Draw()
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
CPopUi *CPopUi::Create()
{
	CPopUi * pObject = nullptr;
	pObject = new CPopUi(PRIORITY_OBJECT);

	if (pObject != nullptr)
	{
		pObject->Init();
	

		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * CPopUi::GetPos() const
{
	return &m_pos;
}

void CPopUi::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}



//------------------------------------
// 動き系統
//------------------------------------
void CPopUi::move()
{
	//動き入れたいときはここに	SetMove()で変えれるよ

	m_pos += m_move;
}
//============================
//
//攻撃範囲設定
// Author:hamada ryuuga
//
//============================

#include "arealine.h"
#include "hamada.h"
#include "manager.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CArealine::CArealine(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CArealine::~CArealine()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CArealine::Init()
{

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CArealine::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CArealine::Update()
{

	//動き
	CArealine::move();

	C3dpolygon::Update();

}

//------------------------------------
// 描画
//------------------------------------
void CArealine::Draw()
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
CArealine *CArealine::Create()
{
	CArealine * pObject = nullptr;
	pObject = new CArealine(PRIORITY_BG);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_NONE);//テクスチャ選択
		pObject->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//サイズ設定
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//座標設定
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//色設定
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//moveの設定

		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * CArealine::GetPos() const
{
	return &m_pos;
}

void CArealine::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}
//------------------------------------
//座標の差分を取るやつ 
//------------------------------------
void CArealine::SetDifferenceMove(D3DXVECTOR3 move)
{
	m_move = move-m_pos;
}

//------------------------------------
//サイズの差分を取るやつ 
//------------------------------------
void CArealine::SetSizeMove(D3DXVECTOR3 move)
{
	m_SizeMove = move-m_size;
}

//------------------------------------
// 動き系統
//------------------------------------
void CArealine::move()
{
	m_SizeMove.x += (0.0f - m_SizeMove.x) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_SizeMove.y += (0.0f - m_SizeMove.y) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_SizeMove.z += (0.0f - m_SizeMove.z) * Decrease;	//（目的の値-現在の値）＊減衰係数

	m_size += m_SizeMove;
	SetSize(m_size);
	//動き入れたいときはここに	SetMove()で変えれるよ
	m_move.x += (0.0f - m_move.x) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_move.y += (0.0f - m_move.y) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_pos += m_move;
}


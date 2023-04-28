//============================
//
// 何もない３Dのobject設定
// Author:hamada ryuuga
//
//============================

#include "3dpolygonbase.h"
#include "hamada.h"
#include "manager.h"


//------------------------------------
// コンストラクタ
//------------------------------------
C3dbase::C3dbase(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
C3dbase::~C3dbase()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT C3dbase::Init()
{

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void C3dbase::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void C3dbase::Update()
{

	//動き
	C3dbase::move();

	C3dpolygon::Update();

}

//------------------------------------
// 描画
//------------------------------------
void C3dbase::Draw()
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
C3dbase *C3dbase::Create()
{
	C3dbase * pObject = nullptr;
	pObject = new C3dbase(PRIORITY_BG);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_NONE);//テクスチャ選択
		pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));//サイズ設定
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//座標設定
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//色設定
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//moveの設定

		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * C3dbase::GetPos() const
{
	return &m_pos;
}

void C3dbase::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}


//------------------------------------
//サイズの差分を取るやつ 
//------------------------------------
void C3dbase::SetSizeMove(D3DXVECTOR3 move)
{
	m_SizeMove = move - m_size;
}

//------------------------------------
// 動き系統
//------------------------------------
void C3dbase::move()
{
	m_SizeMove.x += (0.0f - m_SizeMove.x) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_SizeMove.y += (0.0f - m_SizeMove.y) * Decrease;	//（目的の値-現在の値）＊減衰係数
	m_SizeMove.z += (0.0f - m_SizeMove.z) * Decrease;	//（目的の値-現在の値）＊減衰係数

	m_size += m_SizeMove;

	SetSize(m_size);
	//動き入れたいときはここに	SetMove()で変えれるよ

	m_pos += m_move;
}


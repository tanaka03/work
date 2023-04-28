//============================
//
// もじ設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "words.h"

#include "manager.h"
#
#include "object.h"
#include "font.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CWords::CWords(int list) :CObject(3)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CWords::~CWords()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CWords::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//頂点情報へのポインタ

						//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//- 
	// 頂点情報の設定
	//-
	//頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);


	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	

	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CWords::Uninit(void)
{
	//if (m_pTex != nullptr)
	//{
	//	m_pTex->Release();
	//	m_pTex = nullptr;
	//}

	// 破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();

}

//------------------------------------
// 更新
//------------------------------------
void CWords::Update(void)
{
	m_rot.z += m_moveRot.z;

	VERTEX_2D *pVtx; //頂点へのポインタ

					 //頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// 計算用マトリックス

					//マトリックス作成
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_rot.z);
	//頂点座標
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);

		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_size.x);//<-サイズ変更
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_size.y);//<-サイズ変更
		pVtx[i].pos.z = 0.0f;
	}

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();


	//ここにmoveをいれる
	m_pos += m_move;
}

//------------------------------------
// 描画
//------------------------------------
void CWords::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;        //デバイスへのポインタ

									  //デバイスの取得
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();


	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, m_pTex);

	//ポリゴンの描画

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,
		2);
	//プリミティブ(ポリゴン)数
	pDevice->SetTexture(0, NULL);

}

//------------------------------------
// create
//------------------------------------
CWords *CWords::Create(const char*Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type)
{
	CWords * pObject = nullptr;
	pObject = new CWords;

	if (pObject != nullptr)
	{
	
		pObject->SetPos(pos);
		pObject->SetSize(Size);
		pObject->Init();
		pObject->Setwords(Text, Type);

	}
	return pObject;
}

//=============================================================================
// GetPos関数
//=============================================================================
void CWords::Setwords(const char*Text, CFont::FONT Type)
{
	std::string Txt = Text;
	if (Txt != "")
	{
		m_pTex = CManager::GetInstance()->GetFont()->GetFont(Text, Type);
	}
	else
	{
		m_pTex = nullptr;
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}


//=============================================================================
// GetPos関数
//=============================================================================
const D3DXVECTOR3 * CWords::GetPos() const
{
	return &m_pos;
}

//=============================================================================
// SetPos関数
//=============================================================================
void CWords::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}
//=============================================================================
// SetPos関数
//=============================================================================
void CWords::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//===========================================================================
//セットカラー
//=============================================================================
void CWords::SetColar(D3DXCOLOR Collar)
{
	VERTEX_2D *pVtx; //頂点へのポインタ

					 //頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[1].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[2].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[3].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);

	m_col = Collar;
	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}
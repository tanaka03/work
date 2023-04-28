//=============================================================================
//
// Object
// Author : 浜田琉雅
//
//=============================================================================

#include "object.h"
#include "3dpolygon.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "hamada.h"

int C3dpolygon::m_MaxPolygon;
const D3DXVECTOR3 C3dpolygon::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, +1.0f, +1.0f),
	D3DXVECTOR3(+1.0f, +1.0f, +1.0f),
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(+1.0f, -1.0f, -1.0f),
};

//=============================================================================
// コンストラクト関数
//=============================================================================
C3dpolygon::C3dpolygon(int list):CObject(list)
{
	
}

//=============================================================================
// デストラクト関数
//=============================================================================
C3dpolygon::~C3dpolygon()
{
}

//=============================================================================
// ポリゴンの初期化
//=============================================================================
HRESULT C3dpolygon::Init()
{
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_nScale = 10.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTimer = 0;
	
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

	m_texture = CTexture::TEXTURE_NONE;

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//確保するバッファのサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_3D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//rhwの設定
	pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	m_CounterAnim = 0;
	m_PatternAnimX = 1;
	m_PatternAnimY = 1;

	m_DivisionX = 1;
	m_DivisionY = 1;
	m_DivisionMAX = m_DivisionX*m_DivisionY;

	m_animationSpeed = 0;
	m_AnimationSpeedCount = 0;

	m_Timar = 0;
	m_TimaCount = 0;
	m_OnAnimation = false;
	SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSize(m_size);
	return S_OK;
}

//=============================================================================
// ポリゴンの終了
//=============================================================================
void C3dpolygon::Uninit()
{
	// 破棄
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}

//=============================================================================
// ポリゴンの更新
//=============================================================================
void C3dpolygon::Update()
{
	m_nTimer++;


	m_MaxPolygon++;
	//m_pos.z = -0.01f*m_MaxPolygon;

	if (m_OnAnimation)
	{
		m_TimaCount++;

		if (m_TimaCount >= m_Timar)
		{
			m_AnimationSpeedCount++;
			if (m_AnimationSpeedCount >= m_animationSpeed)
			{
				m_AnimationSpeedCount = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{//アニメーション
					m_PatternAnimX = 0;
					m_PatternAnimY++;
					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;
						if (!m_Loop)
						{
							Uninit();
						}
						return;
					}
				}

				float U = 1.0f / (m_DivisionX);
				float V = 1.0f / (m_DivisionY);

				SetTex(PositionVec4(
					U * (m_PatternAnimX)
					, U *(m_PatternAnimX)+U
					, V * (m_PatternAnimY)
					, V * (m_PatternAnimY)+V));
				SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		else
		{
			SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}

//=============================================================================
// ポリゴンの描画
//=============================================================================
void C3dpolygon::Draw()
{
	
	//デバイスへのポインタ
	//デバイスの取得
 	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;													// 計算用マトリックス
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	
	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetTexture(m_texture));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,
		2);						//プリミティブ(ポリゴン)数

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}




//=============================================================================
// create関数
//=============================================================================
C3dpolygon *C3dpolygon::Create(int list)
{
	C3dpolygon * pObject = nullptr;
	pObject = new C3dpolygon(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//=============================================================================
// GetPos関数
//=============================================================================
const D3DXVECTOR3 *C3dpolygon::GetPos() const
{
	return &m_pos;
}

//=============================================================================
// SetPos関数
//=============================================================================
void C3dpolygon::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z= pos.z;
}

//--------------------------------------------------
// テクスチャの設定
//--------------------------------------------------
void C3dpolygon::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//---------------------------------------
//セットテクスチャ(2d)
//---------------------------------------
void C3dpolygon::SetTex(PositionVec4 Tex)
{
	VERTEX_3D *pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャの座標設定
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();
}

//---------------------------------------
//セットサイズ
//---------------------------------------
void  C3dpolygon::SetSize(const D3DXVECTOR3 &size)
{
	m_size = size;

	VERTEX_3D*pVtx;		//頂点情報へのポインタ

	//頂点バッファをロックし、頂点情報へのポインタを取得

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// 頂点情報の設定
	//------------------------
	//頂点座標
	for (int i = 0; i < 4; ++i)
	{
		pVtx[i].pos.x = m_Vtx[i].x * m_size.x; // TODO: これなおす。
		pVtx[i].pos.y = m_Vtx[i].y * m_size.y; // TODO: これなおす。
		pVtx[i].pos.z = m_Vtx[i].z * m_size.z;
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

}
//---------------------------------------
//頂点Colarの設定
//---------------------------------------
void C3dpolygon::SetColar(D3DXCOLOR Colar)
{
	VERTEX_3D *pVtx; //頂点へのポインタ

	//頂点バッファをロックし頂点情報へのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_Colar = Colar;
	//テクスチャの座標設定
	//頂点カラーの設定								  
	pVtx[0].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[1].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[2].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[3].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);

	//頂点バッファをアンロック
	m_pVtxBuff->Unlock();

}

//---------------------------------------
//Vtxの取得
//---------------------------------------
LPDIRECT3DVERTEXBUFFER9 &C3dpolygon::GetVtx()
{
	return m_pVtxBuff;
}

//=============================================================================
// Animationの枚数設定関数
//=============================================================================
void C3dpolygon::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 0;
	m_PatternAnimY = 0;
	m_animationSpeed = Speed;
	m_Timar = Drawtimer;
	m_OnAnimation = true;
	m_Loop = loop;
	//表示座標を更新
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}

//============================
//
// ライン設定
// Author:hamada ryuuga
//
//============================
#include "line.h"
#include "camera.h"
#include "manager.h"


CLine::CLine(int nPriority) : CObject(nPriority)
{

}
CLine::~CLine()
{

}

//=========================================
// 初期化処理
//=========================================
HRESULT CLine::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;
	//カメラのデータ取得

	// 頂点座標をロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 初期化処理
	m_Line.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 頂点座標
	m_Line.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 回転座標

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 頂点座標をアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================
// 終了処理
//=========================================
void  CLine::Uninit(void)
{
	// 頂点バッファーの解放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}

//=========================================
// 更新処理
//=========================================
void  CLine::Update(void)
{
}

//=========================================
// 描画処理
//=========================================
void  CLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	DWORD Test = 0;

	pDevice->GetRenderState(D3DRS_ALPHAFUNC, &Test);//より大きい

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//ライト設定falseにするとライトと食らわない
	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(&m_Line.mtxWorld);

	//ビルボードの設定
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, m_Line.pos.x, m_Line.pos.y, m_Line.pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(&m_Line.mtxWorld, &m_Line.mtxWorld, &mtxTrans);

	//ライト設定falseにするとライトと食らわない
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ワールド座標行列の設定
	pDevice->SetTransform(D3DTS_WORLD, &m_Line.mtxWorld);

	// 頂点バッファをデバイスのデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//ライト設定falseにするとライトと食らわない
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	Uninit();
}

//----------------------------------
//セット
//----------------------------------
void  CLine::SetLine(D3DXVECTOR3 Maxpos,D3DXVECTOR3 pos)//場所.回転.色.タイプ
{
	// 頂点座標をロック
	VERTEX_3D*pVtx; //頂点へのポインタ
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = pos;
	pVtx[1].pos = Maxpos;
	pVtx[2].pos = D3DXVECTOR3(pos.x, 100.0f, pos.z); 
	pVtx[3].pos = D3DXVECTOR3(Maxpos.x, 100.0f, Maxpos.z);

	// 頂点座標をアンロック
	m_pVtxBuff->Unlock();
}

//----------------------------------
//セット
//----------------------------------
CLine * CLine::Create()
{
	CLine * pObject = nullptr;
	pObject = new CLine;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}




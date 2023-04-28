//============================
//
// ライン設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"
#include "object.h"


#define	MAX_LINE	(4096)
#define	MAX_RECIPE	(5)
#define MAX_TEX (2)
#define BallSpede (1)

//------------------------------------
// ポリゴンの構造体を定義
//------------------------------------

class CLine : public CObject
{
public:
	const int MAXTRAJECTORY = 100;
	CLine(int nPriority = PRIORITY_OBJECT);
	~CLine() override;

	HRESULT Init()override;//初期化
	void Uninit()override;//破棄
	void Update()override;//更新
	void Draw()override;//描画

	void SetLine(D3DXVECTOR3 Maxpos, D3DXVECTOR3 pos);//場所.回転.色.タイプ

	static CLine* Create();
	typedef struct
	{
		D3DXVECTOR3 pos;	// 頂点座標
		D3DXVECTOR3 rot;	// 回転座標
		D3DXMATRIX mtxWorld;// ワールドマトリックス
	} LINE;

private:
	LINE m_Line;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// 頂点バッファーへのポインタ
	static D3DXVECTOR3 s_RotMove;
};


#endif


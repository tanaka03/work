//=============================================================================
//
// TUTORIAL画面のヘッダー
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _TUTORIAL_H_		//このマクロが定義されてなかったら
#define _TUTORIAL_H_		//2重インクルード防止のマクロ定義

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object.h"

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CObject2d;

//-----------------------------------------------------------------------------
// チュートリアルクラス
//-----------------------------------------------------------------------------
class CTutorial :public CObject
{
	const int MAXTASK = 1;
public:
	CTutorial();
	~CTutorial();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CObject2d *m_object2d[4];
	//CScore*pScore;

	D3DXVECTOR3 m_posOld;
	int m_NextTaskCount;//次のタスクまでのカウント


	int m_nInterval;
	int m_nEnableTime;
	bool m_bFire;


};

#endif

//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#ifndef _TITLE_H_
#define _TITLE_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include"main.h"
#include "object2d.h"
#include "manager.h"

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class C3dpolygon;
class CPlayer;


//-----------------------------------------------------------------------------
// タイトル
//-----------------------------------------------------------------------------
class CTitle :public CObject
{
	//画面(モード)の種類
	enum MODE
	{
		MODE_GAME = 0,			//ゲーム画面	
		MODE_TUTORIAL,
		MODE_RANKING,		//ランキング画面
		MODE_END,
		MODE_MAX
	};

public:
	CTitle();
	~CTitle();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	C3dpolygon *m_3dpolygon[4];
	CObject2d *m_object2d[4];
	CObject2d *m_list[2];
	CObject2d *m_Level2d;
	CObject2d *fade;

	int m_addX;
	int m_addY;
	CManager::LEVEL m_Level;

	MODE NextMode;
	bool Sizcontroller;
	bool ModeSelect;
	float m_alpha;
	float m_Rot;
	int m_ParticleCount;
	
};

#endif
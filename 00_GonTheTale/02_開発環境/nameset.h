//**************************************************
//
// êßçÏ ( ñºÇ‹Ç¶ )
// Author : hamada ryuuga
//
//**************************************************

#ifndef _NAMESET_H_
#define _NAMESET_H_

#include"main.h"
#include "object2d.h"
#include "name.h"

class CNameSet :public CObject
{
public:
	CNameSet();
	~CNameSet();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:

	void RankingNeme();

	CObject2d *m_object2d[2];

	static std::string m_PlayName;

	CName*m_ListName[3];
	CName*m_PlayNameSet[10];

	D3DXVECTOR3 Collar;
	D3DXVECTOR3 m_NemePos;

	int m_NowPlay;
	bool ON;
};

#endif
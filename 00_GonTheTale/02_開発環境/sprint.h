//=============================================================================
//
// dashitem
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _SPRINT_H_
#define	_SPRINT_H_

#include"building.h"

//**************************************************
// ƒNƒ‰ƒX
//**************************************************
class CSprint : public CBuilding
{
public:
	CSprint();
	~CSprint() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CSprint *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Move();
	void quat() {}
	void Hit() override;
	void NotHit() override;
private:
	bool m_hit;
	bool m_isMove;
};

#endif // !_PENBULUM_H_


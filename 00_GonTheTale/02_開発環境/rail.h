//==================================================
// pendulum.h
// Author: tutida ryousei
//==================================================
#ifndef _RAIL_H_
#define	_RAIL_H_

#include"building.h"

//**************************************************
// ƒNƒ‰ƒX
//**************************************************
class CRail : public CBuilding
{
public:
	CRail();
	~CRail() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CRail *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Move();
	void quat() {}
	void Hit() override;
	void NotHit() override;
private:
	bool m_hit;
	bool m_isMove;
};

#endif // !_PENBULUM_H_


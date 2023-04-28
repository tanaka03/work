//=============================================================================
//
// dashitem
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _DASHITEM_H_
#define	_DASHITEM_H_

#include"building.h"

//**************************************************
// ƒNƒ‰ƒX
//**************************************************
class CDashitem : public CBuilding
{
public:
	CDashitem();
	~CDashitem() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CDashitem *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Move();
	void quat() {}
	void Hit() override;
	void NotHit() override;
private:
	float m_scale;
	bool m_isScale;
	bool m_hit;
	bool m_isMove;
};

#endif // !_PENBULUM_H_

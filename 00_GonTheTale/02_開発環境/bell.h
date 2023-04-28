//=============================================================================
//
// 得点アイテム
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _BELL_H_
#define	_BELL_H_

#include"building.h"

//**************************************************
// クラス
//**************************************************
class CBell : public CBuilding
{
public:
	CBell();
	~CBell() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CBell *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void Move();
	void quat() {}
	void Hit() override;
	void NotHit() override;
private:
	bool m_hit;
	bool m_isMove;
	CShadow *Shadow;
};

#endif // !_PENBULUM_H_


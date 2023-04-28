//==================================================
// wood.h
// Author: tutida ryousei
//==================================================
#ifndef _WOOD_H_
#define _WOOD_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include"ObjectX.h"

//**************************************************
// �N���X
//**************************************************
class CWood : public CObjectX
{
public:
	CWood();
	~CWood() override;

	HRESULT Init() override;
	void Update() override;

	static CWood *Create(D3DXVECTOR3 pos, float rot, float movespeed, float rotspeed);

	void SetPos(const D3DXVECTOR3 &pos) { m_Pos = pos; }
	void SetSpawnRot(const float &spawnrot) { m_fSpawnRot = spawnrot; }
	void SetMoveSpeed(float movespeed) { m_fMoveSpeed = movespeed; }
	void SetRotSpeed(float rotspeed) { m_fRotSpeed = rotspeed; }
	void quat() {}
	//void Hit() override;
private:

	D3DXVECTOR3 m_Pos;		// �ʒu
	D3DXVECTOR3 m_Rot;		// �p�x
	float m_fSpawnRot;		// �����p�x
	float m_fMoveSpeed;		// �ړ����x
	float m_fRotSpeed;		// ��]���x
	int m_life;
};

#endif // !_WOOD_H_

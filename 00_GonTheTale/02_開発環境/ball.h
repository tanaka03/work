//==================================================
// ball.h
// Author: tutida ryousei
//==================================================
#ifndef _BALL_H_
#define	_BALL_H_

#include"building.h"


class CBuilding;

//**************************************************
// �N���X
//**************************************************
class CBall : public CBuilding
{
public:
	CBall();
	~CBall();
	
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Hit() override {}
	void NotHit() override {};
	static CBall *Create(D3DXVECTOR3 pos, float radius, float rotspeed, int rotType);
	void Move();

	void SetCenterPos(D3DXVECTOR3 centerpos) { m_centerPos = centerpos; }
	void SetRadius(float radius) { m_fRadius = radius; }
	void SetRotSpeed(float rotspeed) { m_fRotSpeed = rotspeed; }
	void SetRotType(int type) { m_nRotType = type; }


	D3DXVECTOR3 GetCenterPos() { return m_centerPos; }
	float GetRadius() { return m_fRadius; }
	float GetRotSpeed() { return m_fRotSpeed; }
	int GetRotType() { return m_nRotType; }
	void quat();

private:
	D3DXVECTOR3 m_centerPos;	// ���S�̈ʒu
	D3DXVECTOR3 m_Pos;			// �I�u�W�F�N�g�̈ʒu
	D3DXVECTOR3 m_Rot;			// �p�x
	D3DXMATRIX m_mtxRot;
	D3DXQUATERNION m_quat;
	D3DXVECTOR3 m_vecAxis;
	float m_fValueRot;
	float m_fRotSpeed;			// ��]���x
	float m_fMoveSpeed;			// �ړ����x
	float m_fRadius;			// ���a
	int m_nRotType;				// �E��肩����肩

};

#endif // !_BALL_H_

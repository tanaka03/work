//==================================================
// pendulum.h
// Author: tutida ryousei
//==================================================
#ifndef _PENBULUM_H_
#define	_PENBULUM_H_

#include"building.h"

//**************************************************
// �N���X
//**************************************************
class CPendulum : public CBuilding
{
public:
	CPendulum();
	~CPendulum() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Hit() override {};
	void NotHit() override {};
	static CPendulum *Create(D3DXVECTOR3 pos, D3DXVECTOR3 destrot, float coefficient, int type);
	void Move();

	void SetDestRot(D3DXVECTOR3 destrot) { m_DestRot = destrot; }
	void SetCoefficient(float coefficient) { m_fCoefficient = coefficient; }
	void SetType(int type) { m_nType = type; }
	
	D3DXVECTOR3 GetDestRot() { return m_DestRot; }
	float GetCoefficient() { return m_fCoefficient; }
	int GetType() { return m_nType; }
	void GetRotNon() { m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f); }
	void quat() {}

private:
	int m_nType;			// ���
	float m_fCoefficient;	// �����A�����W��
	D3DXVECTOR3 m_Rot;		// �p�x
	D3DXVECTOR3 m_DestRot;	// �ړI�̊p�x(�U�蕝)
};

#endif // !_PENBULUM_H_

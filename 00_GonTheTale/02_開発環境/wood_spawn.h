//==================================================
// wood_spawn.h
// Author: tutida ryousei
//==================================================
#ifndef _WOOD_SPAWN_H_
#define	_WOOD_SPAWN_H_

#include"renderer.h"
#include"building.h"


class CBuilding;
//**************************************************
// �N���X
//**************************************************
class CWood_Spawn : public CBuilding
{
public:
	CWood_Spawn();
	~CWood_Spawn() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Hit()  override {};
	void NotHit() override {};
	static CWood_Spawn *Create(D3DXVECTOR3 pos, float rot, float movespeed, float rotspeed, int cooltime);

	void SetPos(D3DXVECTOR3 pos) { m_Pos = pos; }
	void SetRot(float rot) { m_fRot = rot; }
	void SetMoveSpeed(float movespeed) { m_fMoveSpeed = movespeed; }
	void SetRotSpeed(float rotspeed) { m_fRotSpeed = rotspeed; }
	void SetCoolTime(int cooltime) { m_nCoolTime = cooltime; }

	D3DXVECTOR3 GetSpawnPos() {return m_Pos; }
	float GetRot() { return m_fRot; }
	float GetMoveSpeed() { return m_fMoveSpeed; }
	float GetRotSpeed() { return m_fRotSpeed; }
	int GetCoolTime() { return m_nCoolTime; }
	void quat() {}

private:
	D3DXVECTOR3 m_Pos;		// �ʒu
	float m_fRot;			// �p�x
	int m_nCoolTime;		// �X�|�[������Ԋu
	float m_fMoveSpeed;		// �ړ����x
	float m_fRotSpeed;		// ��]���x
	int m_nCount;
};

#endif // !_WOOD_SPAWN_H_

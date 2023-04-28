//==================================================
// wood.h
// Author: tutida ryousei
//==================================================
#ifndef _WOOD_H_
#define _WOOD_H_

//**************************************************
// インクルード
//**************************************************
#include"ObjectX.h"

//**************************************************
// クラス
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

	D3DXVECTOR3 m_Pos;		// 位置
	D3DXVECTOR3 m_Rot;		// 角度
	float m_fSpawnRot;		// 生成角度
	float m_fMoveSpeed;		// 移動速度
	float m_fRotSpeed;		// 回転速度
	int m_life;
};

#endif // !_WOOD_H_

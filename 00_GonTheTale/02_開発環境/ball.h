//==================================================
// ball.h
// Author: tutida ryousei
//==================================================
#ifndef _BALL_H_
#define	_BALL_H_

#include"building.h"


class CBuilding;

//**************************************************
// クラス
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
	D3DXVECTOR3 m_centerPos;	// 中心の位置
	D3DXVECTOR3 m_Pos;			// オブジェクトの位置
	D3DXVECTOR3 m_Rot;			// 角度
	D3DXMATRIX m_mtxRot;
	D3DXQUATERNION m_quat;
	D3DXVECTOR3 m_vecAxis;
	float m_fValueRot;
	float m_fRotSpeed;			// 回転速度
	float m_fMoveSpeed;			// 移動速度
	float m_fRadius;			// 半径
	int m_nRotType;				// 右回りか左回りか

};

#endif // !_BALL_H_

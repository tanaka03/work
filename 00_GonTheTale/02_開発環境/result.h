//============================
//
// ���U���g��ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//============================
#ifndef _RESULT_H_		//���̃}�N������`����ĂȂ�������
#define _RESULT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

#include "main.h"
#include "object.h"
#include "object2d.h"

class CResult :public CObject
{
public:
	CResult();
	~CResult();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;	
private:
	CObject2d *m_object2d[4];
	int m_addX;
	int m_addY;
	float m_Rot;
	float m_Colar;
	float m_Pos;
	bool Sizcontroller;
	bool m_On;

};

#endif
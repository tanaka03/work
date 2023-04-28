//==================================================
// wood.cpp
// Author: tutida ryousei
//==================================================
#include"wood.h"

#include "manager.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CWood::CWood()
{
	m_Pos = { 0.0f,0.0f,0.0f };
	m_Rot = { 0.0f,0.0f,0.0f };
	m_life = 100;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CWood::~CWood()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CWood::Init()
{


	// ���f���̐ݒ�
	const char* Model = "data/MODEL/wood.x";
	SetModel(Model);

	// �������̊p�x
	m_Rot.y += m_fSpawnRot;

	return S_OK;
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CWood::Update()
{
	if (m_Pos.y > 0.0f)
	{
		m_Pos.y -= 3.0f;
	}
	else
	{
		// �ړ�
		m_Pos.x -= sinf(m_fSpawnRot) * m_fMoveSpeed;
		m_Pos.z -= cosf(m_fSpawnRot) * m_fMoveSpeed;

		// ��]
		m_Rot.x -= m_fRotSpeed;
	}
	m_life--;
	if (m_life < 0)
	{
		CObjectX::Uninit();
	}

	CObjectX::SetPos(m_Pos);
	CObjectX::SetRot(m_Rot);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CWood *CWood::Create(D3DXVECTOR3 pos, float spawnrot, float movespeed, float rotspeed)
{
	CWood *pWood = nullptr;

	pWood = new CWood;

	if (pWood != nullptr)
	{
		pWood->SetPos(pos);
		pWood->SetSpawnRot(spawnrot);
		pWood->SetMoveSpeed(movespeed);
		pWood->SetRotSpeed(rotspeed);
		pWood->Init();
	}

	return pWood;
}
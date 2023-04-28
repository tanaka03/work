//==================================================
// ball.cpp
// Author: tutida ryousei
//==================================================
#include"pendulum.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CPendulum::CPendulum()
{
	m_Rot = { 0.0f,0.0f,0.0f };
	m_DestRot = { 0.0f,0.0f,0.0f };
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPendulum::~CPendulum()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CPendulum::Init()
{
	CBuilding::Init();

	// ���f���̐ݒ�
	if (m_nType == 0)
	{
		const char* Model = "data/MODEL/pendulum.x";
		SetModel(Model);
	}
	else
	{
		const char* Model = "data/MODEL/pendulum2.x";
		SetModel(Model);
	}

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPendulum::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPendulum::Update()
{
	CObjectX::Update();

	// ����
	Move();

	// �p�x�̐ݒ�
	SetRot(m_Rot);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CPendulum::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CPendulum *CPendulum::Create(D3DXVECTOR3 pos, D3DXVECTOR3 destrot, float coefficient, int type)
{
	CPendulum *pPendulum = nullptr;

	pPendulum = new CPendulum;

	if (pPendulum != nullptr)
	{
		pPendulum->SetPos(pos);
		pPendulum->SetDestRot(destrot);
		pPendulum->SetCoefficient(coefficient);
		pPendulum->SetType(type);
		pPendulum->SetFileName("Pendulum");
		pPendulum->Init();
	}

	return pPendulum;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CPendulum::Move()
{
	// X���W
	if (m_Rot.x < m_DestRot.x) {
		if (m_Rot.x < 0)
		{
			// ����
			m_Rot.x += (m_DestRot.x + m_Rot.x) * m_fCoefficient;
		}
		else
		{
			// ����
			m_Rot.x += (m_DestRot.x - m_Rot.x) * m_fCoefficient;
		}

		if (m_Rot.x >= m_DestRot.x * 0.95f)
		{
			// �ړI�̊p�x�̔��]
			m_DestRot.x *= -1.0f;
		}
	}
	else {
		if (m_Rot.x > 0)
		{
			// ����
			m_Rot.x += (m_DestRot.x + m_Rot.x) * m_fCoefficient;
		}
		else
		{
			// ����
			m_Rot.x += (m_DestRot.x - m_Rot.x) * m_fCoefficient;
		}

		if (m_Rot.x <= m_DestRot.x * 0.95f)
		{
			// �ړI�̊p�x�̔��]
			m_DestRot.x *= -1.0f;
		}
	}

	// Z���W
	if (m_Rot.z < m_DestRot.z) {
		if (m_Rot.z < 0)
		{
			// ����
			m_Rot.z += (m_DestRot.z + m_Rot.z) * m_fCoefficient;
		}
		else
		{
			// ����
			m_Rot.z += (m_DestRot.z - m_Rot.z) * m_fCoefficient;
		}

		if (m_Rot.z >= m_DestRot.z * 0.95f)
		{
			// �ړI�̊p�x�̔��]
			m_DestRot.z *= -1.0f;
		}
	}
	else {
		if (m_Rot.z > 0)
		{
			// ����
			m_Rot.z += (m_DestRot.z + m_Rot.z) * m_fCoefficient;
		}
		else
		{
			// ����
			m_Rot.z += (m_DestRot.z - m_Rot.z) * m_fCoefficient;
		}

		if (m_Rot.z <= m_DestRot.z * 0.95f)
		{
			// �ړI�̊p�x�̔��]
			m_DestRot.z *= -1.0f;
		}
	}
	 
	// Y���W
	m_Rot.y += m_DestRot.y;
}
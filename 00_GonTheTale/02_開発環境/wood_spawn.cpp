//==================================================
// wood_spawn.cpp
// Author: tutida ryousei
//==================================================
#include"wood_spawn.h"
#include"wood.h"
#include"manager.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CWood_Spawn::CWood_Spawn()
{
	m_Pos = { 0.0f,0.0f,0.0f };
	m_nCoolTime = 0;
	m_nCount = 0;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CWood_Spawn::~CWood_Spawn()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CWood_Spawn::Init()
{
	CBuilding::Init();
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CWood_Spawn::Uninit()
{
	//CObjectX::Uninit();
	Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CWood_Spawn::Update()
{
	m_nCount++;

	if (m_nCount % m_nCoolTime == 0)
	{	
		// �I�u�W�F�N�g�̐���
		CWood::Create(m_Pos, m_fRot, m_fMoveSpeed, m_fRotSpeed);
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CWood_Spawn::Draw()
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CWood_Spawn *CWood_Spawn::Create(D3DXVECTOR3 pos, float rot, float movespeed, float rotspeed, int cooltime)
{
	CWood_Spawn *pSpawn = nullptr;

	pSpawn = new CWood_Spawn;

	if (pSpawn != nullptr)
	{
		pSpawn->Init();
		pSpawn->SetPos(pos);
		pSpawn->SetRot(rot);
		pSpawn->SetMoveSpeed(movespeed);
		pSpawn->SetRotSpeed(rotspeed);
		pSpawn->SetCoolTime(cooltime);
		pSpawn->SetFileName("Wood");
	}

	return pSpawn;
}
//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
//=========================================
// include
//=========================================
#include "particle_manager.h"
#include "file.h"

#include <assert.h>

int CParticleManager::m_MaxIndex = 0;
//-----------------------------------------
// �R���X�g���N�^
//-----------------------------------------
CParticleManager::CParticleManager() :
	m_numAll(0),
	m_particleEmitter({})
{
}

//-----------------------------------------
// �f�X�g���N�^
//-----------------------------------------
CParticleManager::~CParticleManager()
{
}

//-----------------------------------------
// ������
//-----------------------------------------
HRESULT CParticleManager::Init()
{
	LoadJson("data/FILE/Effect.json");
	LoadJson("data/FILE/Sand.json");
	LoadJson("data/FILE/Flare.json");
	LoadJson("data/FILE/ice.json");
	return S_OK;
}

//-----------------------------------------
// �I��
//-----------------------------------------
void CParticleManager::Uninit()
{
	for (CParticleEmitter* emitter : m_particleEmitter)
	{
		if (emitter != nullptr)
		{
			emitter->Uninit();
			delete emitter;
			emitter = nullptr;
		}
	}
}

//-----------------------------------------
// �X�V
//-----------------------------------------
void CParticleManager::Update()
{
	for (CParticleEmitter* i : m_particleEmitter)
	{
		if (i == nullptr)
		{
			continue;
		}

		i->Update();
	}
}

//-----------------------------------------
// ����
//-----------------------------------------
int CParticleManager::Create(const D3DXVECTOR3& pos, const int& index,int Type)
{
	
	CParticleEmitter* emitter = new CParticleEmitter();

	emitter->Init();		// ������
	emitter->SetPos(pos);	// �ʒu�̍X�V

	if ((int)m_bundledData[Type].size() <= index)
	{
		assert(false);
		return 0;
	}

	emitter->SetParticle(m_bundledData[Type].at(index).particleData);	// �w�肳��Ă��p�[�e�B�N���f�[�^�̑}��
	emitter->SetEmitter(m_bundledData[Type].at(index).emitterData);

	m_numAll++;
	m_particleEmitter.push_back(emitter);

	return m_particleEmitter.size();
}

//-----------------------------------------
// �����[�X
//-----------------------------------------
void CParticleManager::Release(const int idx)
{
	delete m_particleEmitter.at(idx);
	m_particleEmitter.erase(m_particleEmitter.begin() + (idx));
}

//-----------------------------------------
// �ݒ�
//-----------------------------------------
void CParticleManager::SetBundledData(const BundledData& inData,int Data)
{
	m_bundledData[Data].push_back(inData);
}

//-----------------------------------------
// �`�F���W�@�\
//-----------------------------------------
void CParticleManager::ChangeBundledData(const int idx, const BundledData& inData)
{
	m_bundledData[m_Index].at(idx) = inData;
}

//-----------------------------------------
// �w�肳�ꂽ�ԍ��̈ʒu��ύX����
//-----------------------------------------
void CParticleManager::SetEmitterPos(const int idx, const D3DXVECTOR3 & inPos)
{
	m_particleEmitter.at(idx)->SetPos(inPos);
}

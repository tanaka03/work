//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
#ifndef _PARTICLE_MANAGER_H_
#define _PARTICLE_MANAGER_H_

//=========================================
// include
//=========================================
#include <vector>
#include "particle.h"
#include "particle_emitter.h"

//=========================================
// �O���錾
//=========================================
class CParticleEmitter;

//=========================================
// �p�[�e�B�N���t�@�N�g���[
//=========================================
class CParticleManager
{
public:	// �\����
	struct BundledData
	{
		CParticle::Info particleData;
		CParticleEmitter::Info emitterData;
	};

	enum NOWMAGIC
	{
		NOW_STORM = 0,		// ��
		NOW_SUN,			// ��
		NOW_FIRE,		    // ��
		NOW_ICE,			// �X
		NOW_NON,
		NOW_MAX
	};
public:
	CParticleManager();
	~CParticleManager();

	HRESULT Init();
	void Uninit();
	void Update();
	int Create(const D3DXVECTOR3& pos, const int& idx, int Type);
	void Release(const int idx);
	void SetBundledData(const BundledData&inData, int Data);
	void ChangeBundledData(const int idx, const BundledData&inData);
	void SetEmitterPos(const int idx,const D3DXVECTOR3& inPos);

	// �Q�b�^�\
	std::vector<BundledData>& GetBundledData(int ind) { return m_bundledData[ind]; }
	std::vector<CParticleEmitter*> GetEmitter() { return m_particleEmitter; }
private:
	int m_numAll;	// ������
	std::vector<BundledData> m_bundledData[10];	// ����
	std::vector<CParticleEmitter*> m_particleEmitter;	// �G�~�b�^�\���
	int m_index;
	static int m_MaxIndex;
};

#endif // !_PARTICLE_FACTORY_H_

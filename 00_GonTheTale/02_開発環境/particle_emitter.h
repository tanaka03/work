//=========================================
// 
// �p�[�e�B�N���G�~�b�^
// Author YudaKaito
// Author HamadaRyuuga
//=========================================
#ifndef _PARTICLE_EMITTER_H_
#define _PARTICLE_EMITTER_H_

//=========================================
// include
//=========================================
#include "particle.h"

//=========================================
// �O���錾
//=========================================
class CParticle;

//=========================================
// �p�[�e�B�N���G�~�b�^
//=========================================
class CParticleEmitter
{
public:	// �\����
	struct Info
	{
		float fAngle;
	};
public:	// �ÓI�����o�[�ϐ�
public:
	CParticleEmitter();
	~CParticleEmitter();

	HRESULT Init();
	void Uninit();
	void Update();
	void SetPos(const D3DXVECTOR3& inPos);
	const D3DXVECTOR3& GetPos() { return m_pos; }
	void PopParticle(void);
	void SetParticle(const CParticle::Info& inParticle);
	void SetEmitter(const Info& inEmitter) { m_info = inEmitter; }
	CParticle::Info* GetParticle() { return &m_particleInfo; }
private:
	D3DXVECTOR3 m_pos;	// �o���ʒu
	Info m_info;		// �G�~�b�^�[���Ǘ�������ꗗ
	CParticle::Info m_particleInfo;	// ���̃G�~�b�^�[����o��p�[�e�B�N���̃f�[�^
};

#endif // !_PARTICLE_EMITTER_H_

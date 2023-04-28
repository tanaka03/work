//=============================================================================
//
// �t�F�[�h
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _FADE_H_
#define _FADE_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "object2d.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class  CMotion;

//-----------------------------------------------------------------------------
// �t�F�[�h�N���X
//-----------------------------------------------------------------------------
class CFade : public CObject2d
{
public:
	CFade();
	~CFade();

	//���(���[�h)�̎��
	enum FADE
	{
		FADEIN = 0,
		FADEOUT,
		FADENON,
		FADEMAX
	};

	HRESULT Init() override;	// ������
	void Uninit() override;		// �j��
	void Update() override;		// �X�V
	void Draw() override;		// �`��
	static CFade* Create();		// ����
	void CFade::NextMode(CManager::MODE nextMode);
	FADE * GetFade() { return&fade; };
private:

	float m_FadeSp;
	float m_FadeSet;
	bool m_Bake;
	CManager::MODE m_NextMode;
	FADE fade;

};
#endif
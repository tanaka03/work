//============================
//
// �t�F�[�h�ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "fade.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CFade::CFade() :CObject2d(PRIORITY_FADE)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CFade::~CFade()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CFade::Init(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	CObject2d::Init();
	m_FadeSp = 0.07f;
	m_FadeSet = 0.0f;

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CFade::Uninit(void)
{
	// ���݂̃��[�V�����ԍ��̕ۊ�
	 CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CFade::Update(void)
{
	if (fade != FADENON)
	{
		// ���݂̃��[�V�����ԍ��̕ۊ�
		CObject2d::Update();
		if (fade == FADEOUT)
		{
			m_FadeSet -= m_FadeSp;
		}
		if (fade == FADEIN)
		{
			m_FadeSet += m_FadeSp;
		}

		if (m_FadeSet >= 1.0f)
		{
			fade = FADEOUT;
			m_FadeSet = 1.0f;
			CManager::GetInstance()->SetMode(m_NextMode);

		}
		if (m_FadeSet <= 0.0f)
		{
			fade = FADENON;

			m_FadeSet = 0.0f;

			return;
		}
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeSet));
	}
	
}

//------------------------------------
// �`��
//------------------------------------
void CFade::Draw(void)
{
	 CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CFade* CFade::Create()
{
	CFade * pObject = nullptr;
	pObject = new CFade;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->m_NextMode = CManager::MODE_TITLE;
		pObject->SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
		pObject->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		pObject->SetUp(CObject::MODE);
		pObject->fade = FADENON;
	}
	return pObject;
}


//------------------------------------
// ���̃��[�h�ɂ�����
//------------------------------------
void CFade::NextMode(CManager::MODE nextMode)
{
	if (fade == FADENON)
	{
		Init();
		m_NextMode = nextMode;
		SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		fade = FADEIN;
	}
}

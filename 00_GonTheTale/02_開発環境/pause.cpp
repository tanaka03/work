//**************************************************
//
// ���� ( �^�C�g�� )
// Author : hamada ryuuga
//
//**************************************************
#include "pause.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
 
#include "manager.h"

//========================
// �R���X�g���N�^�[
//========================
CPause::CPause()
{
}
//========================
// �f�X�g���N�g
//========================
CPause::~CPause()
{
}

//================
//����������
//================
HRESULT CPause::Init(void)
{
	// �I�u�W�F�N�g�̐���
	// @param priority			�I�u�W�F�N�g�̃v���C�I���e�B
	// @param tex				�I�u�W�F�N�g�̃e�N�X�`��
	// @param pos				�I�u�W�F�N�g�̈ʒu
	// @param size				�I�u�W�F�N�g�̊g�k
	// @param col				�I�u�W�F�N�g�̐F
	// @return					���������I�u�W�F�N�g�̃|�C���^
	auto createObject = [](CObject::PRIORITY priority, CTexture::TEXTURE tex,
		D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
	{
		CObject2d* obj = CObject2d::Create(priority);
		obj->SetTexture(tex);
		obj->SetPos(pos);
		obj->SetSize(size);
		obj->SetColar(col);
		return obj;
	};

	m_NextMode = MODE_GAME;
	m_OnPause = false;

	// ���[�h�I�����̔w�i����������
	m_Bg = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSEBG,
		CManager::centerPos,
		D3DXVECTOR3(450.0f, CManager::centerPos.y, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	// �Q�[���̕���
	m_object2d[0] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSEGAME,
		CManager::centerPos,
		D3DXVECTOR3(150.0f, 50.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 100.0f;

	// �`���[�g���A���̕���
	m_object2d[1] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSERETURN,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y + y, 0.0f),
		D3DXVECTOR3(150.0f, 50.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	// �����L���O�̕���
	m_object2d[2] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSETITLE,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y + y, 0.0f),
		D3DXVECTOR3(150.0f, 50.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	// �����L���O�̕���
	m_object2d[3] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSEMENU,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y - y, 0.0f),
		D3DXVECTOR3(300.0f, 100.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================
//�j��
//================
void CPause::Uninit(void)
{
	CObject::Release();
}

//==================
//�X�V����
//==================
void CPause::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_PAUSE)&& *CManager::GetInstance()->GetFade()->GetFade() == CFade::FADENON)
	{
		if (m_OnPause)
		{
			Set();
			m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
			for (int i = 0; i < 4; i++)
			{
				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
		else
		{
			m_NextMode = 0;
			Set();
			//�w�i
			m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));
			for (int i = 0; i < 4; i++)
			{//�S�����ς���
				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			//�I�����Ă���
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		if (m_OnPause)
		{
			switch (m_NextMode)
			{
			case MODE::MODE_GAME:
				//���[�h�̐ݒ�
				CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_RETURN:
				//���[�h�̐ݒ�
				m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
				for (int i = 0; i < 4; i++)
				{
					m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
				break;
			case MODE::MODE_TITLE:
				//���[�h�̐ݒ�
				CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
				break;
			default:
				break;
			}
			m_OnPause = false;
		}
		if (m_OnPause)
		{
			m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.30f, 0.5f));
			for (int i = 0; i < 3; i++)
			{
				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_Bg->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			for (int i = 0; i < 3; i++)
			{

				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}
	if (m_OnPause)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			//���[�h�I��
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			m_NextMode = (MODE)(m_NextMode - 1);

			if (m_NextMode < MODE::MODE_GAME)
			{
				m_NextMode = MODE::MODE_TITLE;
			}
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			//���[�h�I��
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			m_NextMode = (MODE)(m_NextMode + 1);

			if (m_NextMode >= MODE::MODE_END)
			{
				m_NextMode = MODE::MODE_GAME;
			}
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

#ifdef _DEBUG
#endif // DEBUG
}

//==================
//�`�揈��
//==================
void CPause::Draw(void)
{
}
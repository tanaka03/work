//=============================================================================
//
// timer�ݒ�
// Author:hamada ryuuga
//
//=============================================================================
#include"timer.h"
#include"number.h"
#include"manager.h"
#include"game.h"


#include "score.h"

int CTimer::m_Myscore;						// ����
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CTimer::CTimer()
{
	m_nTime = 0;
	m_nFrameCount = 0;
	m_nZeroCount = 0;
	m_Myscore = 0;
	m_bCountType = true;
	m_bTimeUp = false;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTimer::~CTimer()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CTimer::Init()
{
	// �ړI�̈ʒu
	m_Pos = { 0.0f,m_DestPos.y,m_DestPos.z };
	m_TimePos = { 1400.0f,m_DestPos.y,m_DestPos.z };

	
	for (int nCnt = 0; nCnt < m_nNumTimer; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create();
		m_pNumber[nCnt]->SetPos({ m_Pos.x + (m_size.x) * nCnt, m_Pos.y, 0.0f });
		m_pNumber[nCnt]->SetSize(m_size*0.65f);
	}

	// �^�C���̐ݒ�
	SetTimer();
	// �擪��0������
	ZeroAlpha();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTimer::Uninit()
{
	m_Myscore = m_nTime;
	for (int nCnt = 0; nCnt < m_nNumTimer; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Uninit();
			m_pNumber[nCnt] = nullptr;
		}
	}

	CObject::Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTimer::Update()
{
	/*if (bCountdown)*/
	{// �J�E���g�_�E�����I����ĂȂ��ꍇ
		for (int nCnt = 0; nCnt < m_nNumTimer; nCnt++)
		{
			if (m_pNumber[nCnt] != nullptr)
			{
				m_pNumber[nCnt]->Update();
				m_pNumber[nCnt]->SetPos({ (m_Pos.x + m_size.x * nCnt),m_Pos.y,m_Pos.z });
			}
		}
		//m_pObject2D->SetPos({ m_TimePos.x,m_TimePos.y,m_TimePos.z });

		// �ړI�̈ʒu�ֈړ�
		m_Pos.x += (m_DestPos.x - m_Pos.x) * 0.05f;
		m_TimePos.x += (1180.0f - m_TimePos.x) * 0.05f;

		m_nFrameCount++;
		m_bCountType = true;

		if (m_nFrameCount % 60 == 0 && m_nTime > 0)
		{
			m_nTime--;
		}
		else if (m_nTime <= 0 && !m_bTimeUp)
		{
			m_bTimeUp = true;

			//// �^�C���A�b�v�̕\��
			//CGameEnd::Create(D3DXVECTOR3(CManager::SCREEN_WIDTH / 2, CManager::SCREEN_HEIGHT / 2, 0.0f),
			//	D3DXVECTOR3(600.0f, 400.0f, 0.0f),
			//	120,
			//	0.05f,
			//	CTexture::TEXTURE_TIMEUP);
		}

#ifdef _DEBUG
#endif // DEBUG

		// �^�C�}�[�̐ݒ�
		SetTimer();
		// �擪��0������
		ZeroAlpha();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTimer::Draw()
{
	for (int nCnt = 0; nCnt < m_nNumTimer; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{
			m_pNumber[nCnt]->Draw();
		}
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CTimer *CTimer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time)
{
	CTimer *pTimer = nullptr;

	pTimer = new CTimer;

	if (pTimer != nullptr)
	{
		pTimer->SetDestPos(pos);
		pTimer->SetSize(size);
		pTimer->SetTimer(time);
		pTimer->Init();
	}

	return pTimer;
}

//--------------------------------------------------
// �^�C�}�[�̐ݒ�
//--------------------------------------------------
void CTimer::SetTimer()
{
	// �e���̊i�[
	m_aPosTexU[0] = m_nTime % 1000 / 100;
	m_aPosTexU[1] = m_nTime % 100 / 10;
	m_aPosTexU[2] = m_nTime % 10;

	for (int nCnt = 0; nCnt < m_nNumTimer; nCnt++)
	{
		if (m_pNumber[nCnt] != nullptr)
		{// �����̃A�j���[�V����
			m_pNumber[nCnt]->AnimTexture(m_aPosTexU[nCnt], 10);
		}
	}
}

//--------------------------------------------------
// �擪��0������
//--------------------------------------------------
void CTimer::ZeroAlpha()
{
	if (m_pNumber[m_nZeroCount] != nullptr)
	{
		if (m_bCountType)
		{// �J�E���g�_�E��
			if (m_aPosTexU[m_nZeroCount] == 0 && m_nTime != 0)
			{
				m_pNumber[m_nZeroCount]->SetNumCol(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_nZeroCount++;
			}
		}
		else
		{// �J�E���g�A�b�v
			if (m_aPosTexU[m_nZeroCount] == 0 && m_nTime != 999)
			{
				m_nZeroCount--;
				m_pNumber[m_nZeroCount]->SetNumCol(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
	}
}

//--------------------------------------------------
// �^�C���̉��Z
//--------------------------------------------------
void CTimer::AddTime(int add)
{
	m_nTime += add;

	// �ő�l�𒴂��Ȃ��悤�ɂ���
	if (m_nTime >= 999)
	{
		m_nTime = 999;
	}

	m_bCountType = false;
}

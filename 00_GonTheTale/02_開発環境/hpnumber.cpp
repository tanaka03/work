//=============================================================================
//
// timer�ݒ�
// Author:hamada ryuuga
//
//=============================================================================
#include"hpnumber.h"
#include"number.h"
#include"manager.h"
#include"game.h"


#include "score.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CHpNumber::CHpNumber()
{
	m_nNumber = 0;
	m_nFrameCount = 0;
	m_nZeroCount = 0;
	m_bCountType = true;
	m_bNumberUp = false;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CHpNumber::~CHpNumber()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CHpNumber::Init()
{
	// �ړI�̈ʒu
	m_Pos = { 350.0f,m_DestPos.y,m_DestPos.z };
	m_NumberPos = { 1400.0f,m_DestPos.y,m_DestPos.z };


	for (int nCnt = 0; nCnt < m_nNumNumber; nCnt++)
	{
		m_pNumber[nCnt] = CNumber::Create();
		m_pNumber[nCnt]->SetPos({ m_Pos.x + (m_size.x) * nCnt, m_Pos.y, 0.0f });
		m_pNumber[nCnt]->SetSize(m_size*0.65f);
	}

	// �^�C���̐ݒ�
	SetNumber();
	// �擪��0������
	ZeroAlpha();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CHpNumber::Uninit()
{
	for (int nCnt = 0; nCnt < m_nNumNumber; nCnt++)
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
void CHpNumber::Update()
{
	/*if (bCountdown)*/
	{// �J�E���g�_�E�����I����ĂȂ��ꍇ
		for (int nCnt = 0; nCnt < m_nNumNumber; nCnt++)
		{
			if (m_pNumber[nCnt] != nullptr)
			{
				m_pNumber[nCnt]->Update();
				m_pNumber[nCnt]->SetPos({ (m_Pos.x + m_size.x * nCnt),m_Pos.y,m_Pos.z });
			}
		}
		//m_pObject2D->SetPos({ m_NumberPos.x,m_NumberPos.y,m_NumberPos.z });
		m_nFrameCount++;
		m_bCountType = true;

		if (m_nFrameCount % 60 == 0 && m_nNumber > 0)
		{
			//m_nNumber--;
		}
		else if (m_nNumber <= 0 && !m_bNumberUp)
		{
			m_bNumberUp = true;

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
		SetNumber();
		// �擪��0������
		ZeroAlpha();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CHpNumber::Draw()
{
	for (int nCnt = 0; nCnt < m_nNumNumber; nCnt++)
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
CHpNumber *CHpNumber::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time)
{
	CHpNumber *pNumber = nullptr;

	pNumber = new CHpNumber;

	if (pNumber != nullptr)
	{
		pNumber->SetDestPos(pos);
		pNumber->SetSize(size);
		pNumber->SetNumber(time);
		pNumber->Init();
	}

	return pNumber;
}

//--------------------------------------------------
// �^�C�}�[�̐ݒ�
//--------------------------------------------------
void CHpNumber::SetNumber()
{
	// �e���̊i�[
	m_aPosTexU[0] = m_nNumber % 1000 / 100;
	m_aPosTexU[1] = m_nNumber % 100 / 10;
	m_aPosTexU[2] = m_nNumber % 10;

	for (int nCnt = 0; nCnt < m_nNumNumber; nCnt++)
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
void CHpNumber::ZeroAlpha()
{
	if (m_pNumber[m_nZeroCount] != nullptr)
	{
		if (m_bCountType)
		{// �J�E���g�_�E��
			if (m_aPosTexU[m_nZeroCount] == 0 && m_nNumber != 0)
			{
				m_pNumber[m_nZeroCount]->SetNumCol(&D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				m_nZeroCount++;
			}
		}
		else
		{// �J�E���g�A�b�v
			if (m_aPosTexU[m_nZeroCount] == 0 && m_nNumber != 999)
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
void CHpNumber::AddNumber(int add)
{
	m_nNumber += add;

	// �ő�l�𒴂��Ȃ��悤�ɂ���
	if (m_nNumber >= 999)
	{
		m_nNumber = 999;
	}

	m_bCountType = false;
}

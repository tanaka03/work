//============================
//
// ��ʓ����ݒ�
// Author:hamada ryuuga
//
//============================

#include "select.h"
#include "utility.h"
#include "popui.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "attack.h"
#include "text.h"
#include "score.h"
#include "3dpolygonbase.h"
#include "reaction.h"
#include "game.h"
#include "timer.h"
#include "effect.h"
#include "bossbar.h"
#include "manager.h"

#include "sound.h"

#include "manager.h"
#include "fade.h"
#include "damageeffect.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CSelect::CSelect() :CObject(PRIORITY_BG)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CSelect::~CSelect()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CSelect::Init()
{
	D3DXVECTOR3 Pos = D3DXVECTOR3(300.0f, -300.0f, 0.0f);
	for (int i = 0; i < PlayerEvent_MAX; i++)
	{
		m_Select[i] = CPopUi::Create();
		m_Select[i]->SetPos(D3DXVECTOR3(-450.0f+(Pos.x*i), Pos.y, Pos.z));
		m_Select[i]->SetSize(D3DXVECTOR3(100.0f, 50.0f, 0.0f));//�T�C�Y�ݒ�

	}
	m_Select[0]->SetTexture(CTexture::TEXTURE_KOUGE);//�T�C�Y�ݒ�
	m_Select[1]->SetTexture(CTexture::TEXTURE_LOOK);//�T�C�Y�ݒ�
	m_Select[2]->SetTexture(CTexture::TEXTURE_ITEM);//�T�C�Y�ݒ�
	m_Select[3]->SetTexture(CTexture::TEXTURE_RUN);//�T�C�Y�ݒ�
	m_Reaction = CReaction::Create();
	m_Reaction->AreaSize(defaultPos, defaultSize);

	m_Timer = CTimer::Create(D3DXVECTOR3(580.0f, 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f),180);
	m_Boss = C3dbase::Create();
	m_Boss->SetPos(D3DXVECTOR3(0.0f, 150.0f, 0.0f));
	m_Boss->SetSize(D3DXVECTOR3(0.0f, 100.0f, 0.0f));//�T�C�Y�ݒ�
	m_Boss->SetSizeMove(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_Boss->SetTexture(CTexture::TEXTURE_BOSS);//�e�N�X�`���I��

	CText* Text = CText::Create(D3DXVECTOR3(640.0f, 400.0f, 0.0f), D3DXVECTOR3(640.0f, 100.0f, 0.0f), CText::MAX, 50, 10, "�T�C�A�N�ȃ��ɂ��킳�ꂻ���Ȃ�������");
	Text->SetRelease(false);
	Text->SetCountXfast(3);

	m_IsSelect = false;
	m_IsReaction = false;
	m_EnemyAttackFaze = false;
	m_Event = PlayerEvent_Attack;
	m_Select[m_Event]->SetColar(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));//�F�ݒ�

	EnemyAttackInit();		// �G�̍U���̏�����
	m_LogOn = false;
	m_NowType = C3dbase::Create();
	m_NowType->SetPos(D3DXVECTOR3(0.0f, 150.0f, 0.0f));
	m_NowType->SetSize(D3DXVECTOR3(0.0f, 100.0f, 0.0f));//�T�C�Y�ݒ�
	m_NowType->SetSizeMove(D3DXVECTOR3(150.0f, 150.0f, 0.0f));
	m_NowType->SetColar(D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.0f));//�F�ݒ�
	m_NowType->SetTexture(CTexture::TEXTURE_RT);//�e�N�X�`���I��
	m_Rot = 0.0f;
	m_AttackPattern = 0;	// �G�̍U���p�^�[��

	m_Hp = CBossbar::Create(D3DXVECTOR3(640.0f, 100.0f, 0.0f), 100);
	m_bReturn = false;
	Return = false;
	m_deathCheck = false;
	m_bReturnTime = 100;
	
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CSelect::Uninit()
{
	CObject::Release();
}

//------------------------------------
// �X�V
//------------------------------------
void CSelect::Update()
{
	m_EnemyAttackFaze = false;
	if (m_IsReaction)
	{//�G�̍U���̂�����Ƃ�
		bool EndEnemyAttack = false;

		// �G�̍U���p�^�[��
		switch (m_AttackPattern)
		{
		case 0:
			SetEnemyAttack(0, 0, 0, 1, 10, { 800.0f, -150.0f, 0.0f }, { -7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(1, 20, 0, 1, 10, { -800.0f, -30.0f, 0.0f }, { 7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(2, 70, 0, 1, 10, { -800.0f, -150.0f, 0.0f }, { 7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			Return = SetEnemyAttack(3, 90, 350, 1, 10, { 800.0f, -30.0f, 0.0f }, { -7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);

			if (Return)
			{
				m_bReturn = true;
			}
			if (m_bReturn)
			{
				EventbackEffect();
			}

			SetEnemyAttack(4, 500, 0, 1, 10, { 800.0f, -150.0f, 0.0f }, { -7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(5, 520, 0, 1, 10, { -800.0f, -30.0f, 0.0f }, { 7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(6, 570, 0, 1, 10, { -800.0f, -150.0f, 0.0f }, { 7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			EndEnemyAttack = SetEnemyAttack(7, 590, 850, 1, 10, { 800.0f, -30.0f, 0.0f }, { -7.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			break;
		case 1:
			SetEnemyAttack(0, 0, 0, 5, 5, { 800.0f, -40.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(1, 0, 0, 5, 5, { 800.0f, -270.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(2, 50, 0, 5, 5, { 800.0f, 60.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			Return = SetEnemyAttack(3, 50, 200, 5, 5, { 800.0f, -170.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			
			if (Return)
			{
				m_bReturn = true;
			}
			if (m_bReturn)
			{
				EventbackEffect();
			}

			SetEnemyAttack(4, 350, 0, 5, 5, { 800.0f, -40.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(5, 350, 0, 5, 5, { 800.0f, -270.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(6, 400, 0, 5, 5, { 800.0f, 60.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			EndEnemyAttack = SetEnemyAttack(7, 400, 500, 5, 5, { 800.0f, -170.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			break;
		case 2:
			SetEnemyAttack(0, 0, 0, 20, 5, { 800.0f, -170.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(1, 130, 0, 20, 5, { 800.0f, -170.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(2, 120, 0, 3, 5, { -800.0f, -25.0f, 0.0f }, { 15.0f, 0.0f, 0.0f }, { 20.0f, 50.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(3, 260, 0, 20, 5, { 800.0f, -170.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			Return = SetEnemyAttack(4, 250, 550, 3, 5, { -800.0f, -25.0f, 0.0f }, { 15.0f, 0.0f, 0.0f }, { 20.0f, 50.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);

			if (Return)
			{
				m_bReturn = true;
			}
			if (m_bReturn)
			{
				EventbackEffect();
			}

			SetEnemyAttack(5, 700, 0, 20, 5, { 800.0f, -170.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(6, 830, 0, 20, 5, { 800.0f, -170.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(7, 820, 0, 3, 5, { -800.0f, -25.0f, 0.0f }, { 15.0f, 0.0f, 0.0f }, { 20.0f, 50.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(8, 960, 0, 20, 5, { 800.0f, -170.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			EndEnemyAttack = SetEnemyAttack(9, 950, 1200, 3, 5, { -800.0f, -25.0f, 0.0f }, { 15.0f, 0.0f, 0.0f }, { 20.0f, 50.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			break;
		case 3:
			SetEnemyAttack(0, 0, 0, 5, 10, { 800.0f, -30.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(1, 50, 0, 3, 10, { -800.0f, -150.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			Return = SetEnemyAttack(2, 60, 300, 1, 0, { 800.0f, -30.0f, 0.0f }, { -7.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);

			if (Return)
			{
				m_bReturn = true;
			}
			if (m_bReturn)
			{
				EventbackEffect();
			}

			SetEnemyAttack(3, 450, 0, 5, 10, { 800.0f, -30.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(4, 500, 0, 3, 10, { -800.0f, -150.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			EndEnemyAttack = SetEnemyAttack(5, 510, 800, 1, 0, { 800.0f, -30.0f, 0.0f }, { -7.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			break;

		case 4:
			SetEnemyAttack(0, 0, 0, 1, 0, { 800.0f, -30.0f, 0.0f }, { -5.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(1, 70, 0, 5, 3, { -800.0f, -170.0f, 0.0f }, { 20.0f, 0.0f, 0.0f }, { 20.0f, 65.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(2, 170, 0, 1, 3, { 800.0f, -170.0f, 0.0f }, { -20.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(3, 200, 0, 5, 3, { -800.0f, -100.0f, 0.0f }, { 15.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			Return = SetEnemyAttack(4, 130, 450, 1, 0, { -800.0f, -30.0f, 0.0f }, { 5.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);

			if (Return)
			{
				m_bReturn = true;
			}
			if (m_bReturn)
			{
				EventbackEffect();
			}

			SetEnemyAttack(5, 500, 0, 1, 0, { 800.0f, -30.0f, 0.0f }, { -5.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(6, 570, 0, 5, 3, { -800.0f, -170.0f, 0.0f }, { 20.0f, 0.0f, 0.0f }, { 20.0f, 65.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(7, 670, 0, 1, 3, { 800.0f, -170.0f, 0.0f }, { -20.0f, 0.0f, 0.0f }, { 20.0f, 80.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(8, 700, 0, 5, 3, { -800.0f, -100.0f, 0.0f }, { 15.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			EndEnemyAttack = SetEnemyAttack(9, 630, 800, 1, 0, { -800.0f, -30.0f, 0.0f }, { 5.0f, 0.0f, 0.0f }, { 20.0f, 100.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			break;
		case 5:
			SetEnemyAttack(0, 0, 0, 3, 20, { 800.0f, -85.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { 20.0f, 150.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			Return = SetEnemyAttack(1, 0, 550, 3, 20, { -800.0f, -85.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, { 20.0f, 150.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(2, 0, 0, 1, 0, { 800.0f, -170.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(3, 0, 0, 1, 0, { -800.0f, -30.0f, 0.0f }, { 8.0f, 0.0f, 0.0f }, { 20.0f, 70.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);
			SetEnemyAttack(4, 100, 0, 1, 0, { -800.0f, -30.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, { 20.0f, 70.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 0.5f }, false);

			if (Return)
			{
				m_bReturn = true;
			}
			if (m_bReturn)
			{
				EventbackEffect();
			}

			SetEnemyAttack(5, 700, 0, 3, 20, { 800.0f, -85.0f, 0.0f }, { -3.0f, 0.0f, 0.0f }, { 20.0f, 150.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			EndEnemyAttack = SetEnemyAttack(6, 700, 950, 3, 20, { -800.0f, -85.0f, 0.0f }, { 3.0f, 0.0f, 0.0f }, { 20.0f, 150.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(7, 700, 0, 1, 0, { 800.0f, -170.0f, 0.0f }, { -4.0f, 0.0f, 0.0f }, { 20.0f, 60.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(8, 700, 0, 1, 0, { -800.0f, -30.0f, 0.0f }, { 8.0f, 0.0f, 0.0f }, { 20.0f, 70.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
			SetEnemyAttack(9, 800, 0, 1, 0, { -800.0f, -30.0f, 0.0f }, { 10.0f, 0.0f, 0.0f }, { 20.0f, 70.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, true);
		default:
			break;
		}

		if (EndEnemyAttack)
		{
			CText* Text = CText::Create(D3DXVECTOR3(640.0f, 400.0f, 0.0f), D3DXVECTOR3(640.0f, 100.0f, 0.0f), CText::MAX, 50, 10, "�ɂ��΂͂Ȃ�");
			Text->SetRelease(false);
			Text->SetCountXfast(3);
			m_Reaction->AreaSize(defaultPos, defaultSize);
			m_IsReaction = false;

			// �U���p�^�[���̍X�V
			if (m_AttackPattern == 5)
			{
				// �ŏ��ɖ߂�
				m_AttackPattern = 0;
			}
			else
			{
				// �i�߂�
				m_AttackPattern++;
			}
			m_EnemyAttackFaze = true;
			m_LogOn = false;
			EnemyAttackInit();		// �G�̍U���̏�����
		}
	}
	else
	{//������̍U��
		if (m_IsSelect)
		{//�I��������ǂ��Ȃ邩
			switch (m_Event)
			{
			case CSelect::PlayerEvent_Attack:
				//�U��
				EventAttackUpdate();
				break;
			case CSelect::PlayerEvent_Minor:
			{
				CText* Text = CText::Create(D3DXVECTOR3(640.0f, 400.0f, 0.0f), D3DXVECTOR3(640.0f, 100.0f, 0.0f), CText::MAX, 50, 10, "����ׂ�Ȃ�");
				//���ׂ�Ƃ��H
				m_IsSelect = false;
				Text->SetRelease(false);
				Text->SetCountXfast(3);
			}
				break;
			case CSelect::PlayerEvent_Item:
			{
				CText* Text = CText::Create(D3DXVECTOR3(640.0f, 400.0f, 0.0f), D3DXVECTOR3(640.0f, 100.0f, 0.0f), CText::MAX, 50, 10, "�A�C�e���͂Ȃ�");
				//�A�C�e���Ƃ��H
				m_IsSelect = false;
				Text->SetRelease(false);
				Text->SetCountXfast(3);
			}
				break;
			case CSelect::PlayerEvent_Miss:
			{
				CText* Text = CText::Create(D3DXVECTOR3(640.0f, 400.0f, 0.0f), D3DXVECTOR3(640.0f, 100.0f, 0.0f), CText::MAX, 50, 10, "�ɂ���Ȃ�");
				//�������Ƃ��H
				m_IsSelect = false;
				Text->SetRelease(false);
				Text->SetCountXfast(3);
			}
				break;
			case CSelect::PlayerEvent_MAX:
				break;
			default:
				break;
			}
		}
		else
		{//�I�����Ă������߂���
			m_Select[m_Event]->GetPos();
			CPlayer*Player = CGame::GetPlayer();

			D3DXVECTOR3 Pos = *m_Select[m_Event]->GetPos();
			
			Player->SetPos(Pos);

			CInput *CInputpInput = CInput::GetKey();
			if (CInputpInput->Trigger(CInput::KEY_RIGHT))
			{


				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);	//ui�ړ���

				m_Select[m_Event]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�F�ݒ�
				m_Event = (PlayerEvent)(m_Event + 1);
				if (m_Event >= PlayerEvent_MAX)
				{
					m_Event = PlayerEvent_Attack;
				}

				m_Select[m_Event]->SetColar(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));//�F�ݒ�
			}
			if (CInputpInput->Trigger(CInput::KEY_LEFT))	//ui�ړ���
			{

				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);

				m_Select[m_Event]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�F�ݒ�
				m_Event = (PlayerEvent)(m_Event - 1);
				if (m_Event < PlayerEvent_Attack)
				{
					m_Event = PlayerEvent_Miss;
				}
				m_Select[m_Event]->SetColar(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));//�F�ݒ�
			}
			if (CInputpInput->Trigger(CInput::KEY_SHOT))
			{
				CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_ON);
				
				switch (m_Event)
				{//���肵���珉�����������������z����Ƃ�
				case CSelect::PlayerEvent_Attack:
					CSelect::EventAttackInit();
					break;
				case CSelect::PlayerEvent_Minor:
					break;
				case CSelect::PlayerEvent_Item:
					break;
				case CSelect::PlayerEvent_Miss:
					break;
				case CSelect::PlayerEvent_MAX:
					break;
				default:
					break;
				}
				m_IsSelect = true;
			}

		}
		
	}

	if (m_deathCheck)
	{
		static int deathTime = 0;
		deathTime++;

		const D3DXVECTOR3* EnemyPos = m_Boss->GetPos();
		int popEffect = 40;

		if ((deathTime % 25) == 0)
		{
			for (int i = 0; i < popEffect; i++)
			{
				CEffect* pEffect = CEffect::Create(D3DXVECTOR3(sinf((i * ((360 / popEffect) * (D3DX_PI / 180)))), cosf((i * ((360 / popEffect) * (D3DX_PI / 180)))), 0.0f));
				pEffect->SetPos(*EnemyPos);
				pEffect->SetColar(D3DXCOLOR(1.0f,0.5f,0.0f,1.0f));
			}
		}

		if (deathTime > 150)
		{
			CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		}
	}
}

//------------------------------------
// �`��
//------------------------------------
void CSelect::Draw()
{
	
}

//------------------------------------
// create
//------------------------------------
CSelect *CSelect::Create()
{
	CSelect * pObject = new CSelect;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}
//------------------------------------
// Player�̍U���̏�����
//------------------------------------
void CSelect::EventAttackInit()
{
	//m_nEnemyAttackCount = 0;
	m_Attackvariation = 0; 
	m_Difference = 0.0f;
	m_ColarTimer = 0;
	m_Reaction->AreaSize(AttackdefaultPos, AttackdefaultSize);
	//�U���̂��
	m_3dbase = C3dbase::Create();
	m_3dbase->SetPos(D3DXVECTOR3(0.0f, -50.0f, 0.0f));
	m_3dbase->SetSize(D3DXVECTOR3(0.0f, 70.0f, 0.0f));//�T�C�Y�ݒ�
	m_3dbase->SetSizeMove(D3DXVECTOR3(480.0f, 70.0f, 0.0f));
	m_3dbase->SetTexture(CTexture::TEXTURE_LINE);//�e�N�X�`���I��

	for (int i = 0; i < Max; i++)
	{
		D3DXVECTOR3 Pos = D3DXVECTOR3(-300.0f, -50.0f, 0.0f);
		m_Difference += FloatRandom(150, 50);
		m_Attack[i] = CAttack::Create();
		m_Attack[i]->SetPos(D3DXVECTOR3(Pos.x- m_Difference, Pos.y, Pos.z));
		m_Attack[i]->SetSize(D3DXVECTOR3(20.0f, 100.0f, 0.0f));//�T�C�Y�ݒ�
		m_Attack[i]->SetMove(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
		m_Attack[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 01.0f));//�F�ݒ�
	}
	
}
//------------------------------------
// Player�̍U���̂͂�
//------------------------------------
void CSelect::EventAttackUninit()
{
}
//------------------------------------
//Player�̍U���̃A�b�v�f�[�g
//------------------------------------
void CSelect::EventAttackUpdate()
{
	//�U���̔���̖_�F�ς�
	m_ColarTimer++;
	if (m_ColarTimer == 5)
	{
		m_Attack[m_Attackvariation]->SetColar(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));//�F�ݒ�
	}
	if (m_ColarTimer >= 10)
	{
		m_Attack[m_Attackvariation]->SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));//�F�ݒ�
		m_ColarTimer = 0;
	}

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_SHOT))
	{	//�U���̔���̖_���W�Ƃ�
		D3DXVECTOR3 Pos = *m_Attack[m_Attackvariation]->GetPos();
		//�U���̔���̖_����
		m_Attack[m_Attackvariation]->Release();
		//�U���̉񐔉��Z
		m_Attackvariation++;
		if (m_Attackvariation >= Max)
		{//�U���̍ő吔��������
			m_3dbase->Release();
			//����̍U���̔���N������
			m_IsReaction = true;
			//������̃R�}���h�I��
			m_IsSelect = false;
			//�����g�𓮂���
			m_Reaction->AreaSize(ReactiondefaultPos, ReactiondefaultSize);
			//Player�̈ړ�
			CGame::GetPlayer()->SetDifferenceMove(ReactiondefaultPos);
		}

 		CDamageEffect::Create({ 0.0f,0.0f,0.0f });//���W�ݒ�;
		

		float rate;
		if (Pos.x <= 0)
		{
			rate = 250.0f / -Pos.x;
		}
		else
		{
			rate = 250.0f / Pos.x;
		}
		if (Pos.x <= +17 && Pos.x >= -17)	//���_���[�W������ȊO�ŉ���ς��Ă���
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BOM);
		}
		else
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BOM1);
		}

		if (rate >= 5.0f)
		{
			rate = 5.0f;
		}
		
 		m_Hp->SetDamage(rate);
		if (m_Hp->Getlife() <= 0.0f)
		{
			m_deathCheck = true;
		}
		//m_Score->Add(rate);
	}
	if (m_Attack[m_Attackvariation]->GetPos()->x >= 540)
	{
		//�U���̔���̖_����
		m_Attack[m_Attackvariation]->Release();
		//�U���̔���̉񐔉��Z
		m_Attackvariation++;
		if (m_Attackvariation >= Max)
		{	//�U���̔���̉摜����
			m_3dbase->Release();

			m_IsReaction = true;
			m_IsSelect = false;
			//�����g�𓮂���
			m_Reaction->AreaSize(ReactiondefaultPos, ReactiondefaultSize);
			CGame::GetPlayer()->SetDifferenceMove(ReactiondefaultPos);
		}
	}

}

//------------------------------------
//�G�̍U���̏�����
//------------------------------------
void CSelect::EnemyAttackInit()
{
	for (int nCnt = 0; nCnt < AttackSetMax; nCnt++)
	{
		AttackSet[nCnt].nEnemyAttackCount = 0;		// �U����
		AttackSet[nCnt].nDelay = 0;					// �U���Ԋu
		AttackSet[nCnt].nCreateTime = 0;			// �U�����o��܂ł̎���
		AttackSet[nCnt].nEndTime = 0;				// �U�����I��鎞��
	}
}

//------------------------------------
//�G�̍U��
//------------------------------------
bool CSelect::SetEnemyAttack(int Setnum, int CreateTime, int EndTime, int Num, int Delay, D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR Col, bool Collision)
{

	int dlay = 7;

	if (AttackSet[Setnum].nCreateTime <= dlay)
	{
		CGame::GetPlayer()->SetDifferenceMove(ReactiondefaultPos);
		if (AttackSet[Setnum].nCreateTime == dlay)
		{
			m_LogOn = true;
		}

	}

	// �U���̊Ԋu
	AttackSet[Setnum].nDelay--;
	// �U�����o��܂ł̎���
	AttackSet[Setnum].nCreateTime++;
	// �U�����I��鎞��
	AttackSet[Setnum].nEndTime++;

	if (AttackSet[Setnum].nDelay <= 0 
		&& AttackSet[Setnum].nEnemyAttackCount < Num 
		&& AttackSet[Setnum].nCreateTime >= CreateTime)
	{
		m_EnemyAttack = CAttack::Create();	// ����
		m_EnemyAttack->SetPos(Pos);			// �ʒu
		m_EnemyAttack->SetMove(Move);		// �ړ����x
		m_EnemyAttack->SetSize(Size);		// �T�C�Y�ݒ�
		m_EnemyAttack->SetColar(Col);		// �F�ݒ�
		m_EnemyAttack->SetCollision(Collision);

		// �f�B���C�̍X�V
		AttackSet[Setnum].nDelay = Delay;

		// �G�̍U���̐�
		AttackSet[Setnum].nEnemyAttackCount++;
	}

	// �U�����I��鎞��
	if (AttackSet[Setnum].nEndTime == EndTime)
	{
		return true;
	}

	return false;
}

//------------------------------------
//�߂鎞�̃G�t�F�N�g
//------------------------------------
void CSelect::EventbackEffect()
{
	m_bReturnTime--;

	if (m_bReturnTime > 0)
	{
		m_Rot -= 0.1f;
		NormalizeAngle(&m_Rot);
		m_NowType->SetRot(D3DXVECTOR3(0.0f, 0.0f, m_Rot));
		m_NowType->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�F�ݒ�

		if (m_bReturnEffect)
		{
			for (int i = 0; i < 5; i++)
			{
				D3DXVECTOR3 Pos = D3DXVECTOR3(-600.0f, -50.0f, 0.0f);
				float DifferenceX = FloatRandom(500, 10);
				float DifferenceY = FloatRandom(150, -150);
				CEffect*Effect = CEffect::Create(D3DXVECTOR3(10.0f, 0.0f, 0.0f));
				Effect->SetPos(D3DXVECTOR3(Pos.x + DifferenceX, Pos.y + DifferenceY, Pos.z));
				Effect->SetSize(D3DXVECTOR3(20.0f, 100.0f, 0.0f));//�T�C�Y�ݒ�
				Effect->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.1f));//�F�ݒ�
			}

			m_bReturnEffect = false;
		}
	}
	else
	{
		m_NowType->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));//�F�ݒ�
		m_bReturnTime = 100;
		m_bReturn = false;
		m_bReturnEffect = true;
	}
}

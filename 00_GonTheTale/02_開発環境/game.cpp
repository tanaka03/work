//============================
//
// �Q�[�����
// Author:hamada ryuuga
//
//============================

//-----------------------------------------------------------------------------
// �C���N���[�h
//-----------------------------------------------------------------------------
#include "game.h"
#include "input.h"
#include "manager.h"
#include "light.h"

#include "fade.h"
#include "multiply.h"
#include "particle_manager.h"
#include "score.h"
#include "sound.h"
#include "pause.h"

#include "camera.h"
#include "ranking.h"
#include "player.h"
#include "select.h"

#include "damageeffect.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�[�ϐ��̐錾
//-----------------------------------------------------------------------------
CPause *CGame::m_Pause = nullptr;
CPlayer*CGame::m_Player = nullptr;
int CGame::m_GameScore = 0;

//=============================================================================
// �R���X�g���N�^�[
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// �f�X�g���N�g
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// ������
//=============================================================================
HRESULT CGame::Init(void)
{
	m_GameCount = 0;
	m_SpeedUp = 300;
	m_nCntSpawn = 0;
	
//	CManager::GetInstance()->GetRenderer()->SetFog(true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_GameScore = 0;

	m_Pause = new CPause;
	m_Pause->Init();
	m_Pause->SetUp(CObject::PAUSE);

	m_Player = CPlayer::Create();



	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_GAME);//

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CGame::Uninit(void)
{
	if (m_Pause != nullptr)
	{
		m_Pause->Uninit();
		m_Pause = nullptr;
	}
	CManager::GetInstance()->GetSound()->Stop();
	CObject::Release();
	//CObjectXManager::ReleaseAll();
}

//=============================================================================
// �X�V
//=============================================================================
void CGame::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();
	
	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		m_Player->SetNowType(CPlayer::GRAVITY_MOVE);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_F2))
	{
		m_Player->SetNowType(CPlayer::DEFAULT_MOVE);
		return;
	}
	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		return;
	}
}

//=============================================================================
// �`��
//=============================================================================
void CGame::Draw(void)
{
}

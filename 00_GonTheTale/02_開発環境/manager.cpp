//=============================================================================
//
// �}�l�[�W���[
// Author : �l�c����
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "manager.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "texture.h"
#include "tutorial.h"

#include "font.h"
#include "nameset.h"
#include "ranking.h"
#include "playfab.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
HWND g_hWnd;

//-----------------------------------------------------------------------------
// �ÓI�����o�[�ϐ��̏�����
//-----------------------------------------------------------------------------
CManager * CManager::m_manager = nullptr;
const D3DXVECTOR3 CManager::centerPos = D3DXVECTOR3((float)SCREEN_WIDTH * 0.5f, (float)SCREEN_HEIGHT * 0.5f, 0.0f);
CManager::LEVEL * CManager::m_Level;
//=============================================================================
// �V���O���g���ł̃C���X�^���X�̎擾
//=============================================================================
CManager * CManager::GetInstance()
{
	if (m_manager == nullptr)
	{
		m_manager = new CManager;
	}
	return m_manager;
}

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CManager::CManager() :
	m_pTexture(nullptr),
	m_cRenderer(nullptr),
	m_Fade(nullptr),
	m_Game(nullptr),
	m_Sound(nullptr)
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CManager::Init(HWND hWnd, bool /*bWindow*/, HINSTANCE hInstance)
{
	srand((unsigned int)time(NULL)); // ���ݎ����̏��ŏ�����

	m_cRenderer = new CRenderer;

	m_Input = CInput::Create();

	g_hWnd = hWnd;

	// ����������
	if (FAILED(m_cRenderer->Init(hWnd, FALSE)))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return -1;
	}
	//���͏����̏���������
	if (FAILED(m_Input->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_Sound = nullptr;
	m_Sound = new CSound;

	//���͏����̏���������
	if (FAILED(m_Sound->Init(hWnd)))
	{
		return E_FAIL;
	}

	m_pTexture = nullptr;
	m_pTexture = new CTexture;
	
	{//��ʑJ��
		m_mode = CManager::MODE_TITLE;	//���݂̃��[�h
	}
	
	//���[�h�̐ݒ�
	m_Fade = CFade::Create();
	SetMode(m_mode);


	m_pFont = nullptr;
	m_pFont = new CFont;

	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CManager::Uninit()
{

	CObject::AllUninit();

	if (m_pTexture != nullptr)
	{// �I������
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}
	if (m_cRenderer != nullptr)
	{// �I������

		m_cRenderer->Uninit();
		delete m_cRenderer;
		m_cRenderer = nullptr;
	}
	if (m_Sound != nullptr)
	{// �I������

		m_Sound->Uninit();
		delete m_Sound;
		m_Sound = nullptr;
	}
	

	if (m_pFont != nullptr)
	{// �I������

		m_pFont->ReleaseAll();
		delete m_pFont;
		m_pFont = nullptr;
	}

	//���͏����̏I������
	m_Input->Uninit();


}

//=============================================================================
// �X�V
//=============================================================================
void CManager::Update()
{

	CPlayfab::APIUp();
	//���͏����̍X�V����
	m_Input->Update();


	m_cRenderer->Update();
}

//=============================================================================
// �`��
//=============================================================================
void CManager::Draw()
{
	// �`�揈��	
	m_cRenderer->Draw();
}

//=============================================================================
// GetRenderer
//=============================================================================
CRenderer *CManager::GetRenderer()
{
	return m_cRenderer;
}


//=============================================================================
// GetTexture
//=============================================================================
CTexture *CManager::GetTexture()
{
	return m_pTexture;
}

//=============================================================================
// GetFade
//=============================================================================
CFade * CManager::GetFade()
{
	return m_Fade;
}

//=============================================================================
// Getfont
//=============================================================================
CFont * CManager::GetFont()
{
	return m_pFont;
}

//=============================================================================
// GetMode
//=============================================================================
CManager::MODE * CManager::GetMode()
{
	return &m_mode;
}

//=============================================================================
// GetSound
//=============================================================================
CSound * CManager::GetSound()
{
	return m_Sound;
}

HWND GetWnd(void)
{
	return g_hWnd;
}

//========================
// ���[�h�̐ݒ�
//========================
void CManager::SetMode(MODE mode)
{
	m_mode = mode;
	if (m_Game != nullptr)
	{
		m_Game->Uninit();
	}

	// �|���S���̏I������
	CObject::ModeNotUninit();
	
	switch (mode)
	{
	case CManager::MODE_TITLE:
		m_Game = new CTitle;
		break;
	case CManager::MODE_GAME:
	{
		m_Game = new CGame;
		break;
	}
	case CManager::MODE_RESULT:
		m_Game = new CResult;
		break;
	case CManager::MODE_RANKING:
		m_Game = new CRanking;
		break;
	case CManager::MODE_NAMESET:
		m_Game = new CNameSet;
		break;
	case CManager::MODE_TUTORIAL:
	{
		m_Game = new CTutorial;
		break;
	}
	case CManager::MODE_GAMEOVER:	
		m_Game = new CTitle;
		break;

	default:
		m_Game = new CTitle;
		break;
	}

	// ����������
	if (FAILED(m_Game->Init()))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return ;
	}
	m_Game->SetUp(CObject::MODE);
}




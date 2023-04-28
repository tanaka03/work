//=============================================================================
//
// ���͏��� [input.cpp]
// Author1 : KOZUNA HIROHITO
// input.h���Q�Ƃ𐄏�
//
//=============================================================================

//-----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "input.h"

CInput *CInput::m_Input = nullptr;

//*************************************************************************************
//�R���X�g���N�^
//*************************************************************************************
CInput::CInput()
{
	m_pKeyboard = nullptr;
	m_pKeyJoypad = nullptr;
}

//*************************************************************************************
//�f�X�g���N�^
//*************************************************************************************
CInput::~CInput()
{
}

//*************************************************************************************
//������
//*************************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_pKeyboard = new CInputKeyboard;

	//�L�[�{�[�h�̏���������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	m_pKeyJoypad = new CInputController;

	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//*************************************************************************************
//�I������
//*************************************************************************************
void CInput::Uninit()
{
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_pKeyJoypad != nullptr)
	{
		m_pKeyJoypad->Uninit();
		delete m_pKeyJoypad;
		m_pKeyJoypad = nullptr;
	}

	if (m_Input != nullptr)
	{
		delete m_Input;
		m_Input = nullptr;
	}
}

//*************************************************************************************
//�X�V����
//*************************************************************************************
void CInput::Update()
{
	m_pKeyboard->Update();
	m_pKeyJoypad->Update();
}

//*************************************************************************************
//�C���v�b�g�̐���
//*************************************************************************************
CInput *CInput::Create()
{
	m_Input = new CInput;
	return m_Input;
}

//*************************************************************************************
//�v���X����
//*************************************************************************************
bool CInput::Press(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case CInput::KEY_UP:
		if (m_pKeyboard->GetKeyboardPress(DIK_W)
			|| m_pKeyboard->GetKeyboardPress(DIK_UP)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_UP,0)
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_RIGHT_STICK, 0).y < -0.5f
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_LEFT_STICK, 0).y < -0.5f)
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetKeyboardPress(DIK_S)
			|| m_pKeyboard->GetKeyboardPress(DIK_DOWN)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_DOWN, 0)
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_RIGHT_STICK, 0).y > 0.5f
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_LEFT_STICK, 0).y > 0.5f)
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetKeyboardPress(DIK_A)
			|| m_pKeyboard->GetKeyboardPress(DIK_LEFT)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_LEFT, 0)
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_RIGHT_STICK, 0).x < -0.5f
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_LEFT_STICK, 0).x < -0.5f)
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetKeyboardPress(DIK_D)
			|| m_pKeyboard->GetKeyboardPress(DIK_RIGHT)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_RIGHT, 0)
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_RIGHT_STICK, 0).x > 0.5f
			|| m_pKeyJoypad->GetJoypadStick(CInputController::JOYKEY_LEFT_STICK, 0).x > 0.5f)
		{
			return true;
		}
		break;
	case CInput::KEY_DECISION:
		if (m_pKeyboard->GetKeyboardPress(DIK_RETURN)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_A , 0)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_LEFT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_SHOT:
		if (m_pKeyboard->GetKeyboardPress(DIK_SPACE)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_B, 0)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_RIGHT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DEBUG:
		if (m_pKeyboard->GetKeyboardPress(DIK_F1))
		{
			return true;
		}
		break;
	case CInput::KEY_F2:
		if (m_pKeyboard->GetKeyboardPress(DIK_F2))
		{
			return true;
		}
		break;

	case CInput::KEY_DELETE:
		if (m_pKeyboard->GetKeyboardPress(DIK_BACKSPACE)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_B, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_RELOAD:
		if (m_pKeyboard->GetKeyboardPress(DIK_R))
		{
			return true;
		}
		break;
	case CInput::KEY_INVENTORY:
		if (m_pKeyboard->GetKeyboardPress(DIK_E))
		{
			return true;
		}
		break;
	case CInput::KEY_DROP:
		if (m_pKeyboard->GetKeyboardPress(DIK_Q))
		{
			return true;
		}
		break;
	case CInput::KEY_PAUSE:
		if (m_pKeyboard->GetKeyboardPress(DIK_P)
			|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_START, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_SHIFT:
		if (m_pKeyboard->GetKeyboardPress(DIK_LSHIFT))
		{
			return true;
		}
		if (m_pKeyboard->GetKeyboardPress(DIK_RSHIFT))
		{
			return true;
		}
		break;
	case CInput::KEY_HAVE:
		if (m_pKeyboard->GetKeyboardPress(DIK_F)|| m_pKeyJoypad->GetJoypadPress(CInputController::JOYKEY_X, 0))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//�g���K�[����
//*************************************************************************************
bool CInput::Trigger(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case CInput::KEY_UP:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_W)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_UP)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_UP, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_S)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_DOWN)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_DOWN, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_A)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_LEFT)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_LEFT, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_D)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_RIGHT)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_RIGHT, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DECISION:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_RETURN)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_A, 0)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_LEFT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_SHOT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_SPACE)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_B, 0)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_RIGHT_SHOULDER, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_DEBUG:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_F1))
		{
			return true;
		}
		break;
	case CInput::KEY_F2:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_F2))
		{
			return true;
		}
		break;
	case CInput::KEY_DELETE:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_BACKSPACE)
			|| m_pKeyJoypad->GetJoypadTrigger(CInputController::JOYKEY_B, 0))
		{
			return true;
		}
		break;
	case CInput::KEY_RELOAD:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_R))
		{
			return true;
		}
		break;	
	case CInput::KEY_INVENTORY:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_E))
		{
			return true;
		}
		break;
	case CInput::KEY_DROP:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_Q))
		{
			return true;
		}
		break;
	case CInput::KEY_PAUSE:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_P))
		{
			return true;
		}
		break;
	case CInput::KEY_MESHUP:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_O))
		{
			return true;
		}
		break;
	case CInput::KEY_MESHDOWN:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_L))
		{
			return true;
		}
		break;
	case CInput::KEY_SHIFT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_LSHIFT))
		{
			return true;
		}
		if (m_pKeyboard->GetKeyboardTrigger(DIK_RSHIFT))
		{
			return true;
		}
		break;
	case CInput::KEY_HAVE:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_F))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}
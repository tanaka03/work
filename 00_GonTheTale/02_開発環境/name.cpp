//============================
//
// NUME
// Author:hamada ryuuga
//
//============================

#include "name.h"
#include "manager.h"
#include "input.h"


//=============================================================================
// �R���X�g���N�^�֐�
//=============================================================================
CName::CName(int list) : CObject2d(list)
{
}

//=============================================================================
// �f�X�g���N�^�֐�
//=============================================================================
CName::~CName()
{
}

//=============================================================================
// �������֐�
//=============================================================================
HRESULT CName::Init()
{
	CObject2d::Init();
	CObject2d::SetTexture(CTexture::TEXTURE_ALPHABET);
	col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_DivisionX = 7;
	m_DivisionY = 4;
	m_DivisionMAX = m_DivisionX*m_DivisionY;

	m_type = A;

	SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
	int X = m_type%m_DivisionX;
	int Y = m_type/m_DivisionX;
	float DivisionX = (1.0f / m_DivisionX);
	float DivisionY = (1.0f / m_DivisionY);

	m_move = true;

	SetTex(PositionVec4(
		DivisionX*X,
		DivisionX*X + DivisionX,
		DivisionY*Y,
		DivisionY*Y + DivisionY));

	return S_OK;
}

//=============================================================================
// �j���֐�
//=============================================================================
void CName::Uninit()
{
	CObject2d::Uninit();
}


//=============================================================================
// �X�V�֐�
//=============================================================================
void CName::Update()
{
	CObject2d::Update();

	CInput *CInputpInput = CInput::GetKey();

	if (m_move)
	{
		if (CInputpInput->Trigger(CInput::KEY_RIGHT))
		{
			int nextType = m_type + 1;
			if (nextType > MAX)
			{
				nextType = 0;
			}
		
			switch (nextType/4)
			{
			case 0:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
				break;
			case 1:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
				break;
			case 2:
				SetColar(D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f));
				
				break;
			case 3:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 4:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
				break;
			case 5:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 6:
				SetColar(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
				break;
			default:
				SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
			SetAlphabet((ALPHABET)nextType);

		}
		if (CInputpInput->Trigger(CInput::KEY_LEFT))
		{
			int nextType = m_type - 1;
			if (nextType <= -1)
			{
				nextType = 26;
			}
			switch (nextType / 4)
			{
			case 0:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
				break;
			case 1:
				SetColar(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
				break;
			case 2:
				SetColar(D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f));

				break;
			case 3:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 4:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
				break;
			case 5:
				SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
				break;
			case 6:
				SetColar(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
				break;
			default:
				SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
			SetAlphabet((ALPHABET)nextType);
		}
	}
}

//=============================================================================
// �`��֐�
//=============================================================================
void CName::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();

	// �V�K�[�x�l <= Z�o�b�t�@�[�x�l (�����ݒ�)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// ���e�X�g�𖳌��ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �����֐�
//=============================================================================
CName *CName::Create()
{
	CName * pObject = nullptr;
	pObject = new CName(1);

	if (pObject != nullptr)
	{
		pObject->Init();

		pObject->SetTexture(CTexture::TEXTURE_ALPHABET);
	}

	return pObject;
}

//=============================================================================
// ALPHABET�ύX����֐�
//=============================================================================
void CName::SetAlphabet(const ALPHABET Alphabet)
{
	m_type = Alphabet;

	switch (m_type / 4)
	{
	case 0:
		SetColar(D3DXCOLOR(0.8f, 0.0f, 0.0f, 1.0f));
		break;
	case 1:
		SetColar(D3DXCOLOR(0.8f, 0.0f, 0.8f, 1.0f));
		break;
	case 2:
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.8f, 1.0f));

		break;
	case 3:
		SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
		break;
	case 4:
		SetColar(D3DXCOLOR(0.0f, 0.8f, 0.0f, 1.0f));
		break;
	case 5:
		SetColar(D3DXCOLOR(0.0f, 0.8f, 0.8f, 1.0f));
		break;
	case 6:
		SetColar(D3DXCOLOR(0.8f, 0.8f, 0.0f, 1.0f));
		break;
	default:
		SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		break;

	}
	int X = m_type%m_DivisionX;
	int Y = m_type / m_DivisionX;
	float DivisionX = (1.0f / m_DivisionX);
	float DivisionY = (1.0f / m_DivisionY);

	SetTex(PositionVec4(
		DivisionX*X,
		DivisionX*X + DivisionX,
		DivisionY*Y,
		DivisionY*Y + DivisionY));
}

//=============================================================================
// �������������Ȃ���
//=============================================================================
void CName::SetMoveSwitch(bool move)
{
	m_move = move;
}

//=============================================================================
// Alphabet�擾����֐�
//=============================================================================
CName::ALPHABET CName::GetAlphabet()
{
	return m_type;
}

//============================
//
// NUMBER
// Author:hamada ryuuga
//
//============================
#include "number.h"
#include "manager.h"

//-----------------------------------------------------------------------------
// �R���X�g���N�g�֐�
//-----------------------------------------------------------------------------
CNumber::CNumber(int list) : CObject2d(list)
{
}

//-----------------------------------------------------------------------------
// �f�X�g���N�g�֐�
//-----------------------------------------------------------------------------
CNumber::~CNumber()
{
}

//-----------------------------------------------------------------------------
// �������֐�
//-----------------------------------------------------------------------------
HRESULT CNumber::Init()
{
	CObject2d::Init();
	CObject2d::SetTexture(CTexture::TEXTURE_SCORE);
	SetTex(PositionVec4(
		0.0f, 0.1f, 0.0f, 1.0f));

	m_MyNumber = 0;
	m_speed = 0.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	m_isRelease = false;
	m_DesTimar = 0;
	m_move = true;

	return S_OK;
}

//-----------------------------------------------------------------------------
// �j���֐�
//-----------------------------------------------------------------------------
void CNumber::Uninit()
{
	CObject2d::Uninit();
}

//-----------------------------------------------------------------------------
// �X�V�֐�
//-----------------------------------------------------------------------------
void CNumber::Update()
{
	CObject2d::Update();

	if (m_isRelease)
	{
		m_DesTimar--;

		m_col.a -= 1.0f / m_DesTimarMax;

		m_pos.y -= 1.0f;

		CObject2d::SetColar(m_col);

		if (m_DesTimar <= 0)
		{
			Uninit();
			return;
		}
	}
	//if (m_Move)
	//{
	//	m_Speed += (0.0f - m_Speed)* 0.5f;//�i�ړI�̒l-���݂̒l�j�������W��

	//	SetTex(PositionVec4(
	//		0.1f*m_MyNumber, 0.1f*m_MyNumber + 0.1f, 0.0f + m_Speed, 1.0f + m_Speed));
	//}
}

//-----------------------------------------------------------------------------
// �`��֐�
//-----------------------------------------------------------------------------
void CNumber::Draw()
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

//-----------------------------------------------------------------------------
// �����֐�
//-----------------------------------------------------------------------------
CNumber *CNumber::Create()
{
	CNumber * pObject = nullptr;
	pObject = new CNumber(PRIORITY_OBJECT);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//-----------------------------------------------------------------------------
// �����܂ł̎��Ԑݒ�֐�
//-----------------------------------------------------------------------------
void CNumber::Releasetimer(int nTimar)
{
	m_DesTimar = nTimar;
	m_DesTimarMax = m_DesTimar;
	m_isRelease = true;
}

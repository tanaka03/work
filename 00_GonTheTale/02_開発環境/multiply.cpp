//============================
//
// �{��//����͊J�������ɂ��������s��
// Author:hamada ryuuga
//
//============================

#include "multiply.h"
#include "number.h"
#include "utility.h"
#include "game.h"

int CMultiply::m_Rate;
int CMultiply::m_RateWait;
bool CMultiply::m_Decrease;

//=============================================================================
// �Z�b�g�֐�
//=============================================================================
void CMultiply::set(int Number, D3DXVECTOR3 Pos, bool extinction, bool b3D)
{
	int aPosTexU[100];
	int nModScore = Number;
	int nDigits;

	nDigits = (int)log10f((float)nModScore);

	for (int i = nDigits; i >= 0; i--)
	{
		
		aPosTexU[i] = (nModScore % 10);
		nModScore /= 10;
	}
	D3DXVECTOR3 ratiopos = Pos;

	if (b3D)
	{	
	ratiopos = ScreenCastWorld(&ratiopos,			// �X�N���[�����W
		D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));									// �X�N���[���T�C�Y
	
	}
	ratiopos += D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	for (int nCntScore = 0; nCntScore <= nDigits; nCntScore++)
	{
		
  		ratio[nCntScore]->SetPos(ratiopos);
		ratiopos += D3DXVECTOR3(50.0f, 0.0f, 0.0f);
		ratio[nCntScore]->SetSize(D3DXVECTOR3(30.0f, 30.0f, 0.0f));
		ratio[nCntScore]->SetNumber(aPosTexU[nCntScore]);
		ratio[nCntScore]->SetMove(false);
		ratio[nCntScore]->SetTex(PositionVec4(
			0.1f*aPosTexU[nCntScore], 0.1f*aPosTexU[nCntScore] + 0.1f, 0.0f, 1.0f));

		if (extinction)
		{
			ratio[nCntScore]->Releasetimer(90);
		}
	}
 	
}


//=============================================================================
// ������\������֐�
//=============================================================================
CMultiply* CMultiply::Create(int Number, D3DXVECTOR3 Pos, bool extinction,bool b3D)
{
	CMultiply * pObject = new CMultiply;

	if (pObject != nullptr)
	{
		for (int nCntScore = 0; nCntScore < 3; nCntScore++)
		{
		
 			pObject->ratio[nCntScore] = CNumber::Create();
			
		}
		pObject->set(Number, Pos, extinction, b3D);
	}

	return pObject;
}


//=============================================================================
// �X�R�A��\������֐�
//=============================================================================
void CMultiply::SetRate(int Rete)
{
	if (m_Rate <= 256)
	{
		m_RateWait = 6000;
		m_Decrease = false;
		m_Rate = Rete;
		set(m_Rate, D3DXVECTOR3(150.0f, 200.0f, 0.0f), false,false);
	}
}

CMultiply::CMultiply()
{
}

CMultiply::~CMultiply()
{
}

//=============================================================================
// �j���֐�
//=============================================================================
void CMultiply::Uninit()
{
}

//=============================================================================
// �X�V�֐�
//=============================================================================
void CMultiply::Update()
{
	if (m_Rate > 0)
	{
		m_RateWait--;
	
		if (m_RateWait <= 0)
		{

			m_Decrease = false;
			m_Rate--;
			if (m_Rate <= 0)
			{
				m_Rate = 0;
			}
			//CGame::GetMultiply()->set(m_Rate, D3DXVECTOR3(150.0f, 200.0f, 0.0f), false,false);
		}
	}

}

//============================
//
// �U���ݒ�
// Author:hamada ryuuga
//
//============================

#include "reaction.h"
#include "utility.h"
#include "popui.h"
#include "game.h"
#include "player.h"
#include "input.h"
#include "attack.h"
#include "text.h"
#include "score.h"
#include "3dpolygonbase.h"
#include "arealine.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CReaction::CReaction() :CObject(PRIORITY_BG)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CReaction::~CReaction()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CReaction::Init()
{
	m_area[0] = CArealine::Create();
	m_area[1] = CArealine::Create();
	m_area[2] = CArealine::Create();
	m_area[3] = CArealine::Create();

	AreaSize(D3DXVECTOR3(0.0f, -50.0f, 0.0f), D3DXVECTOR2(1000.0f,200.0f));

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CReaction::Uninit()
{
	CObject::Release();
}

//------------------------------------
// �X�V
//------------------------------------
void CReaction::Update()
{
	



}

//------------------------------------
// �`��
//------------------------------------
void CReaction::Draw()
{

}

//------------------------------------
// create
//------------------------------------
CReaction *CReaction::Create()
{
	CReaction * pObject = new CReaction;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}

//------------------------------------
//�������̃T�C�Y�ς���
//------------------------------------
void CReaction::AreaSize(D3DXVECTOR3 Pos, D3DXVECTOR2 Size)
{
	float SizeX = Size.x*0.5f;
	float SizeY = Size.y*0.5f;
	float wide = 5.0f;
	m_area[0]->SetSizeMove(D3DXVECTOR3(SizeX, wide, 0.0f));
	m_area[1]->SetSizeMove(D3DXVECTOR3(SizeX, wide, 0.0f));
	m_area[2]->SetSizeMove(D3DXVECTOR3(wide, SizeY, 0.0f));
	m_area[3]->SetSizeMove(D3DXVECTOR3(wide, SizeY, 0.0f));

	m_area[0]->SetDifferenceMove(D3DXVECTOR3(Pos.x- wide, Pos.y + SizeY, Pos.z));
	m_area[1]->SetDifferenceMove(D3DXVECTOR3(Pos.x+ wide, Pos.y - SizeY, Pos.z));
	m_area[2]->SetDifferenceMove(D3DXVECTOR3(Pos.x- SizeX, Pos.y- wide, Pos.z));
	m_area[3]->SetDifferenceMove(D3DXVECTOR3(Pos.x+ SizeX, Pos.y+ wide, Pos.z));

}



//=============================================================================
//
// ���_�A�C�e��
// Author:hamada ryuuga
//
//=============================================================================

#include "bell.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"
#include "score.h"
#include "shadow.h"
#include "manager.h"
#include "sound.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CBell::CBell()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CBell::~CBell()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CBell::Init()
{
	CBuilding::Init();

	const char* Model = "data\\MODEL\\Bell\\suzu.x";
	SetModel(Model);
	m_hit = false;
	m_isMove = false;
	Shadow = CShadow::Create(GetPos());
	D3DXVECTOR3 Pos = CGame::GetStage()->GetPlayerHitMesh(GetPos(), GetPos(), true, Shadow);
	Shadow->SetPos(Pos);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CBell::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CBell::Update()
{
	CObjectX::Update();

	// ����
	Move();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CBell::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CBell *CBell::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBell *pBell = nullptr;

	pBell = new CBell;

	if (pBell != nullptr)
	{
		pBell->SetPos(pos);
		pBell->SetRot(rot);
		pBell->SetFileName("bell");
		pBell->Init();
	}

	return pBell;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CBell::Move()
{

}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CBell::Hit()
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_COIN);
	CGame::GetStage()->GetScore()->Add(100);
	Shadow->Release();
	Uninit();
}
//--------------------------------------------------
// �������ĂȂ��Ƃ��̔���
//--------------------------------------------------
void CBell::NotHit()
{
	m_hit = false;
}



//=============================================================================
//
// ���[��
// Author:hamada ryuuga
//
//=============================================================================

#include "sprint.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"
#include "sound.h"
#include "manager.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CSprint::CSprint()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CSprint::~CSprint()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CSprint::Init()
{
	CBuilding::Init();

	const char* Model = "data/MODEL/baneAll.x";
	SetModel(Model);
	m_hit = false;
	m_isMove = false;
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CSprint::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CSprint::Update()
{
	CObjectX::Update();

	// ����
	Move();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CSprint::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CSprint *CSprint::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CSprint *pPendulum = nullptr;

	pPendulum = new CSprint;

	if (pPendulum != nullptr)
	{
		pPendulum->SetPos(pos);
		pPendulum->SetRot(rot);
		pPendulum->SetFileName("dash");
		pPendulum->Init();
	}

	return pPendulum;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CSprint::Move()
{
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CSprint::Hit()
{
	D3DXVECTOR3 centerPos = CGame::GetStage()->GetPlayer()->GetPos();
	D3DXVECTOR3 centerMove(0.0f,100.0f,0.0f);
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X
	CGame::GetStage()->GetPlayer()->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BANE);

	D3DXMatrixRotationYawPitchRoll(&mtx, GetRot().y, GetRot().x, GetRot().z);
	D3DXVec3TransformCoord(&centerMove, &centerMove, &mtx);
	CGame::GetStage()->GetPlayer()->SetMoveDash(centerMove);
}
//--------------------------------------------------
// �������ĂȂ��Ƃ��̔���
//--------------------------------------------------
void CSprint::NotHit()
{
	m_hit = false;
}



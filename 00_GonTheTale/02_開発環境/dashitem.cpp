//=============================================================================
//
// �����A�C�e��
// Author:hamada ryuuga
//
//=============================================================================

#include "dashitem.h"
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
CDashitem::CDashitem()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CDashitem::~CDashitem()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CDashitem::Init()
{
	CBuilding::Init();

	const char* Model = "data/MODEL/Dashitem.x";
	SetModel(Model);
	m_scale = 1.0f;
	m_hit = false;
	m_isScale = false;
	m_isMove = false;
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CDashitem::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CDashitem::Update()
{
	CObjectX::Update();

	// ����
	Move();

	if (m_isScale)
	{
		m_scale -= 0.1f;
		SetScale({ m_scale ,m_scale,m_scale });
		if (m_scale <= 0.0f)
		{
			Uninit();
		}
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CDashitem::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CDashitem *CDashitem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CDashitem *pPendulum = nullptr;

	pPendulum = new CDashitem;

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
void CDashitem::Move()
{

}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CDashitem::Hit()
{
	D3DXVECTOR3 centerPos = CGame::GetStage()->GetPlayer()->GetPos();

	D3DXVECTOR3 centerMove(0.0f, 0.0f, 150.0f);
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

	//
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DASH);
	m_isScale = true;
	//CGame::GetStage()->GetPlayer()->SetGravity(false);
	D3DXMatrixRotationYawPitchRoll(&mtx, GetRot().y, GetRot().x, GetRot().z);
	D3DXVec3TransformCoord(&centerMove, &centerMove, &mtx);
	CGame::GetStage()->GetPlayer()->SetMoveDash(centerMove);
}
//--------------------------------------------------
// �������ĂȂ��Ƃ��̔���
//--------------------------------------------------
void CDashitem::NotHit()
{
	m_hit = false;
}



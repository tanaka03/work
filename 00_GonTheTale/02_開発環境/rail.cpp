//=============================================================================
//
// ���[��
// Author:hamada ryuuga
//
//=============================================================================

#include "rail.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CRail::CRail()
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CRail::~CRail()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CRail::Init()
{
	CBuilding::Init();

	const char* Model = "data/MODEL/reil.x";
	SetModel(Model);
	m_hit = false;
	m_isMove = false;
	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CRail::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CRail::Update()
{
	CObjectX::Update();

	// ����
	Move();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CRail::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CRail *CRail::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CRail *pPendulum = nullptr;

	pPendulum = new CRail;

	if (pPendulum != nullptr)
	{
		pPendulum->SetPos(pos);
		pPendulum->SetRot(rot);
		pPendulum->SetFileName("Rail");
		pPendulum->Init();
	}

	return pPendulum;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CRail::Move()
{
	
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CRail::Hit()
{

	D3DXMATRIX mtx;
	
	D3DXVECTOR3 centerPos = CGame::GetStage()->GetPlayer()->GetPos();

	D3DXVECTOR3 min = CObjectX::GetVtxMin();
	D3DXVECTOR3 max = CObjectX::GetVtxMax();


	mtx = *hmd::giftmtx(&mtx, GetPos(), GetRot());

	D3DXVECTOR3 PopPos(D3DXVECTOR3(mtx._41, mtx._42, mtx._43));

	D3DXVECTOR3 maxMove = (max+ PopPos) - centerPos;
	D3DXVECTOR3 minMove = (min+ PopPos) - centerPos;

	float MaxLength = D3DXVec3Length(&maxMove);
	float MinLength = D3DXVec3Length(&minMove);

	if (!m_hit)
	{//�ǂ��������ɐi�ނ�����m�F
		if (MaxLength < MinLength)
		{
			m_hit = true;
			m_isMove = false;
		}
		else
		{
			m_hit = true;
			m_isMove = true;
		}
	}
	else
	{//�m�F�ł����炻�̕����Ƀz�[�~���O����
		D3DXVECTOR3 centerPosOld = CGame::GetStage()->GetPlayer()->GetPosOld();

		if (m_isMove)
		{
			Homing(&centerPos, centerPos, D3DXVECTOR3(PopPos.x, max.y / 2, PopPos.z + max.z*1.5f), 10);

			CGame::GetStage()->GetPlayer()->SetPos(centerPos);
		}
		else
		{
			Homing(&centerPos, centerPos, D3DXVECTOR3(PopPos.x, max.y / 2, PopPos.z + min.z*1.5f), 10);

			CGame::GetStage()->GetPlayer()->SetPos(centerPos);
		}
	}
}
//--------------------------------------------------
// �������ĂȂ��Ƃ��̔���
//--------------------------------------------------
void CRail::NotHit()
{
	m_hit = false;
}
	


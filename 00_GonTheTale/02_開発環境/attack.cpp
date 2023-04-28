//============================
//
// �U���_
// Author:hamada ryuuga
//
//============================

#include "attack.h"
#include "hamada.h"
#include "manager.h"
#include "player.h"
#include "game.h"
//------------------------------------
// �R���X�g���N�^
//------------------------------------
CAttack::CAttack(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CAttack::~CAttack()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CAttack::Init()
{
	C3dpolygon::Init();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	Size(50.0f, 50.0f, 50.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetSize(Size);
	SetTexture(CTexture::TEXTURE_NONE);//�e�N�X�`���I��
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//���W�ݒ�
	SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�F�ݒ�
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//move�̐ݒ�
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CAttack::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CAttack::Update()
{
	CPlayer*Player = CGame::GetPlayer();
	D3DXVECTOR3 Pos = *Player->GetPos();
	D3DXVECTOR3 Size = { CPlayer::WIDTH,CPlayer::WIDTH,CPlayer::WIDTH };
	
	if (CAttack::collision(Pos, Size))
	{
		Player->DamageHit(1);
	}


	//����
	CAttack::move();

	C3dpolygon::Update();

}

//------------------------------------
// �`��
//------------------------------------
void CAttack::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//�y���ŉ�]���܂����Ȃ݂�m_rot�����ƃO���O�����܂�
	//m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);
	C3dpolygon::Draw();

	//���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CAttack *CAttack::Create()
{
	CAttack * pObject = nullptr;
	pObject = new CAttack(PRIORITY_OBJECT);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CAttack::GetPos() const
{
	return &m_pos;
}

void CAttack::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

//------------------------------------
// �����n��
//------------------------------------
void CAttack::move()
{
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	m_pos += m_move;
}

//------------------------------------
// �����蔻��
//------------------------------------
bool CAttack::collision(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 EnemySize)
{
	//�����蔻��
	if (((m_pos.y - m_size.y) <= (PlayerPos.y + EnemySize.y)) &&
		((m_pos.y + m_size.y) >= (PlayerPos.y - EnemySize.y)) &&
		((m_pos.x - m_size.x) <= (PlayerPos.x + EnemySize.x)) &&
		((m_pos.x + m_size.x) >= (PlayerPos.x - EnemySize.x)) &&
		m_bCollision)
	{

		return true;
	}
	return false;
}


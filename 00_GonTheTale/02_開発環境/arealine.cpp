//============================
//
//�U���͈͐ݒ�
// Author:hamada ryuuga
//
//============================

#include "arealine.h"
#include "hamada.h"
#include "manager.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CArealine::CArealine(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CArealine::~CArealine()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CArealine::Init()
{

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CArealine::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CArealine::Update()
{

	//����
	CArealine::move();

	C3dpolygon::Update();

}

//------------------------------------
// �`��
//------------------------------------
void CArealine::Draw()
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
CArealine *CArealine::Create()
{
	CArealine * pObject = nullptr;
	pObject = new CArealine(PRIORITY_BG);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_NONE);//�e�N�X�`���I��
		pObject->SetSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//�T�C�Y�ݒ�
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//���W�ݒ�
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�F�ݒ�
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//move�̐ݒ�

		//������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CArealine::GetPos() const
{
	return &m_pos;
}

void CArealine::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}
//------------------------------------
//���W�̍���������� 
//------------------------------------
void CArealine::SetDifferenceMove(D3DXVECTOR3 move)
{
	m_move = move-m_pos;
}

//------------------------------------
//�T�C�Y�̍���������� 
//------------------------------------
void CArealine::SetSizeMove(D3DXVECTOR3 move)
{
	m_SizeMove = move-m_size;
}

//------------------------------------
// �����n��
//------------------------------------
void CArealine::move()
{
	m_SizeMove.x += (0.0f - m_SizeMove.x) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_SizeMove.y += (0.0f - m_SizeMove.y) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_SizeMove.z += (0.0f - m_SizeMove.z) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��

	m_size += m_SizeMove;
	SetSize(m_size);
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	m_move.x += (0.0f - m_move.x) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.y += (0.0f - m_move.y) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_move.z += (0.0f - m_move.z) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_pos += m_move;
}


//============================
//
// �����Ȃ��RD��object�ݒ�
// Author:hamada ryuuga
//
//============================

#include "3dpolygonbase.h"
#include "hamada.h"
#include "manager.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
C3dbase::C3dbase(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
C3dbase::~C3dbase()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT C3dbase::Init()
{

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void C3dbase::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void C3dbase::Update()
{

	//����
	C3dbase::move();

	C3dpolygon::Update();

}

//------------------------------------
// �`��
//------------------------------------
void C3dbase::Draw()
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
C3dbase *C3dbase::Create()
{
	C3dbase * pObject = nullptr;
	pObject = new C3dbase(PRIORITY_BG);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_NONE);//�e�N�X�`���I��
		pObject->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));//�T�C�Y�ݒ�
		pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//���W�ݒ�
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//�F�ݒ�
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//move�̐ݒ�

		//������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * C3dbase::GetPos() const
{
	return &m_pos;
}

void C3dbase::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}


//------------------------------------
//�T�C�Y�̍���������� 
//------------------------------------
void C3dbase::SetSizeMove(D3DXVECTOR3 move)
{
	m_SizeMove = move - m_size;
}

//------------------------------------
// �����n��
//------------------------------------
void C3dbase::move()
{
	m_SizeMove.x += (0.0f - m_SizeMove.x) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_SizeMove.y += (0.0f - m_SizeMove.y) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��
	m_SizeMove.z += (0.0f - m_SizeMove.z) * Decrease;	//�i�ړI�̒l-���݂̒l�j�������W��

	m_size += m_SizeMove;

	SetSize(m_size);
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����

	m_pos += m_move;
}


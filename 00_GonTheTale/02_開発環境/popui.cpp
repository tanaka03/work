//============================
//
// Ui�ݒ�
// Author:hamada ryuuga
//
//============================

#include "popui.h"
#include "hamada.h"
#include "manager.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CPopUi::CPopUi(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CPopUi::~CPopUi()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CPopUi::Init()
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
void CPopUi::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CPopUi::Update()
{

	//����
	CPopUi::move();

	C3dpolygon::Update();

}

//------------------------------------
// �`��
//------------------------------------
void CPopUi::Draw()
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
CPopUi *CPopUi::Create()
{
	CPopUi * pObject = nullptr;
	pObject = new CPopUi(PRIORITY_OBJECT);

	if (pObject != nullptr)
	{
		pObject->Init();
	

		//������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CPopUi::GetPos() const
{
	return &m_pos;
}

void CPopUi::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}



//------------------------------------
// �����n��
//------------------------------------
void CPopUi::move()
{
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����

	m_pos += m_move;
}
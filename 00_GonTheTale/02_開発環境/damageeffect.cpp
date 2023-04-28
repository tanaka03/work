//============================
//
// �G�t�F�N�g�ݒ�
// Author:hamada ryuuga
//
//============================

#include "damageeffect.h"
#include "hamada.h"
#include "manager.h"
#include "utility.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CDamageEffect::CDamageEffect(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CDamageEffect::~CDamageEffect()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CDamageEffect::Init()
{
	m_life = 100;

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CDamageEffect::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CDamageEffect::Update()
{

	//����
	CDamageEffect::move();

	C3dpolygon::Update();

}

//------------------------------------
// �`��
//------------------------------------
void CDamageEffect::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//�A���t�@�u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


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
CDamageEffect *CDamageEffect::Create(D3DXVECTOR3 Move)
{
	CDamageEffect * pObject = nullptr;
	pObject = new CDamageEffect(PRIORITY_POPEFFECT);

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_ATTACK);//�e�N�X�`���I��
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));//�T�C�Y�ݒ�
		pObject->SetPos(D3DXVECTOR3(0.0f, 150.0f, 0.0f));//���W�ݒ�
		pObject->SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));//�F�ݒ�
		if (Move.y <= 0.0f) 
		{
			Move.y = -Move.y;
		}
		//pObject->SetMove(D3DXVECTOR3(Move.x, Move.y, Move.z));//move�̐ݒ�
		//pObject->SetLife(IntRandom(130, 10));
		//������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		pObject->SetAnimation(5, 1, 5, 0, false);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��
	}

	return pObject;
}

//------------------------------------
// �����n��
//------------------------------------
void CDamageEffect::move()
{
	//m_pos += m_move;
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	m_life--;
	
	if (m_life <= 0)
	{
		Uninit();
	}
	
	
}


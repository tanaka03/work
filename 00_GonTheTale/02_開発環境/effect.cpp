//============================
//
// �G�t�F�N�g�ݒ�
// Author:hamada ryuuga
//
//============================

#include "effect.h"
#include "hamada.h"
#include "manager.h"
#include "utility.h"


//------------------------------------
// �R���X�g���N�^
//------------------------------------
CEffect::CEffect(int list) :C3dpolygon(list)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CEffect::~CEffect()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CEffect::Init()
{
	m_life = 100;

	C3dpolygon::Init();
	return E_NOTIMPL;
}

//------------------------------------
// �I��
//------------------------------------
void CEffect::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CEffect::Update()
{

	//����
	CEffect::move();

	C3dpolygon::Update();

}

//------------------------------------
// �`��
//------------------------------------
void CEffect::Draw()
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
CEffect *CEffect::Create(D3DXVECTOR3 Move)
{
	CEffect * pObject = nullptr;
	pObject = new CEffect(PRIORITY_POPEFFECT);

	if (pObject != nullptr)
	{
		float Mode= FloatRandom(10, 1);
		float Speed = FloatRandom(3, 0);
		pObject->Init();
		pObject->SetTexture(CTexture::TEXTURE_NONE);//�e�N�X�`���I��
		pObject->SetSize(D3DXVECTOR3(10.0f, 2.0f*10.0f, 0.0f));//�T�C�Y�ݒ�
		//pObject->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//���W�ݒ�
		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�F�ݒ�
		if (Move.y <= 0.0f) 
		{
			Move.y = -Move.y;
		}
		pObject->SetMove(D3DXVECTOR3(Move.x, Move.y, Move.z));//move�̐ݒ�
		pObject->SetLife(IntRandom(130, 10));
		//������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		//pObject->SetAnimation(7, 1, 0, 0, false);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��
	}

	return pObject;
}

//------------------------------------
// Get��Set 
//------------------------------------
const D3DXVECTOR3 * CEffect::GetPos() const
{
	return &m_pos;
}

void CEffect::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}
//------------------------------------
// �����n��
//------------------------------------
void CEffect::move()
{
	m_pos += m_move;
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	m_life--;
	
	if (m_life <= 0)
	{
		Uninit();
	}
	
	
}


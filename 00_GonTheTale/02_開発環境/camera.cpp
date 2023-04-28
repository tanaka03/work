//=============================================================================
//
// �J�����ݒ�
// Author:hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "camera.h"
#include "input.h"

#include "manager.h"
#include "player.h"

#include "title.h"
#include "game.h"
#include "utility.h"
#include "object.h"

//-----------------------------------------------------------------------------
// �萔
//-----------------------------------------------------------------------------
const D3DXVECTOR3 CCamera::INIT_POSV(0.0f, 0.0f, -750.0f);	// �ʒu�̏����ʒu
const float CCamera::MOVE_ATTENUATION = 0.1f;	// �����W��
const float CCamera::MOVE_ANGLE = 10.0f;	// �����W��
const float CCamera::FIELD_OF_VIEW = 45.0f;	// ����p
const float CCamera::NEAR_VALUE = 10.0f;	// �j�A
const float CCamera::FUR_VALUE = 100000.0f;	// �t�@�[

//-----------------------------------------------------------------------------
// �R���X�g���N�g
//-----------------------------------------------------------------------------
CCamera::CCamera()
{
	
}

//-----------------------------------------------------------------------------
// �f�X�g���N�g
//-----------------------------------------------------------------------------
CCamera::~CCamera()
{
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void CCamera::Init(void)
{
	m_isFree = false;
	m_isAnimation = false;
	m_isLoop = false;
	m_bossEnd = false;
	m_nouAnimation = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//���_�@�����_�@������@�ݒ�
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_directionR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_isFrameCount = 0;
	m_isShakePow = 0.0f;

}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CCamera::Update(void)
{
	
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CCamera::Set(int Type)
{
	m_type = Type;
	LPDIRECT3DDEVICE9  pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//�f�o�C�X�̃|�C���^

	//�r���[�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxView);
	D3DXVECTOR3 RandomMove = {0.0f,0.0f,0.0f};

	if (m_isFrameCount >= 0)
	{
		m_isFrameCount--;
		RandomMove.x = FloatRandom(m_isShakePow, -m_isShakePow);
		RandomMove.y = FloatRandom(m_isShakePow, -m_isShakePow);
		RandomMove.z = FloatRandom(m_isShakePow, -m_isShakePow);
	}

	//�r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&(m_posV+RandomMove),
		&(m_posR+RandomMove),
		&m_vecU);

	//�K�p
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//�v���W�F�N�V�����}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxProje);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
	D3DXMatrixOrthoLH(&m_mtxProje,					// �v���W�F�N�V�����}�g���b�N�X
		(float)SCREEN_WIDTH,								// ��
		(float)SCREEN_HEIGHT,								// ����
		0.0f,											// �j�A
		2000.0f);	

//else
//{
//	// �v���W�F�N�V�����}�g���b�N�X�̍쐬(���s���e)
//	D3DXMatrixOrthoLH(&m_MtxProje,					// �v���W�F�N�V�����}�g���b�N�X
//		(float)SCREEN_WIDTH,								// ��
//		(float)SCREEN_HEIGHT,								// ����
//		-100.0f,											// �j�A
//		2000.0f);											// �t�@�[
//}
//�K�p
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProje);
}

//-----------------------------------------------------------------------------
//	Animation�̍Đ�����
//-----------------------------------------------------------------------------
void CCamera::PlayAnimation(int Animation, bool Isloop)
{	
	m_nouAnimation = Animation;
	m_isAnimation = true;
	m_isLoop = Isloop;
	
}



//-----------------------------------------------------------------------------
//�J��������炷��ݒ�
//-----------------------------------------------------------------------------
void CCamera::ShakeCamera(int IsFrameCount, float IsShakePow)
{
	m_isFrameCount = IsFrameCount;
	m_isShakePow = IsShakePow;
}

//==================================================
// ball.cpp
// Author:hamada
//==================================================
#include"ball.h"
#include "input.h"

//**************************************************
// �}�N����`
//**************************************************
#define SPEED	(15.0f)
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CBall::CBall()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CBall::~CBall()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CBall::Init()
{
	CBuilding::Init();

	// ���f���̐ݒ�
	const char* Model = "data/MODEL/ball.x";
	SetModel(Model);

	// �ʒu�̐ݒ�
	if (m_nRotType == 0)
	{
		m_Pos = { m_centerPos.x - m_fRadius ,m_centerPos.y,m_centerPos.z };
	}
	else
	{
		m_Pos = { m_centerPos.x + m_fRadius ,m_centerPos.y,m_centerPos.z };
	}

	return	S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CBall::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CBall::Update()
{


	CObjectX::Update();

	// �ړ�
	Move();

	//SetPos(m_Pos);
	//SetRot(m_Rot);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CBall::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CBall *CBall::Create(D3DXVECTOR3 centerpos, float radius, float rotspeed, int rotType)
{
	CBall *pBall = nullptr;

	pBall = new CBall;

	if (pBall != nullptr)
	{
		pBall->SetCenterPos(centerpos);
		pBall->SetRadius(radius);
		pBall->SetRotSpeed(rotspeed);
		pBall->SetRotType(rotType);
		pBall->SetFileName("Ball");
		pBall->SetQuat(true);
		pBall->Init();
		pBall->SetPos(centerpos);
	}

	return pBall;
}

//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void CBall::Move()
{
	// �C���v�b�g
	CInput *CInputpInput = CInput::GetKey();

	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 rot = GetRot();

	if ((vec.x == 0.0f) && (vec.z == 0.0f))
	{
		if (CInputpInput->Press(CInput::KEY_RIGHT))
		{
			vec.x += 1.0f;
		}
		if (CInputpInput->Press(CInput::KEY_LEFT))
		{
			vec.x += -1.0f;
		}
		if (CInputpInput->Press(CInput::KEY_UP))
		{

			vec.z += 1.0f;
		}
		if (CInputpInput->Press(CInput::KEY_DOWN))
		{
			vec.z += -1.0f;
		}
	}

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 maxVtx = GetVtxMax();
	D3DXVECTOR3 rotate;

	if (vec.x != 0.0f || vec.z != 0.0f)
	{// �ړ��Ƃ���ɍ��킹����]
	 // �x�N�g���̐��K��
		D3DXVec3Normalize(&vec, &vec);
		// �L�[�{�[�h
		pos += vec * SPEED;

		// �ړ��ʂɑ΂��Ẳ�]�������߂�iz���j
		rotate.z = vec.x * SPEED / maxVtx.x;
		rot.z += -rotate.z;

		// �ړ��ʂɑ΂��Ẳ�]�������߂�ix���j
		rotate.x = vec.z * SPEED / maxVtx.z;
		rot.x += rotate.x;

		rot = RotNormalization(rot);

		SetPos(pos);
		SetRot(rot);
		
		/*float fLength = D3DXVec3Length(&rotate);*/

		//X = Z, Z= -X
		D3DXVECTOR3 axis;    // ��]��
		D3DXVECTOR3 inverseVec = -(vec);        // move�l�𔽑΂ɂ���
		D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&axis, &inverseVec, &vecY);    // �O�ςŉ�]�����Z�o�B

													 // �N�I�[�^�j�I���̌v�Z
		D3DXQUATERNION quaternion;
		D3DXQuaternionRotationAxis(&quaternion, &axis, 0.05f);    // ��]���Ɖ�]�p�x���w��

		// �N�I�[�^�j�I����K�p
		m_quat *= quaternion;


		D3DXQuaternionNormalize(&m_quat, &m_quat);
	}
}

//--------------------------------------------------
// �N�I�[�^�j�I��
//--------------------------------------------------
void CBall::quat()
{
	D3DXMATRIX mtx = GetWorldMtx();
	D3DXMATRIX mtxRot;

	// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
	D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quat);            // �N�I�[�^�j�I���ɂ��s���]
	D3DXMatrixMultiply(&mtx, &mtx, &m_mtxRot);    // �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	SetWorldMtx(mtx);

}
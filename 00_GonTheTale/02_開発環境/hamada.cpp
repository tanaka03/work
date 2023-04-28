//=============================================================================
//
// �֗��֐�
// Author : �l�c����
//
//=============================================================================

#include "hamada.h"
#include "manager.h"
#include "renderer.h"
namespace hmd
{
	D3DXMATRIX *giftmtx(D3DXMATRIX *pOut,D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool Billboard);
	D3DXMATRIX *giftmtxQuat(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXQUATERNION Quat, bool Billboard);
	float easeInSine(float X);
	float easeInQuad(float X);
	bool is_sjis_lead_byte(int c);
}

///=============================================================================
//�}�g���b�N�X����]��������
//=============================================================================
D3DXMATRIX *hmd::giftmtx(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool Billboard)
{
	// TODO: �֐�������
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(pOut);


	if (Billboard)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�y���ŉ�]���܂����Ȃ݂�m_rot�����ƃO���O�����܂�
		pOut->_11 = mtxView._11;
		pOut->_12 = mtxView._21;
		pOut->_13 = mtxView._31;
		pOut->_31 = mtxView._13;
		pOut->_32 = mtxView._23;
		pOut->_33 = mtxView._33;

	}

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.x, rot.y, rot.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);
	return pOut;
}

///=============================================================================
//�}�g���b�N�X����]��������
//=============================================================================
D3DXMATRIX *hmd::giftmtxQuat(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXQUATERNION Quat, bool Billboard)
{
	// TODO: �֐�������
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(pOut);


	if (Billboard)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//�y���ŉ�]���܂����Ȃ݂�m_rot�����ƃO���O�����܂�
		pOut->_11 = mtxView._11;
		pOut->_12 = mtxView._21;
		pOut->_13 = mtxView._31;
		pOut->_31 = mtxView._13;
		pOut->_32 = mtxView._23;
		pOut->_33 = mtxView._33;

	}

	// �N�H�[�^�j�I���̎g�p�����p���̐ݒ�
	D3DXMatrixRotationQuaternion(&mtxRot, &Quat);            // �N�I�[�^�j�I���ɂ��s���]
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);    // �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);
	return pOut;
}

//
//�C�[�W���O
//
float hmd::easeInSine(float X)
{
	return 1 - cos((X * D3DX_PI) / 2);
}

float hmd::easeInQuad(float X)
{
	return X * X;
}

//=============================================================================
//1�o�C�g�������V�t�gJIS���ǂ������肷��֐�
//=============================================================================
bool hmd::is_sjis_lead_byte(int c)
{
	return (((c & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}
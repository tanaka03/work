//============================
//
// �����ݒ�
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "words.h"

#include "manager.h"
#
#include "object.h"
#include "font.h"

//------------------------------------
// �R���X�g���N�^
//------------------------------------
CWords::CWords(int list) :CObject(3)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CWords::~CWords()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CWords::Init(void)
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_moveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D*pVtx;		//���_���ւ̃|�C���^

						//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//- 
	// ���_���̐ݒ�
	//-
	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x, m_pos.y, 0.0f);


	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);


	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	

	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CWords::Uninit(void)
{
	//if (m_pTex != nullptr)
	//{
	//	m_pTex->Release();
	//	m_pTex = nullptr;
	//}

	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	Release();

}

//------------------------------------
// �X�V
//------------------------------------
void CWords::Update(void)
{
	m_rot.z += m_moveRot.z;

	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	D3DXVECTOR3 addPos[4];
	D3DXMATRIX mtx;	// �v�Z�p�}�g���b�N�X

					//�}�g���b�N�X�쐬
	D3DXMatrixIdentity(&mtx);
	D3DXMatrixRotationYawPitchRoll(&mtx, 0.0f, 0.0f, m_rot.z);
	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		D3DXVec3TransformCoord(&addPos[i], &m_Vtx[i], &mtx);

		pVtx[i].pos.x = m_pos.x + (addPos[i].x * m_size.x);//<-�T�C�Y�ύX
		pVtx[i].pos.y = m_pos.y + (addPos[i].y * m_size.y);//<-�T�C�Y�ύX
		pVtx[i].pos.z = 0.0f;
	}

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();


	//������move�������
	m_pos += m_move;
}

//------------------------------------
// �`��
//------------------------------------
void CWords::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;        //�f�o�C�X�ւ̃|�C���^

									  //�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);

	//�|���S���̕`��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);
	//�v���~�e�B�u(�|���S��)��
	pDevice->SetTexture(0, NULL);

}

//------------------------------------
// create
//------------------------------------
CWords *CWords::Create(const char*Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type)
{
	CWords * pObject = nullptr;
	pObject = new CWords;

	if (pObject != nullptr)
	{
	
		pObject->SetPos(pos);
		pObject->SetSize(Size);
		pObject->Init();
		pObject->Setwords(Text, Type);

	}
	return pObject;
}

//=============================================================================
// GetPos�֐�
//=============================================================================
void CWords::Setwords(const char*Text, CFont::FONT Type)
{
	std::string Txt = Text;
	if (Txt != "")
	{
		m_pTex = CManager::GetInstance()->GetFont()->GetFont(Text, Type);
	}
	else
	{
		m_pTex = nullptr;
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	}
}


//=============================================================================
// GetPos�֐�
//=============================================================================
const D3DXVECTOR3 * CWords::GetPos() const
{
	return &m_pos;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CWords::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}
//=============================================================================
// SetPos�֐�
//=============================================================================
void CWords::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//===========================================================================
//�Z�b�g�J���[
//=============================================================================
void CWords::SetColar(D3DXCOLOR Collar)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[1].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[2].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);
	pVtx[3].col = D3DXCOLOR(Collar.r, Collar.g, Collar.b, Collar.a);

	m_col = Collar;
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}
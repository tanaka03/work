//============================
//
// ���C���ݒ�
// Author:hamada ryuuga
//
//============================
#include "line.h"
#include "camera.h"
#include "manager.h"


CLine::CLine(int nPriority) : CObject(nPriority)
{

}
CLine::~CLine()
{

}

//=========================================
// ����������
//=========================================
HRESULT CLine::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D* pVtx = NULL;
	//�J�����̃f�[�^�擾

	// ���_���W�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ����������
	m_Line.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���_���W
	m_Line.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]���W

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=========================================
// �I������
//=========================================
void  CLine::Uninit(void)
{
	// ���_�o�b�t�@�[�̉��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	CObject::Release();
}

//=========================================
// �X�V����
//=========================================
void  CLine::Update(void)
{
}

//=========================================
// �`�揈��
//=========================================
void  CLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxView;
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	DWORD Test = 0;

	pDevice->GetRenderState(D3DRS_ALPHAFUNC, &Test);//���傫��

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
	// ���[���h�}�g���b�N�X�̏�����
	// �s�񏉊����֐�(��1�����̍s���P�ʍs��ɏ�����)
	D3DXMatrixIdentity(&m_Line.mtxWorld);

	//�r���{�[�h�̐ݒ�
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	// �ʒu�𔽉f
	// �s��ړ��֐�(��P������X,Y,Z�����̈ړ��s����쐬)
	D3DXMatrixTranslation(&mtxTrans, m_Line.pos.x, m_Line.pos.y, m_Line.pos.z);
	// �s��|���Z�֐�(��2�����~��3��������P�����Ɋi�[)
	D3DXMatrixMultiply(&m_Line.mtxWorld, &m_Line.mtxWorld, &mtxTrans);

	//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Line.mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//���C�g�ݒ�false�ɂ���ƃ��C�g�ƐH���Ȃ�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	Uninit();
}

//----------------------------------
//�Z�b�g
//----------------------------------
void  CLine::SetLine(D3DXVECTOR3 Maxpos,D3DXVECTOR3 pos)//�ꏊ.��].�F.�^�C�v
{
	// ���_���W�����b�N
	VERTEX_3D*pVtx; //���_�ւ̃|�C���^
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = pos;
	pVtx[1].pos = Maxpos;
	pVtx[2].pos = D3DXVECTOR3(pos.x, 100.0f, pos.z); 
	pVtx[3].pos = D3DXVECTOR3(Maxpos.x, 100.0f, Maxpos.z);

	// ���_���W���A�����b�N
	m_pVtxBuff->Unlock();
}

//----------------------------------
//�Z�b�g
//----------------------------------
CLine * CLine::Create()
{
	CLine * pObject = nullptr;
	pObject = new CLine;

	if (pObject != nullptr)
	{
		pObject->Init();
	}
	return pObject;
}




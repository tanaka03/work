//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "3dpolygon.h"
#include "manager.h"
#include "input.h"
#include "utility.h"
#include "camera.h"
#include "hamada.h"

int C3dpolygon::m_MaxPolygon;
const D3DXVECTOR3 C3dpolygon::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, +1.0f, +1.0f),
	D3DXVECTOR3(+1.0f, +1.0f, +1.0f),
	D3DXVECTOR3(-1.0f, -1.0f, -1.0f),
	D3DXVECTOR3(+1.0f, -1.0f, -1.0f),
};

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
C3dpolygon::C3dpolygon(int list):CObject(list)
{
	
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
C3dpolygon::~C3dpolygon()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT C3dpolygon::Init()
{
	m_size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	m_nScale = 10.0f;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nTimer = 0;
	
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	m_texture = CTexture::TEXTURE_NONE;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,		//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);


	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//rhw�̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	m_CounterAnim = 0;
	m_PatternAnimX = 1;
	m_PatternAnimY = 1;

	m_DivisionX = 1;
	m_DivisionY = 1;
	m_DivisionMAX = m_DivisionX*m_DivisionY;

	m_animationSpeed = 0;
	m_AnimationSpeedCount = 0;

	m_Timar = 0;
	m_TimaCount = 0;
	m_OnAnimation = false;
	SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetSize(m_size);
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void C3dpolygon::Uninit()
{
	// �j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	Release();
}

//=============================================================================
// �|���S���̍X�V
//=============================================================================
void C3dpolygon::Update()
{
	m_nTimer++;


	m_MaxPolygon++;
	//m_pos.z = -0.01f*m_MaxPolygon;

	if (m_OnAnimation)
	{
		m_TimaCount++;

		if (m_TimaCount >= m_Timar)
		{
			m_AnimationSpeedCount++;
			if (m_AnimationSpeedCount >= m_animationSpeed)
			{
				m_AnimationSpeedCount = 0;
				m_PatternAnimX++;

				if (m_PatternAnimX > m_DivisionX)
				{//�A�j���[�V����
					m_PatternAnimX = 0;
					m_PatternAnimY++;
					if (m_PatternAnimY >= m_DivisionY)
					{
						m_PatternAnimY = 0;
						if (!m_Loop)
						{
							Uninit();
						}
						return;
					}
				}

				float U = 1.0f / (m_DivisionX);
				float V = 1.0f / (m_DivisionY);

				SetTex(PositionVec4(
					U * (m_PatternAnimX)
					, U *(m_PatternAnimX)+U
					, V * (m_PatternAnimY)
					, V * (m_PatternAnimY)+V));
				SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			}
		}
		else
		{
			SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void C3dpolygon::Draw()
{
	
	//�f�o�C�X�ւ̃|�C���^
	//�f�o�C�X�̎擾
 	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans, mtxView;													// �v�Z�p�}�g���b�N�X
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ���[���h���W�s��̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	
	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::GetInstance()->GetTexture()->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);						//�v���~�e�B�u(�|���S��)��

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	pDevice->SetTexture(0, NULL);
}




//=============================================================================
// create�֐�
//=============================================================================
C3dpolygon *C3dpolygon::Create(int list)
{
	C3dpolygon * pObject = nullptr;
	pObject = new C3dpolygon(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//=============================================================================
// GetPos�֐�
//=============================================================================
const D3DXVECTOR3 *C3dpolygon::GetPos() const
{
	return &m_pos;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void C3dpolygon::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	m_pos.z= pos.z;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void C3dpolygon::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//---------------------------------------
//�Z�b�g�e�N�X�`��(2d)
//---------------------------------------
void C3dpolygon::SetTex(PositionVec4 Tex)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	pVtx[0].tex = D3DXVECTOR2(Tex.P0, Tex.P2);
	pVtx[1].tex = D3DXVECTOR2(Tex.P1, Tex.P2);
	pVtx[2].tex = D3DXVECTOR2(Tex.P0, Tex.P3);
	pVtx[3].tex = D3DXVECTOR2(Tex.P1, Tex.P3);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//---------------------------------------
//�Z�b�g�T�C�Y
//---------------------------------------
void  C3dpolygon::SetSize(const D3DXVECTOR3 &size)
{
	m_size = size;

	VERTEX_3D*pVtx;		//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//------------------------
	// ���_���̐ݒ�
	//------------------------
	//���_���W
	for (int i = 0; i < 4; ++i)
	{
		pVtx[i].pos.x = m_Vtx[i].x * m_size.x; // TODO: ����Ȃ����B
		pVtx[i].pos.y = m_Vtx[i].y * m_size.y; // TODO: ����Ȃ����B
		pVtx[i].pos.z = m_Vtx[i].z * m_size.z;
	}

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

}
//---------------------------------------
//���_Colar�̐ݒ�
//---------------------------------------
void C3dpolygon::SetColar(D3DXCOLOR Colar)
{
	VERTEX_3D *pVtx; //���_�ւ̃|�C���^

	//���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	m_Colar = Colar;
	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�								  
	pVtx[0].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[1].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[2].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[3].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);

	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//---------------------------------------
//Vtx�̎擾
//---------------------------------------
LPDIRECT3DVERTEXBUFFER9 &C3dpolygon::GetVtx()
{
	return m_pVtxBuff;
}

//=============================================================================
// Animation�̖����ݒ�֐�
//=============================================================================
void C3dpolygon::SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop)
{
	m_DivisionX = U;
	m_DivisionY = V;
	m_DivisionMAX = m_DivisionY*m_DivisionX;

	m_PatternAnimX = 0;
	m_PatternAnimY = 0;
	m_animationSpeed = Speed;
	m_Timar = Drawtimer;
	m_OnAnimation = true;
	m_Loop = loop;
	//�\�����W���X�V
	SetTex(PositionVec4(
		1.0f / m_DivisionX * (m_PatternAnimX / (m_DivisionX))
		, 1.0f / m_DivisionX *(m_PatternAnimX / (m_DivisionX)) + 1.0f / m_DivisionX
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY))
		, 1.0f / m_DivisionY * (m_PatternAnimY % (m_DivisionY)+1.0f / m_DivisionY* m_DivisionY)));

}

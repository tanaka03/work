//=============================================================================
//
// Object
// Author : �l�c����
//
//=============================================================================

#include "object.h"
#include "object2d.h"
#include "manager.h"
#include "input.h"


 const D3DXVECTOR3 CObject2d::m_Vtx[4] =
{
	D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
	D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
	D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
};
//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CObject2d::CObject2d(int list):CObject(list)
{
}

//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CObject2d::~CObject2d()
{
}

//=============================================================================
// �|���S���̏�����
//=============================================================================
HRESULT CObject2d::Init()
{
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScale = 10.0f;

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

	m_texture = CTexture::TEXTURE_NONE;

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

	//------------------------ 
	// ���_���̐ݒ�
	//------------------------
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
	return S_OK;
}

//=============================================================================
// �|���S���̏I��
//=============================================================================
void CObject2d::Uninit()
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
void CObject2d::Update()
{
	
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
				SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			}
		}
		else
		{
			SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	m_pos += m_move;
}

//=============================================================================
// �|���S���̕`��
//=============================================================================
void CObject2d::Draw()
{
	LPDIRECT3DDEVICE9 pDevice;		//�f�o�C�X�ւ̃|�C���^

	 //�f�o�C�X�̎擾
	pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();


	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture* pTexture = CManager::GetInstance()->GetTexture();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));
	
	//�|���S���̕`��

	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		2);
	//�v���~�e�B�u(�|���S��)��
	pDevice->SetTexture(0, NULL);
}

//=============================================================================
// create�֐�
//=============================================================================
CObject2d *CObject2d::Create(int list)
{
	CObject2d * pObject = nullptr;
	pObject = new CObject2d(list);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//=============================================================================
// GetPos�֐�
//=============================================================================
D3DXVECTOR3 *CObject2d::GetPos()
{
	return &m_pos;
}

//=============================================================================
// SetPos�֐�
//=============================================================================
void CObject2d::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;
}
//=============================================================================
// SetPos�֐�
//=============================================================================
void CObject2d::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CObject2d::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
} 

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
CTexture::TEXTURE CObject2d::GetTexture()
{
	return m_texture;
}

//---------------------------------------
//�Z�b�g�e�N�X�`��(2d)
//---------------------------------------
void CObject2d::SetTex(PositionVec4 Tex)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

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

void CObject2d::SetColar(D3DXCOLOR Colar)
{
	VERTEX_2D *pVtx; //���_�ւ̃|�C���^

					 //���_�o�b�t�@�����b�N�����_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`���̍��W�ݒ�
	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[1].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[2].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);
	pVtx[3].col = D3DXCOLOR(Colar.r, Colar.g, Colar.b, Colar.a);

	m_col = Colar;
	//���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

}

//=============================================================================
// Animation�̖����ݒ�֐�
//=============================================================================
void CObject2d::SetAnimation(const int U, const int V,const int Speed,const int Drawtimer,const bool loop)
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

//--------------------------------------------------
// �A�j���[�V�����̐ݒ�
//--------------------------------------------------
void CObject2d::AnimTexture(int nPattern, int nPatternMax)
{
	VERTEX_2D *pVtx;			// ���_���ւ̃|�C���^

	float nDivisionRate = 1.0f / nPatternMax;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = D3DXVECTOR2(nPattern * nDivisionRate, 0.0f);
	pVtx[1].tex = D3DXVECTOR2((nPattern + 1) * nDivisionRate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * nDivisionRate, 1.0f);
	pVtx[3].tex = D3DXVECTOR2((nPattern + 1) * nDivisionRate, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
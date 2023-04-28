//=========================================
// 
// ���C�g�̍쐬
// Author HAMAD
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "manager.h"
#include "renderer.h"
#include "light.h"


//=========================================
// �R���X�g���N�g
//=========================================
CLight::CLight()
{
}

//=========================================
// �f�X�g���N�g
//=========================================
CLight::~CLight()
{

}


//=========================================
// ������
//=========================================
void CLight::Init(void)
{
	// ���C�g���N���A����
	ZeroMemory(m_light, sizeof(m_light));

	// ���C�g�̐ݒ�
	Set(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0);
	Set(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 1.0f), 1);
	//Set(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 2);

	// �f�o�C�X�ւ̃|�C���^�̎擾
	CManager::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}

//=========================================
// �I��
//=========================================
void CLight::Uninit(void)
{
}

//=========================================
// �X�V
//=========================================
void CLight::Update(void)
{
}

//=========================================
// �ݒ�
//=========================================
void CLight::Set(D3DLIGHTTYPE type,D3DXCOLOR col, D3DXVECTOR3 vec, int nNum)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;		// ���C�g�̕����x�N�g��

	m_light[nNum].Type = type;	// ���C�g�̎�ނ�ݒ� ( ���s���� )
	m_light[nNum].Diffuse = col;	// ���C�g�̊g�U����ݒ� ( ���C�g�̐F )

	vecDir = vec;	// ���C�g�̕�����ݒ�

	// ���K������ ( �傫�� 1 �̃x�N�g���ɂ��� )
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[nNum].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(nNum, &m_light[nNum]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(nNum, TRUE);

}
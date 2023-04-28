//============================
//
// �QDpolygon�ݒ�
// Author:hamada ryuuga
//
//============================

#include "2dpolygontemplate.h"
#include "utility.h"
//------------------------------------
// �R���X�g���N�^
//------------------------------------
CTest::CTest() :CObject2d(PRIORITY_BG)
{
}

//------------------------------------
// �f�X�g���N�^
//------------------------------------
CTest::~CTest()
{
}

//------------------------------------
// ������
//------------------------------------
HRESULT CTest::Init()
{
	CObject2d::Init();

	m_testrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//------------------------------------
// �I��
//------------------------------------
void CTest::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// �X�V
//------------------------------------
void CTest::Update()
{
	CObject2d::Update();
	//����
	CTest::move();
}

//------------------------------------
// �`��
//------------------------------------
void CTest::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CTest *CTest::Create(D3DXVECTOR3 pos, bool b3D)
{
	CTest * pObject = new CTest;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 Poppos = pos;
		if (b3D)
		{
			Poppos = ScreenCastWorld(&Poppos,			// �X�N���[�����W
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));								// �X�N���[���T�C�Y
		}
		pObject->Init();
		pObject->SetPos(Poppos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);//�e�N�X�`���I��
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//move�̐ݒ�
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));//�T�C�Y�ݒ�

		//������(1���̖���,2�c�̖���,3Animation���x,�S��{�[�������Ǖ\������܂ł̃^�C�����O,5�����ɃA�j���[�V�����Đ����邩�ǂ���)
		pObject->SetAnimation(7,1,0,0,false);//Animation�摜�������ꍇ���������,�ꖇ�G�Ȃ�����Ȃ��ƃo�O��

		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//�F�ݒ�
	
	}
	return pObject;
}


//------------------------------------
// �����n��
//------------------------------------
void CTest::move()
{
	m_testrot.z+=0.1f;
	//�������ꂽ���Ƃ��͂�����	SetMove()�ŕς�����
	SetRot(m_testrot);
	m_pos += m_move;
}
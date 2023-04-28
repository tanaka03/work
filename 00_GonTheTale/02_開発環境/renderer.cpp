//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "renderer.h"
#include "main.h"
#include "object.h"
#include "light.h"
 
#include "particle.h"
 
#include "camera.h"
#include "3dpolygon.h"
#include "pause.h"
#include "game.h"
#include "input.h"

#include "manager.h"

 CCamera* CRenderer::pCamera[2];
 CLight*  CRenderer::pLight;
 CParticle*  CRenderer::particle;

//=============================================================================
// �R���X�g���N�g�֐�
//=============================================================================
CRenderer::CRenderer()
{

}
//=============================================================================
// �f�X�g���N�g�֐�
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// ������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_pD3dpp, sizeof(m_pD3dpp));							// ���[�N���[���N���A
	m_pD3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	m_pD3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	m_pD3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	m_pD3dpp.BackBufferFormat = d3ddm.Format;							// �J���[���[�h�̎w��
	m_pD3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �f���M���ɓ������ăt���b�v����
	m_pD3dpp.EnableAutoDepthStencil = TRUE;								// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	m_pD3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	m_pD3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	m_pD3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	m_pD3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��

// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_pD3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_pD3dpp, &m_pD3DDevice))) &&
		// ��L�̐ݒ肪���s������
		// �`��ƒ��_������CPU�ōs�Ȃ�
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_pD3dpp, &m_pD3DDevice))))
	{
		// �������s
		return E_FAIL;
	}

	D3DXCreateEffectFromFile(m_pD3DDevice, "Effect.fx", NULL, NULL, 0, NULL, &m_pEffect, nullptr);

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̐���
	D3DXCreateFont(m_pD3DDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Terminal"), &m_pFont);
#endif
	//SetFog(true, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	pCamera[0] = new CCamera;
	pCamera[0]->Init();
	
	pCamera[1] = new CCamera;
	pCamera[1]->Init();

	pLight = new CLight;
	pLight->Init();
	
	return S_OK;
}

//=============================================================================
// �I��
//=============================================================================
void CRenderer::Uninit()
{
	CObject::AllUninit();

	// ���C�g�I������
	if (pLight != nullptr)
	{
		pLight->Uninit();
		delete pLight;
		pLight = nullptr;
	}

	// �J�����I������
	if (pCamera[0] != nullptr)
	{
		pCamera[0]->Uninit();
		delete pCamera[0];
		pCamera[0] = nullptr;
	}

	// �J�����I������
	if (pCamera[1] != nullptr)
	{
		pCamera[1]->Uninit();
		delete pCamera[1];
		pCamera[1] = nullptr;
	}

	if (particle != nullptr)
	{
		particle->Uninit();
		delete particle;
		particle = nullptr;
	}

#ifdef _DEBUG
	// �f�o�b�O���\���p�t�H���g�̔j��
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// �f�o�C�X�̔j��
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// �X�V
//=============================================================================
void CRenderer::Update()
{
	CPause * pPause = CGame::GetPause();

	C3dpolygon::PolygonReset();

	
	pCamera[0]->Update();
	pLight->Update();
	if (pPause == nullptr)
	{
		CObject::AllUpdate();
	}
	else
	{
		if (pPause->Get())
		{
			CObject::TypeUpdate(CObject::PAUSE);
			//pPause->Update();
		}
		else
		{
			CObject::AllUpdate();
		}
	}
}

//=============================================================================
// �`��
//=============================================================================
void CRenderer::Draw()
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	//��ʃN���A(�o�b�N�o�b�t�@&Z�o�b�t�@�̃N���A)
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		pCamera[0]->Set(0);
		CObject::AllDraw();	

	
#ifdef _DEBUG
		// FPS�\��
		DrawFPS();
#endif // _DEBUG

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	if (m_pD3DDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST)
	{
		//DeviceLost();
	}
}

#ifdef _DEBUG
//=============================================================================
// FPS�\��
//=============================================================================
void  CRenderer::DrawFPS()
{
	if (m_pFont == nullptr)
	{
		return;
	}

	int time = Gettime();
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	TCHAR str[256];

	wsprintf(str, _T("FPS : %d\n"), time);

	// �e�L�X�g�`��
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG

//=============================================================================
// �t�H�O�ݒ菈��
//=============================================================================
void CRenderer::SetFog(bool bFlag, D3DXCOLOR col)
{
	// �t�H�O�̗L���ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, bFlag);

	// �t�H�O�J���[�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, col);

	// �t�H�O���[�h ������(�͈͎w�� : D3DFOG_LINEAR, ���x�w�� : D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	// �͈͎w��(��LINEAR���Ɏw��)
	float fFogStartPos = 2000;
	float fFogEndPos = 9000;
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// ���x�w��(��EXP���Ɏw��)
	//float fFogDensity = 0.0001f;

	//m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}
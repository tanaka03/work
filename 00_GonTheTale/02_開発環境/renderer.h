//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================
#ifndef _RENDERER_H_			// ���̃}�N����`������ĂȂ�������
#define _RENDERER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//*****************************************************************************
// ���C�u�����[�����N
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// �C���N���[�h
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> // _T
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include <string>

//*****************************************************************************
// �萔��`
//*****************************************************************************
namespace
{
	// �E�C���h�E�̃N���X��
	LPCTSTR CLASS_NAME = _T("AppClass");
	// �E�C���h�E�̃L���v�V������
	LPCTSTR WINDOW_NAME = _T("Fox");
}

const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���

// ���_�t�H�[�}�b�g
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
// ���_�f�[�^
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;	// �e�N�X�`�����W(���x��1)
};

//���_���u3D�v�̍\���̂��`
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �x�N�g��
	D3DCOLOR col;		// �J���[
	D3DXVECTOR2 tex;	// �e�N�X�`��
};

int Gettime(void);

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CCamera;
class CLight;
class CParticle;

//-----------------------------------------------------------------------------
// �`��N���X
//-----------------------------------------------------------------------------
class CRenderer
{
public:
	CRenderer();
	~CRenderer();
	HRESULT Init(HWND hWnd, bool bWindow);
	void Uninit();
	void Update();
	void Draw();

	LPDIRECT3DDEVICE9 GetDevice(void) { return m_pD3DDevice; }

	static CCamera *GetCamera() { return pCamera[0]; }

	static CLight *GetLight() { return pLight; }
	 LPD3DXEFFECT GetEffect() { return m_pEffect; }
	
	
	void SetFog(bool bFlag, D3DXCOLOR col);
#ifdef _DEBUG
	void SetModeline(bool IsMesh) { m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, IsMesh ? D3DFILL_SOLID : D3DFILL_WIREFRAME); }
	void DrawFPS();
#endif // _DEBUG

private:

#ifdef _DEBUG
	LPD3DXFONT m_pFont = nullptr;	// �t�H���g
#endif // _DEBUG
	void DrawMaterial();
	LPDIRECT3D9 m_pD3D = nullptr;	// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;	// Device�I�u�W�F�N�g
	D3DPRESENT_PARAMETERS m_pD3dpp;

	static CCamera* pCamera[2];
	static CLight* pLight;
	static CParticle* particle;

	LPD3DXEFFECT m_pEffect;        // �V�F�[�_�[
};


#endif
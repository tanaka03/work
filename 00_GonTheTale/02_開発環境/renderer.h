//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _RENDERER_H_			// このマクロ定義がされてなかったら
#define _RENDERER_H_			// 二重インクルード防止のマクロ定義

//*****************************************************************************
// ライブラリーリンク
//*****************************************************************************
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"winmm.lib")

//*****************************************************************************
// インクルード
//*****************************************************************************
#include <Windows.h>
#include <tchar.h> // _T
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include <string>

//*****************************************************************************
// 定数定義
//*****************************************************************************
namespace
{
	// ウインドウのクラス名
	LPCTSTR CLASS_NAME = _T("AppClass");
	// ウインドウのキャプション名
	LPCTSTR WINDOW_NAME = _T("Fox");
}

const int SCREEN_WIDTH = 1280;	// スクリーンの幅
const int SCREEN_HEIGHT = 720;	// スクリーンの高さ

// 頂点フォーマット
const DWORD FVF_VERTEX_2D = (D3DFVF_XYZRHW | D3DFVF_DIFFUSE| D3DFVF_TEX1);
const DWORD FVF_VERTEX_3D(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);

//*****************************************************************************
// 構造体定義
//*****************************************************************************
// 頂点データ
struct VERTEX_2D
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;	// テクスチャ座標(レベル1)
};

//頂点情報「3D」の構造体を定義
struct VERTEX_3D
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// ベクトル
	D3DCOLOR col;		// カラー
	D3DXVECTOR2 tex;	// テクスチャ
};

int Gettime(void);

//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------
class CCamera;
class CLight;
class CParticle;

//-----------------------------------------------------------------------------
// 描画クラス
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
	LPD3DXFONT m_pFont = nullptr;	// フォント
#endif // _DEBUG
	void DrawMaterial();
	LPDIRECT3D9 m_pD3D = nullptr;	// Direct3Dオブジェクト
	LPDIRECT3DDEVICE9 m_pD3DDevice = nullptr;	// Deviceオブジェクト
	D3DPRESENT_PARAMETERS m_pD3dpp;

	static CCamera* pCamera[2];
	static CLight* pLight;
	static CParticle* particle;

	LPD3DXEFFECT m_pEffect;        // シェーダー
};


#endif
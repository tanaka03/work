//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
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
// コンストラクト関数
//=============================================================================
CRenderer::CRenderer()
{

}
//=============================================================================
// デストラクト関数
//=============================================================================
CRenderer::~CRenderer()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == nullptr)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&m_pD3dpp, sizeof(m_pD3dpp));							// ワークをゼロクリア
	m_pD3dpp.BackBufferCount = 1;										// バックバッファの数
	m_pD3dpp.BackBufferWidth = SCREEN_WIDTH;							// ゲーム画面サイズ(幅)
	m_pD3dpp.BackBufferHeight = SCREEN_HEIGHT;							// ゲーム画面サイズ(高さ)
	m_pD3dpp.BackBufferFormat = d3ddm.Format;							// カラーモードの指定
	m_pD3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// 映像信号に同期してフリップする
	m_pD3dpp.EnableAutoDepthStencil = TRUE;								// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	m_pD3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// デプスバッファとして16bitを使う
	m_pD3dpp.Windowed = bWindow;										// ウィンドウモード
	m_pD3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	m_pD3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル

// ディスプレイアダプタを表すためのデバイスを作成
// 描画と頂点処理をハードウェアで行なう
	if ((FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_pD3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_pD3dpp, &m_pD3DDevice))) &&
		// 上記の設定が失敗したら
		// 描画と頂点処理をCPUで行なう
		(FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_pD3dpp, &m_pD3DDevice))))
	{
		// 生成失敗
		return E_FAIL;
	}

	D3DXCreateEffectFromFile(m_pD3DDevice, "Effect.fx", NULL, NULL, 0, NULL, &m_pEffect, nullptr);

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	// デバッグ情報表示用フォントの生成
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
// 終了
//=============================================================================
void CRenderer::Uninit()
{
	CObject::AllUninit();

	// ライト終了処理
	if (pLight != nullptr)
	{
		pLight->Uninit();
		delete pLight;
		pLight = nullptr;
	}

	// カメラ終了処理
	if (pCamera[0] != nullptr)
	{
		pCamera[0]->Uninit();
		delete pCamera[0];
		pCamera[0] = nullptr;
	}

	// カメラ終了処理
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
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != nullptr)
	{
		m_pFont->Release();
		m_pFont = nullptr;
	}
#endif // _DEBUG

	// デバイスの破棄
	if (m_pD3DDevice != nullptr)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != nullptr)
	{
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
}

//=============================================================================
// 更新
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
// 描画
//=============================================================================
void CRenderer::Draw()
{
	// バックバッファ＆Ｚバッファのクリア
	//画面クリア(バックバッファ&Zバッファのクリア)
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		pCamera[0]->Set(0);
		CObject::AllDraw();	

	
#ifdef _DEBUG
		// FPS表示
		DrawFPS();
#endif // _DEBUG

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	if (m_pD3DDevice->Present(NULL, NULL, NULL, NULL) == D3DERR_DEVICELOST)
	{
		//DeviceLost();
	}
}

#ifdef _DEBUG
//=============================================================================
// FPS表示
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

	// テキスト描画
	m_pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
#endif // _DEBUG

//=============================================================================
// フォグ設定処理
//=============================================================================
void CRenderer::SetFog(bool bFlag, D3DXCOLOR col)
{
	// フォグの有効設定
	m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, bFlag);

	// フォグカラーの設定
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, col);

	// フォグモード 第二引数(範囲指定 : D3DFOG_LINEAR, 密度指定 : D3DFOG_EXP)
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);

	// 範囲指定(※LINEAR時に指定)
	float fFogStartPos = 2000;
	float fFogEndPos = 9000;
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fFogStartPos));
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fFogEndPos));

	// 密度指定(※EXP時に指定)
	//float fFogDensity = 0.0001f;

	//m_pD3DDevice->SetRenderState(D3DRS_FOGDENSITY, *(DWORD*)(&fFogDensity));
}
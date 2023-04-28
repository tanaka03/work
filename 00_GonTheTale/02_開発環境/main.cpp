//=============================================================================
//
// メイン
// Author : 浜田琉雅
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "resource1.h"
#include "manager.h"

#include "game.h"


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void funcFileSave(HWND hWnd);

//=============================================================================
// 静的変数
//=============================================================================
static TCHAR szPathdefault[MAX_PATH];
static bool bTexUse = false;
static bool bPress = false;	// リボンバーのトリガー処理のために必要な変数
static char buffer1[MAX_PATH];

#ifdef _DEBUG
// FPSカウンタ
static int g_nCountFPS;
#endif // _DEBUG

//=============================================================================
// メイン関数
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	GetCurrentDirectory(MAX_PATH, szPathdefault);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY2DC)),
		LoadCursor(nullptr, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW + 1),
		MAKEINTRESOURCE(IDR_MENU1),
		CLASS_NAME,
		LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL))
	};

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// 指定したクライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// ウィンドウの作成
	HWND hWnd = CreateWindow(CLASS_NAME,
		WINDOW_NAME,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rect.right - rect.left),
		(rect.bottom - rect.top),
		NULL,
		NULL,
		hInstance,
		NULL);

	CManager* pManeager = CManager::GetInstance();

	if (FAILED(pManeager->Init(hWnd, TRUE, hInstance)))	//画面サイズ
	{//初期化処理が失敗した場合
		return -1;
	}

	// 分解能を設定
	timeBeginPeriod(1);

	// フレームカウント初期化
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();

#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif // _DEBUG

	// ウインドウの表示
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// メッセージループ
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ // PostQuitMessage()が呼ばれたらループ終了
				break;
			}
			else
			{
				// メッセージの翻訳とディスパッチ
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// 現在の時間を取得
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5秒ごとに実行
				// FPSを算出
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// 現在の時間を保存
				dwFrameCount = 0;
			}
#endif // _DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ // 1/60秒経過
				// 現在の時間を保存
				dwExecLastTime = dwCurrentTime;

				pManeager->Update();

				pManeager->Draw();

#ifdef _DEBUG
				dwFrameCount++;
#endif // _DEBUG
			}
		}
	}



	if (pManeager != nullptr)
	{// 終了処理

		pManeager->Uninit();
		delete pManeager;
		pManeager = nullptr;
	}
	
	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// 分解能を戻す
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// ウインドウプロシージャ
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 選択されたメニューの解析:
		switch (wmId)
		{
		case IDA_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_40004:
			MessageBox(hWnd, "2023/2/24", "バージョン1.00", MB_OK);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		//HDC hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]キーが押された
			// ウィンドウを破棄
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifdef _DEBUG
//=============================================================================
// 時間
//=============================================================================
int Gettime(void)
{
	return g_nCountFPS;
}
#endif // _DEBUG

//=============================================================================
// ウィンドウだしてやるやつ
//=============================================================================
void funcFileSave(HWND hWnd)
{
	static OPENFILENAME	ofn;

	static TCHAR szFile[MAX_PATH];
	static TCHAR szPath[MAX_PATH];

	if (szPath[0] == TEXT('\0'))
	{

		//Currentをテクスチャにのとこに変更します
		SetCurrentDirectory(szPathdefault);
		CreateDirectory("data\\TEXTURE", NULL);
		SetCurrentDirectory("data\\TEXTURE");

		GetCurrentDirectory(MAX_PATH, szPath);
	}

	if (ofn.lStructSize == 0)
	{
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// 初期フォルダ位置
		ofn.lpstrFile = szFile;			// 選択ファイル格納
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".png");
		ofn.lpstrFilter = TEXT("pngファイル(*.png)\0*.png\0");
		ofn.lpstrTitle = TEXT("画像ファイルを保存します。");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	}

	if (GetSaveFileName(&ofn))
	{
		MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
	}

	if (szFile[0] != '\0')
	{

		//fileの名前を入れます
		//CApplication::GetInstance()->GetImguiProperty()->SetFileName(szFile);

		//CGame::GetStage()->SetPath(szFile);		// パスの設定
		//CTexture* pTexture = CApplication::GetInstance()->GetTextureClass();
		//pTexture->SetPath(szFile);

		CopyFile((LPCTSTR)buffer1, // 既存のファイルの名前
			szFile, // 新しいファイルの名前
			false// ファイルが存在する場合の動作
		);
		//CGame::GetStage()->SetPathTex(szFile);
		//Currentを戻す
		SetCurrentDirectory(szPathdefault);

		bTexUse = true;
	}
	bPress = true;
}

//=============================================================================
// ファイルねーむ
//=============================================================================
bool *TexUse(void)
{
	return &bTexUse;
}

//=============================================================================
// BufferTXT取得
//=============================================================================
char *GetBuffer(void)
{
	return &buffer1[0];
}


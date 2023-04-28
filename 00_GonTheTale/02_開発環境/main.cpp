//=============================================================================
//
// ���C��
// Author : �l�c����
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
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void funcFileSave(HWND hWnd);

//=============================================================================
// �ÓI�ϐ�
//=============================================================================
static TCHAR szPathdefault[MAX_PATH];
static bool bTexUse = false;
static bool bPress = false;	// ���{���o�[�̃g���K�[�����̂��߂ɕK�v�ȕϐ�
static char buffer1[MAX_PATH];

#ifdef _DEBUG
// FPS�J�E���^
static int g_nCountFPS;
#endif // _DEBUG

//=============================================================================
// ���C���֐�
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

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	// �w�肵���N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

	// �E�B���h�E�̍쐬
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

	if (FAILED(pManeager->Init(hWnd, TRUE, hInstance)))	//��ʃT�C�Y
	{//���������������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	// �t���[���J�E���g������
	DWORD dwCurrentTime = 0;
	DWORD dwExecLastTime = timeGetTime();

#ifdef _DEBUG
	DWORD dwFrameCount = 0;
	DWORD dwFPSLastTime = dwExecLastTime;
#endif // _DEBUG

	// �E�C���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;

	// ���b�Z�[�W���[�v
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{ // PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				// ���b�Z�[�W�̖|��ƃf�B�X�p�b�`
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();	// ���݂̎��Ԃ��擾
#ifdef _DEBUG
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b���ƂɎ��s
				// FPS���Z�o
				g_nCountFPS = dwFrameCount * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;	// ���݂̎��Ԃ�ۑ�
				dwFrameCount = 0;
			}
#endif // _DEBUG

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{ // 1/60�b�o��
				// ���݂̎��Ԃ�ۑ�
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
	{// �I������

		pManeager->Uninit();
		delete pManeager;
		pManeager = nullptr;
	}
	
	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//=============================================================================
// �E�C���h�E�v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	switch (uMsg)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDA_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_40004:
			MessageBox(hWnd, "2023/2/24", "�o�[�W����1.00", MB_OK);
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
		case VK_ESCAPE: // [ESC]�L�[�������ꂽ
			// �E�B���h�E��j��
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
// ����
//=============================================================================
int Gettime(void)
{
	return g_nCountFPS;
}
#endif // _DEBUG

//=============================================================================
// �E�B���h�E�����Ă����
//=============================================================================
void funcFileSave(HWND hWnd)
{
	static OPENFILENAME	ofn;

	static TCHAR szFile[MAX_PATH];
	static TCHAR szPath[MAX_PATH];

	if (szPath[0] == TEXT('\0'))
	{

		//Current���e�N�X�`���ɂ̂Ƃ��ɕύX���܂�
		SetCurrentDirectory(szPathdefault);
		CreateDirectory("data\\TEXTURE", NULL);
		SetCurrentDirectory("data\\TEXTURE");

		GetCurrentDirectory(MAX_PATH, szPath);
	}

	if (ofn.lStructSize == 0)
	{
		ofn.lStructSize = sizeof(OPENFILENAME);
		ofn.hwndOwner = hWnd;
		ofn.lpstrInitialDir = szPath;	// �����t�H���_�ʒu
		ofn.lpstrFile = szFile;			// �I���t�@�C���i�[
		ofn.nMaxFile = MAX_PATH;
		ofn.lpstrDefExt = TEXT(".png");
		ofn.lpstrFilter = TEXT("png�t�@�C��(*.png)\0*.png\0");
		ofn.lpstrTitle = TEXT("�摜�t�@�C����ۑ����܂��B");
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
	}

	if (GetSaveFileName(&ofn))
	{
		MessageBox(hWnd, szFile, TEXT("�t�@�C������t���ĕۑ�"), MB_OK);
	}

	if (szFile[0] != '\0')
	{

		//file�̖��O�����܂�
		//CApplication::GetInstance()->GetImguiProperty()->SetFileName(szFile);

		//CGame::GetStage()->SetPath(szFile);		// �p�X�̐ݒ�
		//CTexture* pTexture = CApplication::GetInstance()->GetTextureClass();
		//pTexture->SetPath(szFile);

		CopyFile((LPCTSTR)buffer1, // �����̃t�@�C���̖��O
			szFile, // �V�����t�@�C���̖��O
			false// �t�@�C�������݂���ꍇ�̓���
		);
		//CGame::GetStage()->SetPathTex(szFile);
		//Current��߂�
		SetCurrentDirectory(szPathdefault);

		bTexUse = true;
	}
	bPress = true;
}

//=============================================================================
// �t�@�C���ˁ[��
//=============================================================================
bool *TexUse(void)
{
	return &bTexUse;
}

//=============================================================================
// BufferTXT�擾
//=============================================================================
char *GetBuffer(void)
{
	return &buffer1[0];
}


//**************************************************
// 
// フォント
// Author  : HamadaRyuuga
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "manager.h"
#include "font.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CFont::s_FileName[] =
{// フォントのパス
	"data/font/FZゴンタかな.otf",
	"data/font/meiryob.ttc",
	"data/font/HGRPP1.TTC",
};

static_assert(sizeof(CFont::s_FileName) / sizeof(CFont::s_FileName[0]) == CFont::FONT_MAX, "aho");

//==================================================
// 定義
//==================================================
const char* CFont::s_FontName[] =
{// フォントのなまえ
	"FZゴンタかな",
	"メイリオ",
	"HG創英角ポップ体",
};

static_assert(sizeof(CFont::s_FontName) / sizeof(CFont::s_FontName[0]) == CFont::FONT_MAX, "aho");

//=============================================================================--------------
// デフォルトコンストラクタ
//=============================================================================--------------
CFont::CFont() :
	m_texFont()
{
	memset(m_texFont, 0, sizeof(m_texFont));
}

//=============================================================================--------------
// デストラクタ
//=============================================================================--------------
CFont::~CFont()
{
}

//=============================================================================--------------
// 読み込み
//=============================================================================--------------
void CFont::Load(FONT inTexture)
{
	assert(inTexture >= 0 && inTexture < FONT_MAX);

	if (m_texFont[inTexture] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}
	
	// フォントを使えるようにする
	DESIGNVECTOR design;
	

	AddFontResourceEx(
		s_FileName[inTexture], //ttfファイルへのパス
		FR_PRIVATE,
		&design
	);

	// フォントの生成
	int fontsize = 38;
	m_lf[inTexture] = { fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN };
	
	
	strcpy(m_lf[inTexture].lfFaceName, s_FontName[inTexture]);
	
}

//=============================================================================--------------
// 読み込み
//=============================================================================--------------
void CFont::LoadWords(std::string inWords, FONT inTexture)
{

	if (!(m_hFont[inTexture] = CreateFontIndirect(&m_lf[inTexture])))
	{

	}

	// デバイスコンテキスト取得
	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont[inTexture]);

	std::string words = inWords;
	// 文字コード取得
	const char *c = words.c_str();
	UINT code = 0;
#if _UNICODE
	// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
	code = (UINT)*c;
#else
	// マルチバイト文字の場合、
	// 1バイト文字のコードは1バイト目のUINT変換、
	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
	if (IsDBCSLeadByte(*c))
		code = (BYTE)c[0] << 8 | (BYTE)c[1];
	else
		code = c[0];
#endif

	// フォントビットマップ取得
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 2, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// デバイスコンテキストとフォントハンドルの開放
	SelectObject(hdc, oldFont);
	DeleteObject(m_hFont[inTexture]);
	ReleaseDC(NULL, hdc);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//デバイスの取得

																		// テクスチャ作成
	if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_texFont[inTexture], NULL)))
		if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_texFont[inTexture], NULL)))
		{

		}

	// テクスチャにフォントビットマップ書き込み
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_texFont[inTexture]->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
		if (FAILED(m_texFont[inTexture]->LockRect(0, &LockedRect, NULL, 0)))
		{

		}

	// フォント情報の書き込み
	// iOfs_x, iOfs_y : 書き出し位置(左上)
	// iBmp_w, iBmp_h : フォントビットマップの幅高
	// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + (4 - (GM.gmBlackBoxX % 4)) % 4;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	FillMemory(LockedRect.pBits, LockedRect.Pitch * TM.tmHeight, 0);
	for (y = iOfs_y; y<iOfs_y + iBmp_h; y++)
		for (x = iOfs_x; x<iOfs_x + GM.gmBlackBoxX; x++) {
			Alpha = (255 * ptr[x - iOfs_x + iBmp_w*(y - iOfs_y)]) / (Level - 1);
			Color = 0x00ffffff | (Alpha << 24);
			memcpy((BYTE*)LockedRect.pBits + LockedRect.Pitch*y + 4 * x, &Color, sizeof(DWORD));
		}

	m_texFont[inTexture]->UnlockRect(0);

	delete[] ptr;

}

//=============================================================================--------------
// 全ての解放
//=============================================================================--------------
void CFont::ReleaseAll(void)
{
	for (int i = 0; i < FONT_MAX; ++i)
	{
		if (m_texFont[i] != NULL)
		{// テクスチャの解放
			m_texFont[i]->Release();
			m_texFont[i] = NULL;
		}
	}

}

//=============================================================================--------------
// 解放
//=============================================================================--------------
void CFont::Release(FONT inTexture)
{
	assert(inTexture >= 0 && inTexture < FONT_MAX);
	DESIGNVECTOR design;

	if (m_texFont[inTexture] != NULL)
	{// テクスチャの解放
		m_texFont[inTexture]->Release();
		m_texFont[inTexture] = NULL;
	}
	if (s_FileName[inTexture] != NULL)
	{
		RemoveFontResourceEx(
			TEXT(s_FileName[inTexture]), //ttfファイルへのパス
			FR_PRIVATE,
			&design
		);
	}
}

//=============================================================================--------------
// 取得
//=============================================================================--------------
LPDIRECT3DTEXTURE9 CFont::GetFont(std::string words,FONT inTexture)
{
	if (inTexture == FONT_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < FONT_MAX);

	// 読み込み
	Load(inTexture);

	LoadWords(words, inTexture);

	return m_texFont[inTexture];
}


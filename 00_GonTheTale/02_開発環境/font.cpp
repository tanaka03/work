//**************************************************
// 
// �t�H���g
// Author  : HamadaRyuuga
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "manager.h"
#include "font.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CFont::s_FileName[] =
{// �t�H���g�̃p�X
	"data/font/FZ�S���^����.otf",
	"data/font/meiryob.ttc",
	"data/font/HGRPP1.TTC",
};

static_assert(sizeof(CFont::s_FileName) / sizeof(CFont::s_FileName[0]) == CFont::FONT_MAX, "aho");

//==================================================
// ��`
//==================================================
const char* CFont::s_FontName[] =
{// �t�H���g�̂Ȃ܂�
	"FZ�S���^����",
	"���C���I",
	"HG�n�p�p�|�b�v��",
};

static_assert(sizeof(CFont::s_FontName) / sizeof(CFont::s_FontName[0]) == CFont::FONT_MAX, "aho");

//=============================================================================--------------
// �f�t�H���g�R���X�g���N�^
//=============================================================================--------------
CFont::CFont() :
	m_texFont()
{
	memset(m_texFont, 0, sizeof(m_texFont));
}

//=============================================================================--------------
// �f�X�g���N�^
//=============================================================================--------------
CFont::~CFont()
{
}

//=============================================================================--------------
// �ǂݍ���
//=============================================================================--------------
void CFont::Load(FONT inTexture)
{
	assert(inTexture >= 0 && inTexture < FONT_MAX);

	if (m_texFont[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}
	
	// �t�H���g���g����悤�ɂ���
	DESIGNVECTOR design;
	

	AddFontResourceEx(
		s_FileName[inTexture], //ttf�t�@�C���ւ̃p�X
		FR_PRIVATE,
		&design
	);

	// �t�H���g�̐���
	int fontsize = 38;
	m_lf[inTexture] = { fontsize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS, PROOF_QUALITY, FIXED_PITCH | FF_MODERN };
	
	
	strcpy(m_lf[inTexture].lfFaceName, s_FontName[inTexture]);
	
}

//=============================================================================--------------
// �ǂݍ���
//=============================================================================--------------
void CFont::LoadWords(std::string inWords, FONT inTexture)
{

	if (!(m_hFont[inTexture] = CreateFontIndirect(&m_lf[inTexture])))
	{

	}

	// �f�o�C�X�R���e�L�X�g�擾
	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
	HDC hdc = GetDC(NULL);
	HFONT oldFont = (HFONT)SelectObject(hdc, m_hFont[inTexture]);

	std::string words = inWords;
	// �����R�[�h�擾
	const char *c = words.c_str();
	UINT code = 0;
#if _UNICODE
	// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
	code = (UINT)*c;
#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	if (IsDBCSLeadByte(*c))
		code = (BYTE)c[0] << 8 | (BYTE)c[1];
	else
		code = c[0];
#endif

	// �t�H���g�r�b�g�}�b�v�擾
	TEXTMETRIC TM;
	GetTextMetrics(hdc, &TM);
	GLYPHMETRICS GM;
	CONST MAT2 Mat = { { 0,1 },{ 0,0 },{ 0,0 },{ 0,1 } };
	DWORD size = GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, 2, NULL, &Mat);
	BYTE *ptr = new BYTE[size];
	GetGlyphOutline(hdc, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	// �f�o�C�X�R���e�L�X�g�ƃt�H���g�n���h���̊J��
	SelectObject(hdc, oldFont);
	DeleteObject(m_hFont[inTexture]);
	ReleaseDC(NULL, hdc);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	//�f�o�C�X�̎擾

																		// �e�N�X�`���쐬
	if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, D3DUSAGE_DYNAMIC, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_texFont[inTexture], NULL)))
		if (FAILED(pDevice->CreateTexture(GM.gmCellIncX, TM.tmHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_texFont[inTexture], NULL)))
		{

		}

	// �e�N�X�`���Ƀt�H���g�r�b�g�}�b�v��������
	D3DLOCKED_RECT LockedRect;
	if (FAILED(m_texFont[inTexture]->LockRect(0, &LockedRect, NULL, D3DLOCK_DISCARD)))
		if (FAILED(m_texFont[inTexture]->LockRect(0, &LockedRect, NULL, 0)))
		{

		}

	// �t�H���g���̏�������
	// iOfs_x, iOfs_y : �����o���ʒu(����)
	// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
	// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
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
// �S�Ẳ��
//=============================================================================--------------
void CFont::ReleaseAll(void)
{
	for (int i = 0; i < FONT_MAX; ++i)
	{
		if (m_texFont[i] != NULL)
		{// �e�N�X�`���̉��
			m_texFont[i]->Release();
			m_texFont[i] = NULL;
		}
	}

}

//=============================================================================--------------
// ���
//=============================================================================--------------
void CFont::Release(FONT inTexture)
{
	assert(inTexture >= 0 && inTexture < FONT_MAX);
	DESIGNVECTOR design;

	if (m_texFont[inTexture] != NULL)
	{// �e�N�X�`���̉��
		m_texFont[inTexture]->Release();
		m_texFont[inTexture] = NULL;
	}
	if (s_FileName[inTexture] != NULL)
	{
		RemoveFontResourceEx(
			TEXT(s_FileName[inTexture]), //ttf�t�@�C���ւ̃p�X
			FR_PRIVATE,
			&design
		);
	}
}

//=============================================================================--------------
// �擾
//=============================================================================--------------
LPDIRECT3DTEXTURE9 CFont::GetFont(std::string words,FONT inTexture)
{
	if (inTexture == FONT_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < FONT_MAX);

	// �ǂݍ���
	Load(inTexture);

	LoadWords(words, inTexture);

	return m_texFont[inTexture];
}


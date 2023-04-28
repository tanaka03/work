//**************************************************
// 
// �t�H���g
// Author  : HamadaRyuuga
// 
//**************************************************
#ifndef _FONT_H_	//���̃}�N����`������ĂȂ�������
#define _FONT_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")

//==================================================
// ��`
//==================================================
class CFont
{
public: /* ��` */
	enum FONT
	{
		FONT_GON = 0,
		FONT_MEIRIO,
		FONT_SOUEIKAKU,
		FONT_MAX,
		FONT_NONE,	// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

	static const char* s_FontName[];	// �t�@�C���p�X
public:
	CFont();		// �f�t�H���g�R���X�g���N�^
	~CFont();	// �f�X�g���N�^

public: /* �����o�֐� */
	void Load(FONT inTexture);						// �w��̓ǂݍ���
	void LoadWords(std::string inWords, FONT inTexture);
	void ReleaseAll();									// �S�Ă̔j��
	void Release(FONT inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetFont(std::string words,FONT inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	HFONT  m_hFont[FONT_MAX];
	LOGFONT m_lf[FONT_MAX];
	LPDIRECT3DTEXTURE9 m_texFont[FONT_MAX];	// �e�N�X�`���̏��
};

#endif // !_FONT_H_


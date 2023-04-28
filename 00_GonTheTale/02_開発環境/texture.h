//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//���̃}�N����`������ĂȂ�������
#define _TEXTURE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

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
class CTexture
{
public: /* ��` */
	enum TEXTURE
	{
		TEXTURE_GON = 0,//�e�X�g

		TEXTURE_LOOKON,//TITLE
		TEXTURE_FOXTITLE,
		TEXTURE_TITLE,
		TEXTURE_TITLEGAME,
		TEXTURE_TITLETUTORIAL,
		TEXTURE_TITLERANKIN,
		TEXTURE_TITLEEND,

		TEXTURE_RESULT_GON,//

		TEXTURE_TUTORIAL001,//�`���[�g���A��
		TEXTURE_TUTORIAL002,//�`���[�g���A��
		
		TEXTURE_PAUSEBG,//PAUSE
		TEXTURE_PAUSEGAME,
		TEXTURE_PAUSERETURN,
		TEXTURE_PAUSETITLE,
		TEXTURE_PAUSEMENU,

		TEXTURE_RANKINBG,
		TEXTURE_RANKIN,
		TEXTURE_RANKINTITLEOFF,
		TEXTURE_RANKINTITLEON,

		TEXTURE_NAMEBG,
		TEXTURE_NAMETITLE,

		TEXTURE_SCORE,
		TEXTURE_ALPHABET,

		TEXTURE_GONBOX,
		TEXTURE_GONLIFE,
		TEXTURE_LINE,
		TEXTURE_BOSS,
		TEXTURE_RT,
		TEXTURE_ATTACK,
		TEXTURE_GAMECLEAR,
		TEXTURE_KOUGE,
		TEXTURE_LOOK,
		TEXTURE_ITEM,
		TEXTURE_RUN,
		TEXTURE_MAX,
		TEXTURE_NONE,	// �g�p���Ȃ�
	};

	static const char* s_FileName[];	// �t�@�C���p�X

public:
	CTexture();		// �f�t�H���g�R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

public: /* �����o�֐� */
	void LoadAll();										// �S�Ă̓ǂݍ���
	void Load(TEXTURE inTexture);						// �w��̓ǂݍ���
	void ReleaseAll();									// �S�Ă̔j��
	void Release(TEXTURE inTexture);					// �w��̔j��
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// ���̎擾

private: /* �����o�ϐ� */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// �e�N�X�`���̏��
};

#endif // !_TEXTURE_H_

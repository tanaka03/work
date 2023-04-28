//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "manager.h"
#include "texture.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const char* CTexture::s_FileName[] =
{// �e�N�X�`���̃p�X

	"data/TEXTURE/gon.png",
	
	"data/TEXTURE/MagicCircle1.png",
	"data/TEXTURE/gamestart.png",
	"data/TEXTURE/GonBG.png",
	"data/TEXTURE/start.png",
	"data/TEXTURE/tutorial.png",
	"data/TEXTURE/ranking.png",
	"data/TEXTURE/end.png",
	
	"data/TEXTURE/GANECLEAR.png",
	
	"data/TEXTURE/tutorial001.png",
	"data/TEXTURE/tutorial002.png",

	"data/TEXTURE/sky_00290.png",
	"data/TEXTURE/pause000.png",
	"data/TEXTURE/pause001.png",
	"data/TEXTURE/pause002.png",
	"data/TEXTURE/pause004.png",

	"data/TEXTURE/rankingbg.png",
	"data/TEXTURE/ranking_rank.png",
	"data/TEXTURE/ranking000.png",
	"data/TEXTURE/ranking001.png",
	
	"data/TEXTURE/BG.png",
	"data/TEXTURE/NameSet000.png",

	
	"data/TEXTURE/Score001.png",
	"data/TEXTURE/alphabet_ucase.png",
	"data/TEXTURE/gonText.png",
	"data/TEXTURE/haat.png",
	"data/TEXTURE/line.png",
	"data/TEXTURE/enemy_fox.png",
	"data/TEXTURE/RT.png",
	"data/TEXTURE/ken.png",

	"data/TEXTURE/gameover.png",
	"data/TEXTURE/attack.png",
	"data/TEXTURE/search.png",
	"data/TEXTURE/item.png",
	"data/TEXTURE/escape.png",
};

static_assert(sizeof(CTexture::s_FileName) / sizeof(CTexture::s_FileName[0]) == CTexture::TEXTURE_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// �S�Ă̓ǂݍ���
//--------------------------------------------------
void CTexture::LoadAll()
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// �e�N�X�`���̓ǂݍ��݂�����Ă���
			continue;
		}

		// �e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// �ǂݍ���
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// �e�N�X�`���̓ǂݍ��݂�����Ă���
		return;
	}

	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// �e�N�X�`���̉��
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// �e�N�X�`���̉��
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// �e�N�X�`�����g�p���Ȃ�
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// �ǂݍ���
	Load(inTexture);

	return s_pTexture[inTexture];
}

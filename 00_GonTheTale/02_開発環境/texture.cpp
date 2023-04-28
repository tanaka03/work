//**************************************************
// 
// texture.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "manager.h"
#include "texture.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const char* CTexture::s_FileName[] =
{// テクスチャのパス

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
// デフォルトコンストラクタ
//--------------------------------------------------
CTexture::CTexture() :
	s_pTexture()
{
	memset(s_pTexture, 0, sizeof(s_pTexture));
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTexture::~CTexture()
{
}

//--------------------------------------------------
// 全ての読み込み
//--------------------------------------------------
void CTexture::LoadAll()
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != nullptr)
		{// テクスチャの読み込みがされている
			continue;
		}

		// テクスチャの読み込み
		D3DXCreateTextureFromFile(pDevice,
			s_FileName[i],
			&s_pTexture[i]);
	}
}

//--------------------------------------------------
// 読み込み
//--------------------------------------------------
void CTexture::Load(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != nullptr)
	{// テクスチャの読み込みがされている
		return;
	}

	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,
		s_FileName[inTexture],
		&s_pTexture[inTexture]);
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CTexture::ReleaseAll(void)
{
	for (int i = 0; i < TEXTURE_MAX; ++i)
	{
		if (s_pTexture[i] != NULL)
		{// テクスチャの解放
			s_pTexture[i]->Release();
			s_pTexture[i] = NULL;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CTexture::Release(TEXTURE inTexture)
{
	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	if (s_pTexture[inTexture] != NULL)
	{// テクスチャの解放
		s_pTexture[inTexture]->Release();
		s_pTexture[inTexture] = NULL;
	}
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE inTexture)
{
	if (inTexture == TEXTURE_NONE)
	{// テクスチャを使用しない
		return nullptr;
	}

	assert(inTexture >= 0 && inTexture < TEXTURE_MAX);

	// 読み込み
	Load(inTexture);

	return s_pTexture[inTexture];
}

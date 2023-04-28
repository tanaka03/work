//**************************************************
// 
// texture.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _TEXTURE_H_	//このマクロ定義がされてなかったら
#define _TEXTURE_H_	//２重インクルード防止のマクロ定義

//==================================================
// インクルード
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")

//==================================================
// 定義
//==================================================
class CTexture
{
public: /* 定義 */
	enum TEXTURE
	{
		TEXTURE_GON = 0,//テスト

		TEXTURE_LOOKON,//TITLE
		TEXTURE_FOXTITLE,
		TEXTURE_TITLE,
		TEXTURE_TITLEGAME,
		TEXTURE_TITLETUTORIAL,
		TEXTURE_TITLERANKIN,
		TEXTURE_TITLEEND,

		TEXTURE_RESULT_GON,//

		TEXTURE_TUTORIAL001,//チュートリアル
		TEXTURE_TUTORIAL002,//チュートリアル
		
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
		TEXTURE_NONE,	// 使用しない
	};

	static const char* s_FileName[];	// ファイルパス

public:
	CTexture();		// デフォルトコンストラクタ
	~CTexture();	// デストラクタ

public: /* メンバ関数 */
	void LoadAll();										// 全ての読み込み
	void Load(TEXTURE inTexture);						// 指定の読み込み
	void ReleaseAll();									// 全ての破棄
	void Release(TEXTURE inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetTexture(TEXTURE inTexture);	// 情報の取得

private: /* メンバ変数 */
	LPDIRECT3DTEXTURE9 s_pTexture[TEXTURE_MAX];	// テクスチャの情報
};

#endif // !_TEXTURE_H_

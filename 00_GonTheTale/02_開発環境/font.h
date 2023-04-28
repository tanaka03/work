//**************************************************
// 
// フォント
// Author  : HamadaRyuuga
// 
//**************************************************
#ifndef _FONT_H_	//このマクロ定義がされてなかったら
#define _FONT_H_	//２重インクルード防止のマクロ定義

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
class CFont
{
public: /* 定義 */
	enum FONT
	{
		FONT_GON = 0,
		FONT_MEIRIO,
		FONT_SOUEIKAKU,
		FONT_MAX,
		FONT_NONE,	// 使用しない
	};

	static const char* s_FileName[];	// ファイルパス

	static const char* s_FontName[];	// ファイルパス
public:
	CFont();		// デフォルトコンストラクタ
	~CFont();	// デストラクタ

public: /* メンバ関数 */
	void Load(FONT inTexture);						// 指定の読み込み
	void LoadWords(std::string inWords, FONT inTexture);
	void ReleaseAll();									// 全ての破棄
	void Release(FONT inTexture);					// 指定の破棄
	LPDIRECT3DTEXTURE9 GetFont(std::string words,FONT inTexture);	// 情報の取得

private: /* メンバ変数 */
	HFONT  m_hFont[FONT_MAX];
	LOGFONT m_lf[FONT_MAX];
	LPDIRECT3DTEXTURE9 m_texFont[FONT_MAX];	// テクスチャの情報
};

#endif // !_FONT_H_


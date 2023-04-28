//=============================================================================
//
// レンダラー
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _MANEAGER_H_			// このマクロ定義がされてなかったら
#define _MANEAGER_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
 
class CRenderer;
class CInput;
class CTexture;
class CObject;
class CResult;
class CGame;
class CFade;
class CSound;
class CFont;

HWND GetWnd(void);

class CManager
{
public:
	//画面(モード)の種類
	enum LEVEL
	{
		LEVEL_EASY = 0,			//ゲーム画面	
		LEVEL_NORMAL,
		LEVEL_HARD,		//ランキング画面
		LEVEL_END,
		LEVEL_MAX
	};

	static const D3DXVECTOR3 centerPos;

	//画面(モード)の種類
	enum MODE
	{
		MODE_TITLE = 0,		//タイトル画面
		MODE_GAME,			//ゲーム画面
		MODE_RESULT,		//リザルト画面
		MODE_FADE,			//フェード画面
		MODE_RANKING,		//ランキング画面
		MODE_GAMEOVER,
		MODE_TUTORIAL,
		MODE_NAMESET,
		MODE_MAX
	};

public: // 静的メンバー変数
	static CManager* m_manager;

public: // 静的関数
	static CManager* GetInstance();
	
private: // シングルトン
	CManager();

public:	// メンバー関数
	~CManager();

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CRenderer *GetRenderer();
	CTexture* GetTexture();	// テクスチャの情報の取得
	CFade* GetFade();	// 
	MODE* GetMode();	//
	void SetMode(CManager::MODE mode);
	CSound * GetSound();


	CFont * GetFont();


	static LEVEL* GameLevel() { return m_Level; }
	static void SetLevel(LEVEL* Level) { m_Level = Level; }
	static LEVEL* m_Level;

private:
	CTexture *m_pTexture;
	CRenderer * m_cRenderer;
	CFade* m_Fade;
	CObject*m_Game;
	CSound*m_Sound;
	MODE m_mode;
	CInput *m_Input;

	CFont *m_pFont;
};



#endif

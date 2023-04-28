//============================
//
// ゲーム画面のヘッダー
// Author:hamada ryuuga
//
//============================
#ifndef _GAME_H_		//このマクロが定義されてなかったら
#define _GAME_H_		//2重インクルード防止のマクロ定義

#include "object.h"

class CPause; 
class CPlayer;

class CGame :public CObject
{
public:
	CGame();
	~CGame();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CPause * GetPause() { return m_Pause; };

//	static CScore*GetScore() { return pScore; };

	static int GetGameScore() { return m_GameScore; };

	static CPlayer* GetPlayer() { return m_Player; };
	
private:
	static CPause *m_Pause;
	static int m_GameScore;
	int m_GameCount;
	int m_SpeedUp;
	int m_nCntSpawn;
	static CPlayer* m_Player;
	
};
#endif
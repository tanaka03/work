//=============================================================================
//
// 画面統括設定
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _SELECT_H_			// このマクロ定義がされてなかったら
#define _SELECT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object.h"

class CPopUi;
class CAttack;
class C3dbase;
class CScore;
class CReaction;
class CTimer;
class CBossbar;
class CSelect : public CObject
{
public:
	
	enum PlayerEvent
	{
		PlayerEvent_Attack = 0,
		PlayerEvent_Minor,
		PlayerEvent_Item,
		PlayerEvent_Miss,
		PlayerEvent_MAX,
	};


	CSelect();
	~CSelect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CSelect* Create();

	bool GetReaction() { return m_IsReaction; }
	bool GetEnemyAttackFaze() { return m_EnemyAttackFaze; }
	bool GetLogOn() { return m_LogOn; }
	//イベントのゲット
	PlayerEvent GetActionType() { return m_Event; }

	CTimer* GetTimer() { return m_Timer; };
private:
	static const int Max = 3;
	static const int AttackSetMax = 15;
	//白い枠基本のサイズ
	const D3DXVECTOR2 defaultSize = D3DXVECTOR2(1000.0f, 200.0f);
	const D3DXVECTOR3 defaultPos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	//こちらの攻撃の基本のサイズ
	const D3DXVECTOR2 AttackdefaultSize = D3DXVECTOR2(1000.0f, 200.0f);
	const D3DXVECTOR3 AttackdefaultPos = D3DXVECTOR3(0.0f, -50.0f, 0.0f);
	
	//相手の攻撃の基本のサイズ
	const D3DXVECTOR2 ReactiondefaultSize = D3DXVECTOR2(300.0f,300.0f);
	const D3DXVECTOR3 ReactiondefaultPos = D3DXVECTOR3(0.0f, -100.0f, 0.0f);
	
	int m_Attackvariation;
	int m_ColarTimer;

	CAttack*m_Attack[Max];
	CPopUi*m_Select[PlayerEvent_MAX];
	C3dbase*m_3dbase;
	PlayerEvent m_Event;
	CScore * m_Score;
	CReaction* m_Reaction;
	CTimer* m_Timer;
	C3dbase* m_Boss;
	C3dbase* m_NowType;

	float m_Difference;
	bool m_IsSelect;
	bool m_IsReaction;

	bool m_EnemyAttackFaze;
	bool m_LogOn;
	void EventAttackInit();
	void EventAttackUninit();
	void EventAttackUpdate();

	CAttack*m_EnemyAttack;
	int m_nEnemyAttackTime;
	D3DXVECTOR3 m_EnemyAttackMove;
	int EAttackSetNum;

	struct EAttack
	{
		int nEnemyAttackCount;
		int nDelay;
		int nCreateTime;
		int nEndTime;
	};

	EAttack AttackSet[AttackSetMax];
	int m_AttackPattern;
	bool m_bReturnEffect;
	bool m_bReturn;
	int m_bReturnTime;
	bool Return;
	bool m_deathCheck;

	void EnemyAttackInit();
	bool SetEnemyAttack(int Setnum, int CreateTime, int EndTime, int Num, int Delay, D3DXVECTOR3 Pos, D3DXVECTOR3 Move, D3DXVECTOR3 Size, D3DXCOLOR Col, bool Collision);


	void EventbackEffect();

	float m_Rot;

	CBossbar* m_Hp;
};
#endif

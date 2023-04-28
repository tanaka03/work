//=============================================================================
//
// プレイヤー設定ヘッター
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "3dpolygon.h"
//-----------------------------------------------------------------------------
// 前方宣言
//-----------------------------------------------------------------------------

class CHpNumber;
class CBossbar;
class CSelect;
class CEvent;
//-----------------------------------------------------------------------------
// プレイヤー操作キャラクタークラス
//-----------------------------------------------------------------------------
class CPlayer : public C3dpolygon
{
public:


public: // 定数
	static const int MAXLIFE;				// 最大体力
	static const float MOVE_ATTENUATION;	// 減衰係数
	static const float MOVE_ROTATTENUATION;	// 回転移動減衰係数
	static const float SPEED;				// スピード
	static const float SPEEDMAX;				// スピード
	static const float WIDTH;				// モデルの半径
	static const int MAX_PRAYER;			// 最大数
	static const int MAX_MOVE;				// アニメーションの最大数
	static const int INVINCIBLE;			// 無敵時間
	static const int MAX_MODELPARTS;		// モデルの最大数
	static const int HP;				// HP

	enum PlayerType
	{
		DEFAULT_MOVE = 0,	// 基本の動き
		GRAVITY_MOVE,		// 重力で落ちるやつ
		MAX			// あんただれや？
	};

public:
	CPlayer(const int list);;
	~CPlayer();

	HRESULT Init()override;	// 初期化
	void Uninit()override;	// 破棄
	void Update()override;	// 更新
	void Draw()override;	// 描画

	static CPlayer *Create();
	//------------------------------------
	//座標の差分を取るやつ 
	//------------------------------------
	void SetDifferenceMove(D3DXVECTOR3 move) { m_move = move - m_pos; }
	void SetNowType(PlayerType Type) { m_NowType = Type; }
	void DamageHit(int Damage);

	static int GetHPNow() { return m_HPNow; }
private:
	void Move();		// 移動
	void GravityMove();		// 重力あり移動
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_posOld;

	//感知範囲
	D3DXVECTOR2 m_wallmin;
	D3DXVECTOR2 m_wallmax;

	static int m_HPNow;
	int m_jumpCount;
	bool m_loolHit;
	bool m_attack;
	bool m_jump;
	bool m_isDaesh;

	PlayerType m_NowType;

	CSelect*m_Select;
	CEvent *m_Event;
	std::vector<D3DXVECTOR3> m_logPos;
	CBossbar* m_Hp;
	CHpNumber* m_HpNumber;
};
#endif

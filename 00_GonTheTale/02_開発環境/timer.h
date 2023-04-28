//==================================================
// timer.h
// Author: tutida ryousei
//==================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include"object.h"

class CNumber;
class CObject2d;

class CTimer : public CObject
{
public:
	CTimer();
	~CTimer();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time);
	void SetTimer();		// タイマーの設定
	void ZeroAlpha();		// 先頭の0を消す
	void AddTime(int add);	// 時間の加算

							// セッター
	void SetDestPos(D3DXVECTOR3 destpos) { m_DestPos = destpos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetTimer(int time) { m_nTime = time; }

	// ゲッター
	bool GetTimeUp() { return m_bTimeUp; }
	int GetTime() { return m_nTime; }
	static int GetMyScore() { return m_Myscore; };
private:
	static const int m_nNumTimer = 3;	// タイマーの桁数
	int m_nTime;						// 時間
	static int m_Myscore;						// 時間
	int m_nFrameCount;					// フレームカウント
	int m_nZeroCount;					// 先頭の0の数
	int m_aPosTexU[m_nNumTimer];		// 各桁の格納先
	bool m_bCountType;					// カウントアップかカウントダウンか
	bool m_bTimeUp;						// タイムアップしたか
	D3DXVECTOR3 m_Pos;					// 位置
	D3DXVECTOR3 m_TimePos;				// 時計の位置
	D3DXVECTOR3 m_DestPos;				// 目的の位置
	D3DXVECTOR3 m_size;					// サイズ
	CNumber *m_pNumber[m_nNumTimer];	// 数字の情報
	CObject2d *m_pObject2D;				// オブジェクト2Dの情報
};

#endif // !_TIMER_H_

//==================================================
// timer.h
// Author: tutida ryousei
//==================================================
#ifndef _HPNUMBER_H_
#define _HPNUMBER_H_

#include"object.h"

class CNumber;
class CObject2d;

class CHpNumber : public CObject
{
public:
	CHpNumber();
	~CHpNumber();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CHpNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time);
	void SetNumber();		// タイマーの設定
	void ZeroAlpha();		// 先頭の0を消す
	void AddNumber(int add);	// 時間の加算

							// セッター
	void SetDestPos(D3DXVECTOR3 destpos) { m_DestPos = destpos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetNumber(int time) { m_nNumber = time; }

	// ゲッター
	bool GetNumberUp() { return m_bNumberUp; }
	int GetNumber() { return m_nNumber; }

private:
	static const int m_nNumNumber = 3;	// タイマーの桁数
	int m_nNumber;						// 時間
	int m_nFrameCount;					// フレームカウント
	int m_nZeroCount;					// 先頭の0の数
	int m_aPosTexU[m_nNumNumber];		// 各桁の格納先
	bool m_bCountType;					// カウントアップかカウントダウンか
	bool m_bNumberUp;						// タイムアップしたか
	D3DXVECTOR3 m_Pos;					// 位置
	D3DXVECTOR3 m_NumberPos;				// 時計の位置
	D3DXVECTOR3 m_DestPos;				// 目的の位置
	D3DXVECTOR3 m_size;					// サイズ
	CNumber *m_pNumber[m_nNumNumber];	// 数字の情報
	CObject2d *m_pObject2D;				// オブジェクト2Dの情報
};

#endif // !_TIMER_H_

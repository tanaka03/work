//============================
//
// Ç»Ç‹Ç¶Ç´ÇﬂÇÈÇ‚Å[Ç¬
// Author:hamada ryuuga
//
//============================

#ifndef _NAME_H_
#define _NAME_H_

#include "object2d.h"



class CName : public CObject2d
{
public:

	enum ALPHABET
	{
		A = 0,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,
		MAX
	};

	CName(int list);
	~CName();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CName* Create();
	void SetAlphabet(const ALPHABET Alphabet);
	void SetMoveSwitch(bool move);
	ALPHABET GetAlphabet();


private:
	D3DXCOLOR col;
	int m_DesTimarMax;
	int m_DesTimar;

	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	ALPHABET m_type;

	bool m_move;

};


#endif
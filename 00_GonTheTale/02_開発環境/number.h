//============================
//
// NUMBER
// Author:hamada ryuuga
//
//============================
#ifndef _NUMBER_H_
#define _NUMBER_H_

#include "object2d.h"

class CNumber : public CObject2d
{
public:
	CNumber(int list);
	~CNumber();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CNumber* Create();
	
	void SetSpeed(float Speed) { m_speed = Speed; }
	void SetNumber(int Number) { m_MyNumber = Number; }
	void SetMove(bool Move) { m_move = Move; }
	
	void Releasetimer(int nTimar);

	// セッター
	void SetNumCol(D3DXCOLOR *col) { SetColar(*col); }
	void SetNumSize(D3DXVECTOR3 size) { SetSize(size); }
	void SetNumTexture(CTexture::TEXTURE pTexture);
private:
	D3DXCOLOR m_col;
	float m_speed;
	int m_DesTimarMax;
	int m_DesTimar;
	int m_MyNumber;
	bool m_isRelease;
	bool m_move;
	
};

#endif
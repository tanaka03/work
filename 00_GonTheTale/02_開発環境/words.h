//============================
//
//  もじ設定ヘッター
// Author:hamada ryuuga
//
//============================
#ifndef _WORDS_H_
#define _WORDS_H_

#include "main.h"
#include "object.h"
#include "font.h"

class CWords : public CObject
{
	const D3DXVECTOR3 CWords::m_Vtx[4] =
	{
		D3DXVECTOR3(-1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, -1.0f, 0.0f),
		D3DXVECTOR3(-1.0f, +1.0f, 0.0f),
		D3DXVECTOR3(+1.0f, +1.0f, 0.0f),
	};
public:
	CWords(int list = 0);
	~CWords() override;

	HRESULT Init(void)override;	// 初期化
	void Uninit(void)override;	// 破棄
	void Update(void)override;	// 更新
	void Draw()override;	// 描画
	static CWords *CWords::Create(const char * Text, D3DXVECTOR3 pos, D3DXVECTOR3 Size, CFont::FONT Type);

	virtual const D3DXVECTOR3 *GetPos() const;

	virtual void SetPos(const D3DXVECTOR3 &pos);
	virtual void SetMove(const D3DXVECTOR3 &move);

	void SetColar(D3DXCOLOR Collar);

	D3DXCOLOR GetColar() { return m_col; };
	D3DXVECTOR3 GetSize() { return m_size; };

	void SetSize(D3DXVECTOR3 Size) { m_size = Size; };
	D3DXVECTOR3 &GetMove() { return m_move; };
	LPDIRECT3DVERTEXBUFFER9 &GetVtx() { return m_pVtxBuff; };
	void SetRot(D3DXVECTOR3 Rot) { m_rot = Rot; };
	void SetMoveRot(D3DXVECTOR3 inMoveRot) { m_moveRot = inMoveRot; };

private:
	void Setwords(const char*Text, CFont::FONT Type);

	int  m_nTimer;
	float m_nScale;
	D3DXVECTOR3 m_size;
	D3DXVECTOR3 m_move; //polygonの位置
	D3DXVECTOR3 m_pos; //polygonの位置
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_moveRot;
	D3DXCOLOR m_col;
	D3DXMATRIX m_mtxWorld;					// マトリックス
	const char *m_words;
	LPD3DXFONT m_pFont = nullptr;
	HFONT  m_hFont;
	std::string m_Text;
	std::string m_ALLText;
	LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;

	//void LoadFont(const char * Text);
};
#endif

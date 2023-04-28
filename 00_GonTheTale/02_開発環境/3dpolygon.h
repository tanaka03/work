//=============================================================================
//
// 3dpolygon
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _3DPOLYGON_H_			// このマクロ定義がされてなかったら
#define _3DPOLYGON_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "texture.h"
#include "object2d.h"

#define TIMER (m_nTimer + 90)

class  C3dpolygon : public CObject
{
protected:
	//polygonの基準サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:

	static C3dpolygon *Create(int list = 0);

	C3dpolygon(int list = 0);
	~C3dpolygon() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	virtual const D3DXVECTOR3 *GetPos() const;
	virtual void SetPos(const D3DXVECTOR3 &pos);
	virtual void SetMove(const D3DXVECTOR3 &move) { m_move = move; };
	
	void SetTexture(CTexture::TEXTURE texture);
	void SetTex(PositionVec4 Tex);
	void SetSize(const D3DXVECTOR3 &size);
	void SetColar(D3DXCOLOR Colar);
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; };
	LPDIRECT3DVERTEXBUFFER9 &GetVtx();

	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);

	static void PolygonReset() { m_MaxPolygon = 0; };

protected:
	float m_nScale;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_pos;		// polygonの位置
	D3DXVECTOR3 m_size;
	D3DXMATRIX m_mtxWorld;	// マトリックス
	int  m_nTimer;
	D3DXVECTOR3  m_move;
	D3DXCOLOR m_Colar;
private:
	static int m_MaxPolygon;
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = nullptr;
	CTexture::TEXTURE m_texture;	// テクスチャの列挙型

	/* アニメーション系統 */
	// 基本データ
	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;
	// 分割数
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;
	// 時間
	int m_animationSpeed;
	int m_AnimationSpeedCount;
	// 現在の時間
	int m_Timar;
	int m_TimaCount;
	// 条件
	bool m_OnAnimation;
	bool m_Loop;

};

#endif

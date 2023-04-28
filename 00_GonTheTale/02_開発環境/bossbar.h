//=============================================================================
//
// Bossばー
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _BOSSDAR_H_			// このマクロ定義がされてなかったら
#define _BOSSDAR_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object2d.h"
#include "texture.h"

class CBossbar : public CObject2d
{
private:
	static const int BOSSHP = 3000;
	//polygonの拡大サイズ
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CBossbar *Create(const D3DXVECTOR3 & pos, float Life);

	CBossbar(const int list);
	~CBossbar() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetMove(const D3DXVECTOR3 &move)override;

	void SetDamage(const int Damage);
	
	float Getlife() { return m_life; };
	static bool GetMaxLife() { return m_maxHp; };

private:
	float m_life;
	CObject2d *m_object2d[1];
	float m_maxLife;
	float m_defaultLife;
	static bool m_maxHp;
	D3DXVECTOR3 m_setUpPos;
};

#endif


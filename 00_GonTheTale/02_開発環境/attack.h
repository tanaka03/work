//=============================================================================
//
// 攻撃棒
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _ATTACK_H_			// このマクロ定義がされてなかったら
#define _ATTACK_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CAttack : public C3dpolygon
{
public:

	static CAttack *CAttack::Create();

	CAttack(const int list);
	~CAttack() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetCollision(bool collision) { m_bCollision = collision; }

private:
	bool m_bCollision;
	void move();
	bool collision(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 EnemySize);


};

#endif



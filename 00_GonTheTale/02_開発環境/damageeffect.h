//=============================================================================
//
// effectオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _DAMAGEEFFECT_H_			// このマクロ定義がされてなかったら
#define _DAMAGEEFFECT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CDamageEffect : public C3dpolygon
{
public:

	static CDamageEffect *CDamageEffect::Create(D3DXVECTOR3 Move);

	CDamageEffect(const int list);
	~CDamageEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(const int &Life) { m_life = Life; };

private:
	void move();
	int m_life;
};

#endif

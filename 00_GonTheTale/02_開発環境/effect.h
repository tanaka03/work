//=============================================================================
//
// effectオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _EFFECT_H_			// このマクロ定義がされてなかったら
#define _EFFECT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CEffect : public C3dpolygon
{
public:


	static CEffect *CEffect::Create(D3DXVECTOR3 Move);

	CEffect(const int list);
	~CEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetLife(const int &Life) { m_life = Life; };



private:
	void move();
	int m_life;
};

#endif

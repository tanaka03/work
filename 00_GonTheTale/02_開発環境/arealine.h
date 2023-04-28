//=============================================================================
//
//攻撃範囲
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _AREALINE_H_			// このマクロ定義がされてなかったら
#define _AREALINE_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CArealine : public C3dpolygon
{
public:


	static CArealine *CArealine::Create();

	CArealine(const int list);
	~CArealine() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;

	void SetDifferenceMove(D3DXVECTOR3 move);

	void SetSizeMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetSizeMove() { return m_SizeMove; }
private:
	const float Decrease = 0.5f;
	void move();

	D3DXVECTOR3 m_SizeMove;

};

#endif


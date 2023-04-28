//=============================================================================
//
// ただのオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _3DPOLYGONTEMPLATE_H_			// このマクロ定義がされてなかったら
#define _3DPOLYGONTEMPLATE_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class C3dbase : public C3dpolygon
{
public:


	static C3dbase *C3dbase::Create();

	C3dbase(const int list);
	~C3dbase() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;

	void SetSizeMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetSizeMove() { return m_SizeMove; }

private:
	const float Decrease = 0.5f;
	D3DXVECTOR3 m_SizeMove;
	void move();

};

#endif

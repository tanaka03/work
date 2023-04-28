//=============================================================================
//
// Uiオブジェクト
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _POPUI_H_			// このマクロ定義がされてなかったら
#define _POPUI_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CPopUi : public C3dpolygon
{
public:


	static CPopUi *CPopUi::Create();

	CPopUi(const int list);
	~CPopUi() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;


private:
	void move();
	D3DXVECTOR3 m_move;

};

#endif


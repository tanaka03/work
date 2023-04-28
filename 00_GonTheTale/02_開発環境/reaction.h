//=============================================================================
//
// 攻撃設定
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _REACTION_H_			// このマクロ定義がされてなかったら
#define _REACTION_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"
#include "object.h"

class CArealine;
class CReaction : public CObject
{
public:
	CReaction();
	~CReaction() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CReaction* Create();

	void AreaSize(D3DXVECTOR3 Pos, D3DXVECTOR2 Size);
private:
	CArealine*m_area[4];
};
#endif

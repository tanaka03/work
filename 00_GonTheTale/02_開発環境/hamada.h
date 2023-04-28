//=============================================================================
//
// 便利関数
// Author : 浜田琉雅
//
//=============================================================================

#ifndef _HAMADA_H_			// このマクロ定義がされてなかったら
#define _HAMADA_H_			// 二重インクルード防止のマクロ定義


#include "renderer.h"

namespace hmd
{
	D3DXMATRIX *giftmtx(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool Billboard = false);
	D3DXMATRIX *giftmtxQuat(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXQUATERNION Quat, bool Billboard = false);
	float easeInSine(float X);
	float easeInQuad(float X);
	bool is_sjis_lead_byte(int c);
}



#endif

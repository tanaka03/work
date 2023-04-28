//=============================================================================
//
// 便利関数
// Author : 浜田琉雅
//
//=============================================================================

#include "hamada.h"
#include "manager.h"
#include "renderer.h"
namespace hmd
{
	D3DXMATRIX *giftmtx(D3DXMATRIX *pOut,D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool Billboard);
	D3DXMATRIX *giftmtxQuat(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXQUATERNION Quat, bool Billboard);
	float easeInSine(float X);
	float easeInQuad(float X);
	bool is_sjis_lead_byte(int c);
}

///=============================================================================
//マトリックスを回転させるやつ
//=============================================================================
D3DXMATRIX *hmd::giftmtx(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool Billboard)
{
	// TODO: 関数化する
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(pOut);


	if (Billboard)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//Ｚ軸で回転しますちなみにm_rotつかうとグルグル回ります
		pOut->_11 = mtxView._11;
		pOut->_12 = mtxView._21;
		pOut->_13 = mtxView._31;
		pOut->_31 = mtxView._13;
		pOut->_32 = mtxView._23;
		pOut->_33 = mtxView._33;

	}

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.x, rot.y, rot.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);
	return pOut;
}

///=============================================================================
//マトリックスを回転させるやつ
//=============================================================================
D3DXMATRIX *hmd::giftmtxQuat(D3DXMATRIX *pOut, D3DXVECTOR3 pos, D3DXQUATERNION Quat, bool Billboard)
{
	// TODO: 関数化する
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans, mtxView;

	// ワールドマトリックスの初期化
	// 行列初期化関数(第1引数の行列を単位行列に初期化)
	D3DXMatrixIdentity(pOut);


	if (Billboard)
	{
		LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

		pDevice->GetTransform(D3DTS_VIEW, &mtxView);
		//Ｚ軸で回転しますちなみにm_rotつかうとグルグル回ります
		pOut->_11 = mtxView._11;
		pOut->_12 = mtxView._21;
		pOut->_13 = mtxView._31;
		pOut->_31 = mtxView._13;
		pOut->_32 = mtxView._23;
		pOut->_33 = mtxView._33;

	}

	// クォータニオンの使用した姿勢の設定
	D3DXMatrixRotationQuaternion(&mtxRot, &Quat);            // クオータニオンによる行列回転
	D3DXMatrixMultiply(pOut, pOut, &mtxRot);    // 行列掛け算関数(第2引数×第3引数第を１引数に格納)

	// 位置を反映
	// 行列移動関数(第１引数にX,Y,Z方向の移動行列を作成)
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	// 行列掛け算関数(第2引数×第3引数第を１引数に格納)
	D3DXMatrixMultiply(pOut, pOut, &mtxTrans);
	return pOut;
}

//
//イージング
//
float hmd::easeInSine(float X)
{
	return 1 - cos((X * D3DX_PI) / 2);
}

float hmd::easeInQuad(float X)
{
	return X * X;
}

//=============================================================================
//1バイト文字をシフトJISかどうか判定する関数
//=============================================================================
bool hmd::is_sjis_lead_byte(int c)
{
	return (((c & 0xffu) ^ 0x20u) - 0xa1) < 94u / 2;
}
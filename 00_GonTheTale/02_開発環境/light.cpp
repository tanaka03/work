//=========================================
// 
// ライトの作成
// Author HAMAD
// 
//=========================================
//------------------------------------
// include
//------------------------------------
#include "manager.h"
#include "renderer.h"
#include "light.h"


//=========================================
// コンストラクト
//=========================================
CLight::CLight()
{
}

//=========================================
// デストラクト
//=========================================
CLight::~CLight()
{

}


//=========================================
// 初期化
//=========================================
void CLight::Init(void)
{
	// ライトをクリアする
	ZeroMemory(m_light, sizeof(m_light));

	// ライトの設定
	Set(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 0);
	Set(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 1.0f), 1);
	//Set(D3DLIGHT_DIRECTIONAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), 2);

	// デバイスへのポインタの取得
	CManager::GetInstance()->GetRenderer()->GetDevice()->SetRenderState(D3DRS_AMBIENT, 0xffffffff);
}

//=========================================
// 終了
//=========================================
void CLight::Uninit(void)
{
}

//=========================================
// 更新
//=========================================
void CLight::Update(void)
{
}

//=========================================
// 設定
//=========================================
void CLight::Set(D3DLIGHTTYPE type,D3DXCOLOR col, D3DXVECTOR3 vec, int nNum)
{
	// デバイスへのポインタの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;		// ライトの方向ベクトル

	m_light[nNum].Type = type;	// ライトの種類を設定 ( 平行光源 )
	m_light[nNum].Diffuse = col;	// ライトの拡散光を設定 ( ライトの色 )

	vecDir = vec;	// ライトの方向を設定

	// 正規化する ( 大きさ 1 のベクトルにする )
	D3DXVec3Normalize(&vecDir, &vecDir);
	m_light[nNum].Direction = vecDir;

	// ライトを設定する
	pDevice->SetLight(nNum, &m_light[nNum]);

	// ライトを有効にする
	pDevice->LightEnable(nNum, TRUE);

}
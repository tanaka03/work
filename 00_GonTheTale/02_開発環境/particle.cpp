// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
// effect.cpp
// ＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#include "particle.h"
#include "main.h"

#include "utility.h"
#include "renderer.h"
#include "manager.h"
#include <assert.h>

//==================================================
// 静的メンバー変数
//==================================================

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CParticle::CParticle() : 
	m_data({})
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CParticle::~CParticle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CParticle::Init()
{
	CObject2d::Init();
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CParticle::Uninit()
{
	CObject2d::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CParticle::Update()
{
	CObject2d::Update();


	/* ↓使用しているなら↓ */

	// エフェクトの移動
	m_pos += m_data.move;

	// 推移
	m_data.nLife--;							// 体力の減少
	m_data.move.y += m_data.fWeight;			// 重力
	m_data.move *= m_data.fAttenuation;			// 移動量の推移
	m_data.fWeight += m_data.fWeightTransition;	// 重さの推移
	m_data.move.x -= 0.1f;
	D3DXCOLOR myColor = CObject2d::GetCollar();
	if (m_data.color.bColTransition)
	{// 色の推移
		if (m_data.color.nEndTime >= m_data.color.nCntTransitionTime)
		{
			m_data.color.nCntTransitionTime++;
			myColor.r += m_data.color.colTransition.r;
			myColor.g += m_data.color.colTransition.g;
			myColor.b += m_data.color.colTransition.b;
			//myColor.a += m_data.color.colTransition.a;
		}
	}
	myColor.a -= 1.0f / m_data.nMaxLife;

	SetPos(m_pos);
	SetCollar(D3DXCOLOR(myColor.r, myColor.g, myColor.b, myColor.a));
	SetSize(D3DXVECTOR3(m_data.fWidth, m_data.fWidth,0.0f));

	if (m_data.nLife <= 0)
	{// エフェクトの寿命
		Release();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CParticle::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();	// デバイスの取得

	switch (m_data.alphaBlend)
	{
	case TYPE_NONE:	// 乗算
		break;

	case TYPE_ADD:	// 加算
		// αブレンディングを加算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		break;

	case TYPE_SUB:	// 減算
		// αブレンディングを減算合成に設定
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

	default:
		assert(false);
		break;
	}

	CObject2d::Draw();

	// αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	// テクスチャを引き継がない
	pDevice->SetTexture(0, NULL);
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CParticle* CParticle::Create(const Info& inParticle, const D3DXVECTOR3& inPos)
{
	CParticle* particle = nullptr;
	if (particle == nullptr)
	{
		particle = new CParticle;
		particle->Init();
		
		particle->SetSize(D3DXVECTOR3(particle->m_data.fWidth, particle->m_data.fWidth,0.0f));
		particle->SetPos(inPos);
		particle->m_data = inParticle;
		//particle->SetTexture(particle->m_data.nIdxTex);
		particle->SetCollar(D3DXCOLOR(particle->m_data.color.colBigin.r, particle->m_data.color.colBigin.g, particle->m_data.color.colBigin.b, particle->m_data.color.colBigin.a));
		
		particle->CObject2d::SetTexture(CTexture::TEXTURE_SMOKE);

		return particle;
	}
	return nullptr;
}

//--------------------------------------------------
// テクスチャの読込み
//--------------------------------------------------
void CParticle::LoadTex()
{

}

//--------------------------------------------------
// float を DWORD に変換
//--------------------------------------------------
DWORD CParticle::FloattoDword(float fVal)
{
	return *((DWORD*)&fVal);
}

//============================
//
// BOSSばー
// Author:hamada ryuuga
//
//============================

#include "bossbar.h"
#include "hamada.h"
#include "manager.h"
#include "player.h"
#include "game.h"


bool CBossbar::m_maxHp;
//=============================================================================
// コンストラクタ
//=============================================================================
CBossbar::CBossbar(int list) :CObject2d(list)
{
	m_object2d[0] = nullptr;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBossbar::~CBossbar()
{
}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CBossbar::Init()
{
	CObject2d::Init();
	m_maxLife = 0;
	//m_object2d[0] = CObject2d::Create(PRIORITY_EFFECT);
	////m_object2d[0]->SetTexture(CTexture::TEXTURE_BOSSHP);
	//m_object2d[0]->SetSize(D3DXVECTOR3(((m_defaultLife)*2.5f)+4.1f, 50.0f, 0.0f));
	//m_object2d[0]->SetPos(D3DXVECTOR3(m_setUpPos.x, m_pos.y - 20.0f, m_pos.z));
	
	m_life = 0;
	return E_NOTIMPL;
}

//=============================================================================
// 終了
//=============================================================================
void CBossbar::Uninit()
{

	CObject2d::Uninit();

}

//=============================================================================
// 更新
//=============================================================================
void CBossbar::Update()
{
	if (m_maxLife < m_defaultLife)
	{
		m_maxLife += 10;
		SetDamage(-10);
	}
	else
	{
		SetColar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		m_maxHp = true;
	}
	if (m_life >= m_defaultLife*0.5)
	{
		SetColar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}
	if (m_life <= m_defaultLife / 2.0f)
	{
		SetColar(D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	if (m_life <= m_defaultLife / 10.0f)
	{
		SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}

	m_size.x += m_move.x;
	m_pos.x -= m_move.x;
	m_move = { 0.0f,0.0f,0.0f };
	CObject2d::Update();
}

//=============================================================================
// 描画
//=============================================================================
void CBossbar::Draw()
{
	LPDIRECT3DDEVICE9 	 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	CObject2d::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create
//=============================================================================
CBossbar *CBossbar::Create(const D3DXVECTOR3 & pos, float Life)
{
	CBossbar * pObject = nullptr;
	pObject = new CBossbar(PRIORITY_EFFECT);

	if (pObject != nullptr)
	{
		pObject->m_setUpPos = pos;
		pObject->SetPos(D3DXVECTOR3(pos.x+(Life), pos.y, pos.z));
		pObject->m_defaultLife = Life;
		pObject->Init();
		pObject->SetSize(D3DXVECTOR3(0.0f, 20.0f, 0.0f));
		pObject->SetColar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
		pObject->SetTexture(CTexture::TEXTURE_NONE);
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	return pObject;
}

//=============================================================================
// Get＆Set 
//=============================================================================

void CBossbar::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

void CBossbar::SetMove(const D3DXVECTOR3 & move)
{
	m_move = move;
}

void CBossbar::SetDamage(const int Damage)
{
	m_move.x -= Damage;
	m_life -= Damage;
}

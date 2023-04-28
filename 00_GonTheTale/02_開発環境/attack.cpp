//============================
//
// 攻撃棒
// Author:hamada ryuuga
//
//============================

#include "attack.h"
#include "hamada.h"
#include "manager.h"
#include "player.h"
#include "game.h"
//------------------------------------
// コンストラクタ
//------------------------------------
CAttack::CAttack(int list) :C3dpolygon(list)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CAttack::~CAttack()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CAttack::Init()
{
	C3dpolygon::Init();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3	Size(50.0f, 50.0f, 50.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetSize(Size);
	SetTexture(CTexture::TEXTURE_NONE);//テクスチャ選択
	SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//座標設定
	SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));//色設定
	SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//moveの設定
	return E_NOTIMPL;
}

//------------------------------------
// 終了
//------------------------------------
void CAttack::Uninit()
{
	C3dpolygon::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CAttack::Update()
{
	CPlayer*Player = CGame::GetPlayer();
	D3DXVECTOR3 Pos = *Player->GetPos();
	D3DXVECTOR3 Size = { CPlayer::WIDTH,CPlayer::WIDTH,CPlayer::WIDTH };
	
	if (CAttack::collision(Pos, Size))
	{
		Player->DamageHit(1);
	}


	//動き
	CAttack::move();

	C3dpolygon::Update();

}

//------------------------------------
// 描画
//------------------------------------
void CAttack::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Ｚ軸で回転しますちなみにm_rotつかうとグルグル回ります
	//m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, m_rot);
	C3dpolygon::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//------------------------------------
// create
//------------------------------------
CAttack *CAttack::Create()
{
	CAttack * pObject = nullptr;
	pObject = new CAttack(PRIORITY_OBJECT);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}

//------------------------------------
// Get＆Set 
//------------------------------------
const D3DXVECTOR3 * CAttack::GetPos() const
{
	return &m_pos;
}

void CAttack::SetPos(const D3DXVECTOR3 & pos)
{
	m_pos = pos;
}

//------------------------------------
// 動き系統
//------------------------------------
void CAttack::move()
{
	//動き入れたいときはここに	SetMove()で変えれるよ
	m_pos += m_move;
}

//------------------------------------
// 当たり判定
//------------------------------------
bool CAttack::collision(D3DXVECTOR3 PlayerPos, D3DXVECTOR3 EnemySize)
{
	//当たり判定
	if (((m_pos.y - m_size.y) <= (PlayerPos.y + EnemySize.y)) &&
		((m_pos.y + m_size.y) >= (PlayerPos.y - EnemySize.y)) &&
		((m_pos.x - m_size.x) <= (PlayerPos.x + EnemySize.x)) &&
		((m_pos.x + m_size.x) >= (PlayerPos.x - EnemySize.x)) &&
		m_bCollision)
	{

		return true;
	}
	return false;
}


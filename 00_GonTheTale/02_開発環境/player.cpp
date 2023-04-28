//=============================================================================
//
// プレイヤー設定
// Author:hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include <stdio.h>
#include <assert.h>
#include "player.h"
#include "input.h"
#include "camera.h"
#include "manager.h"
#include "utility.h"
#include "game.h"
#include "effect.h"
#include "hamada.h"

#include "inputkeyboard.h"
#include "sound.h"
#include "score.h"
#include "select.h"
#include "bossbar.h"
#include "hpnumber.h"
#include "fade.h"
#include "manager.h"
#include "timer.h"
#include "event.h"
#include "damageeffect.h"

//=============================================================================
// static変数
//=============================================================================
const int CPlayer::MAXLIFE = 300;				// 最大体力
const float CPlayer::MOVE_ATTENUATION = 0.5f;	// 移動減衰係数
const float CPlayer::MOVE_ROTATTENUATION = 0.5f;	// 移動減衰係数
const float CPlayer::SPEED = 8.0f;		 		// 移動量
const float CPlayer::SPEEDMAX = 15.0f;		 		// 移動量
const float CPlayer::WIDTH = 15.0f;				// モデルの半径
const int CPlayer::MAX_PRAYER = 16;				// 最大数
const int CPlayer::MAX_MOVE = 9;				// アニメーションの最大数
const int CPlayer::INVINCIBLE = 120;				// 無敵時間
const int CPlayer::HP = 100;				// 無敵時間
int CPlayer::m_HPNow;
//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer(const int list) :C3dpolygon(list)
{
	m_wallmin = { -150.0f,-250.0f};
	m_wallmax = { 150.0f,50.0f};
	m_loolHit = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CPlayer::Init()
{
	// 現在のモーション番号の保管
	m_HPNow = HP;
	C3dpolygon::Init();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, -100.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	
	D3DXVECTOR3	Size(25.0f, 25.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetSize(Size);
	SetTexture(CTexture::TEXTURE_GONLIFE);//テクスチャ選択
	SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	SetUp(PLAYER);	
	m_NowType = DEFAULT_MOVE;
	m_jumpCount = 0;
	m_Select = CSelect::Create();
	m_Hp = CBossbar::Create(D3DXVECTOR3(230.0f, 580.0f, 0.0f),100);
	m_HpNumber = CHpNumber::Create(D3DXVECTOR3(580.0f, 580.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), 100);
	m_Event = nullptr;
	
	return S_OK;
}

//=============================================================================
// 終了
//=============================================================================
void CPlayer::Uninit()
{
	// 現在のモーション番号の保管
	C3dpolygon::Uninit();
}

//=============================================================================
// 更新
//=============================================================================
void CPlayer::Update()
{
	switch (m_NowType)
	{
	case CPlayer::DEFAULT_MOVE:
		SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		Move();
		break;
	case CPlayer::GRAVITY_MOVE:
		SetColar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
		GravityMove();
		break;
	case CPlayer::MAX:
		break;
	default:
		break;
	}
	// 現在のモーション番号の保管
	C3dpolygon::Update();
}

//=============================================================================
// 描画
//=============================================================================
void CPlayer::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	//アルファブレンディングを加算合成に設定
	//pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	//pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	//Ｚ軸で回転しますちなみにm_rotつかうとグルグル回ります
	//m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_mtxWorld = *hmd::giftmtx(&m_mtxWorld, m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	C3dpolygon::Draw();

	//αブレンディングを元に戻す
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// create
//=============================================================================
CPlayer *CPlayer::Create()
{
	CPlayer * pObject = nullptr;
	pObject = new CPlayer(PRIORITY_EFFECT);

	if (pObject != nullptr)
	{
		pObject->Init();
	}

	return pObject;
}
//=============================================================================
// Move
//=============================================================================
void CPlayer::Move()	//動きセット
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();


	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{
		m_move.y -= SPEED;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{
		m_move.y += SPEED;
	}

	m_move.x += (0.0f - m_move.x)*MOVE_ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*MOVE_ATTENUATION;
	m_move.y += (0.0f - m_move.y)*MOVE_ATTENUATION;

	m_pos += m_move;//移動を加算

	if (m_Select->GetReaction())	//避けるアクション時	
	{
		//お題　リターンの処理　stdを使用しプレイヤーの巻き戻りを再現
		if (CInputpInput->Press(CInput::KEY_SHIFT))
		{

			int size =  m_logPos.size();

			if (size <= 0)
			{
			
			}
			else
			{
				m_pos = m_logPos.back();	//戻る

				m_logPos.pop_back();//保存した値を削除
			}
		}
		else
		{
			if (m_pos != m_posOld && m_Select->GetLogOn())	//動いているとき
			{
				m_logPos.push_back(m_pos);//座標を動的に確保
			}
		}
	}
	if (m_Select->GetEnemyAttackFaze())
	{
		m_logPos.clear();	//stdの初期化
	}

	if (m_Select->GetReaction())
	{
		float Size = (WIDTH + 10.0f);
		//かりのかべつくってる
		if (m_pos.y <= m_wallmin.y + Size)
		{
			m_pos.y = m_wallmin.y + Size;
		}
		if (m_pos.y >= m_wallmax.y - Size)
		{
			m_pos.y = m_wallmax.y - Size;
		}
		if (m_pos.x >= m_wallmax.x - Size)
		{
			m_pos.x = m_wallmax.x - Size;
		}
		if (m_pos.x <= m_wallmin.x + Size)
		{
			m_pos.x = m_wallmin.x + Size;
		}
	}
}

//=============================================================================
// Move
//=============================================================================
void CPlayer::GravityMove()	//動きセット
{
	CInput *CInputpInput = CInput::GetKey();
	D3DXVECTOR3 *Camerarot = CRenderer::GetCamera()->GetRot();
	if (CInputpInput->Press(CInput::KEY_RIGHT))
	{
		m_move.x += sinf(D3DX_PI *0.5f + Camerarot->y) * SPEED;
		m_move.z += cosf(D3DX_PI *0.5f + Camerarot->y) * SPEED;
	}
	if (CInputpInput->Press(CInput::KEY_LEFT))
	{
		m_move.x += sinf(-D3DX_PI *0.5f + Camerarot->y) * SPEED;
		m_move.z += cosf(-D3DX_PI *0.5f + Camerarot->y) * SPEED;
	}
	if (CInputpInput->Press(CInput::KEY_DOWN))
	{
		m_move.y -= SPEED;
	}
	if (CInputpInput->Press(CInput::KEY_UP))
	{
		if (m_jumpCount <= 10&& !m_jump)
		{
			m_move.y += SPEED;
			m_jumpCount++;
		}
	}

	else
	{
		if (m_jumpCount != 0)
		{
			m_jump = true;
		}
	}

	if (m_move.y >= SPEEDMAX)
	{
		m_move.y = SPEEDMAX;
	}
	
	m_move.y -= 1.0f;

	m_move.x += (0.0f - m_move.x)*MOVE_ATTENUATION;//（目的の値-現在の値）＊減衰係数
	m_move.z += (0.0f - m_move.z)*MOVE_ATTENUATION;

	m_pos += m_move;//移動を加算
	if (m_Select->GetReaction())
	{
		//かりのかべつくってる
		if (m_pos.y <= m_wallmin.y + WIDTH)
		{
			m_move.y = 0.0f;
			m_pos.y = m_wallmin.y + WIDTH;
			m_jumpCount = 0;
			m_jump = false;
		}
		if (m_pos.y >= m_wallmax.y - WIDTH)
		{
			m_pos.y = m_wallmax.y - WIDTH;

		}
		if (m_pos.x >= m_wallmax.x - WIDTH)
		{
			m_pos.x = m_wallmax.x - WIDTH;
		}
		if (m_pos.x <= m_wallmin.x + WIDTH)
		{
			m_pos.x = m_wallmin.x + WIDTH;
		}
	}
}

//=============================================================================
// 当たった時判定
//=============================================================================
void CPlayer::DamageHit(int Damage)
{
	CRenderer::GetCamera()->ShakeCamera(10, 5.0f);
	m_HPNow -= Damage;
	m_Hp->SetDamage(Damage);
	m_HpNumber->AddNumber(-Damage);
	if (m_Hp->Getlife()<= 0)
	{
		m_HPNow = 0;
		CDamageEffect::Create(*GetPos());//座標設定;
		if (m_Event == nullptr)
		{
			m_Event = CEvent::Create({ 640.0f,380.0f,0.0f }, 0, 150, 50);
		}
		
		m_Select->GetTimer()->SetTimer(0);
		m_Hp->SetDamage(Damage);
		//CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
	}
}


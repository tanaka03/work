//=============================================================================
//
// BOSS
// Author:hamada ryuuga
//
//=============================================================================

#include "boss.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"
#include "line.h"
#include "reaction.h"
#include "manager.h"
#include "chaseenemy.h"
#include "manager.h"
#include "fade.h"
#include "bossbar.h"
#include "camera.h"
#include "stage.h"
#include "score.h"
#include "sound.h"
#include "jeteffect.h"
#include "moveeffect.h"
#include "motion.h"
#include "shadow.h"

CBossbar*CBoss::m_life;
int CBoss::m_Hp;
bool CBoss::m_DesEvent;
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CBoss::CBoss()
{
	m_nouevent = 0;
	m_frameCount = 0;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBoss::~CBoss()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CBoss::Init()
{
	// 現在のモーション番号の保管
	CEnemy::Init();
	SetUp(CObject::BOSS);
	m_hit = false;
	m_isMove = false;
	m_isMeteo = false;
	m_change = false;
	m_isAttack = false;
	m_isFly = false;
	m_isMeteoMove = false;
	m_isAction = false;
	m_isTop = false;
	m_DesEvent = false;
	m_MeteoMovesleep = 0;
	m_MeteoMove = 0;
	m_Hp = 100;
	m_Meteosleep = 0;
	m_Meteo = 0;
	m_life = CBossbar::Create(D3DXVECTOR3(700.0f, 150.0f, 0.0f), (float)m_Hp);
	m_move = {0.0f,0.0f,0.0f};
	m_Gurabitexi = { 0.0f,0.0f,0.0f };
	m_move.x = -5.0f;
	m_damage = 0;
	m_Attacksleep = 0;
	m_attack = 0;
	pointCollar = 3.0f;
	SetScale({ 0.7f,0.7f ,0.7f });

	m_shadow = CShadow::Create(GetPos());
	m_shadow->SetSize(D3DXVECTOR3(200.0f, 0.0f, 200.0f));
	m_shadow->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));

	m_object2d = CObject2d::Create(PRIORITY_UI);
	m_object2d->SetTexture(CTexture::TEXTURE_TUTORIAL002);
	m_object2d->SetSize(D3DXVECTOR3(200.0f, 200.0f, 200.0f));
	m_object2d->SetPos(D3DXVECTOR3(200.0f, 200.0f, 0.0f));
	m_object2d->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBoss::Uninit()
{
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBoss::Update()
{
	CEnemy::Update();

	pointCollar -= 0.02f;
	if (pointCollar >= 0.0f)
	{
		m_object2d->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, pointCollar));
	}
	
	

	D3DXVECTOR3 Pos = GetPos();

	if (Pos.y <= 0.0f)
	{
		m_isFly = false;
	}
	else
	{
		m_isFly = true;
		Pos.y -= 15.0f;
		SetPos(Pos);
	}

	Move();
	
	if (m_isMeteo)
	{
		Meteo();
	}
	if (m_isAttack)
	{
		Attack();
	}
	if (m_isMeteoMove)
	{
		MeteoMove();
	}	
	D3DXVECTOR3 pos = GetPos();
	if (CGame::GetStage()->GetHitMesh(GetPos()))
	{
		m_shadow->SetPos(D3DXVECTOR3(pos.x, 3.0f, pos.z));
		m_shadow->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.7f));
	}
	else
	{
		m_shadow->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBoss::Draw()
{
	CEnemy::Draw();
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBoss *CBoss::Create(D3DXVECTOR3 pos)
{
	CBoss *pEnemy = nullptr;

	pEnemy = new CBoss;

	if (pEnemy != nullptr)
	{
		pEnemy->Init();
		pEnemy->SetPopPos(pos);
		pEnemy->SetEnemyType(CStage::BOSS);
	}

	return pEnemy;
}

//--------------------------------------------------
// 動作
//--------------------------------------------------
void CBoss::Move()
{
	if (m_DesEvent)
	{
		D3DXVECTOR3 Pos = GetPos();

		m_isMeteoMove = false;
		m_isMeteo = false;
		m_isAttack = false;

		for (int i = 0; i < 3; i++)
		{
			float R = FloatRandom(1.0f, 0.0f);
			float G = FloatRandom(1.0f, 0.0f);
			float B = FloatRandom(1.0f, 0.0f);
			float MoveX = FloatRandom(10.0f, -10.0f);
			float MoveY = FloatRandom(15.0f, 10.0f);
			float MoveZ = FloatRandom(10.0f, -10.0f);

			CMoveEffect*JetEffect = CMoveEffect::Create({ MoveX ,MoveY ,MoveZ });
			JetEffect->SetSize(D3DXVECTOR3(200.0f*i, 200.0f*i, 0.0f));//サイズ設定
			JetEffect->SetColar(D3DXCOLOR(R, G, B, 1.0f));//色設定
			JetEffect->SetPos(Pos);
		}
		Pos.x += m_move.x;
		Pos.y -= 1.0f;
		SetPos(Pos);
		if (Pos.y <= -200.0f)
		{
			CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RESULT);
		}
		m_change = !m_change;
		if (m_change)
		{
			m_move.x = -1.0f;
			ChangeColar(D3DXCOLOR{ 1.0f,0.0f,0.0f,0.5f });
		}
		else
		{
			m_move.x = 1.0f;
			SetIsColor(false);
		}


	}
	else
	{
		if (GeteventListSize() != 0 && GetBossMoveTypetSize() != 0)
		{//eventリストがゼロじゃなかったら起こるa
			if (!m_isAction && !m_isFly)
			{
				m_frameCount++;
			}

			if (m_frameCount >= GeteventList(m_nouevent))
			{
				m_isAction = true;
				switch (GetBossMoveType(m_nouevent))
				{
				case CBoss::NONE:
					m_isMeteoMove = true;
					break;
				case CBoss::METEO:
					m_isMeteo = true;
					break;
				case CBoss::MOVE:
					m_isAttack = true;
					break;
				case CBoss::MAXBOSS:
					break;
				default:
					break;
				}
				m_nouevent++;
				if (m_nouevent >= GeteventListSize())
				{
					m_nouevent = 0;
				}
				m_frameCount = 0;
			}
		}
		if (!m_isAction)
		{//Actionしてるときは動いて欲しくない
			D3DXVECTOR3 Pos = GetPos();
			if (Pos.x >= 1200.0f)
			{
				Pos.x = 1199.0f;
				m_move.x *= -1.0f;
			}
			if (Pos.x <= -1200.0f)
			{
				Pos.x = -1199.0f;
				m_move.x *= -1.0f;
			}
			Pos += m_move;

			SetPos(Pos);
			CMotion *pMotion = CMotionModel3D::GetMotion();

			if (m_action != NONE)
			{
				if (pMotion != nullptr)
				{//アニメーション設定
					m_action = NONE;
					pMotion->SetNumMotion(m_action);
				}
			}
		}
		//Damage判定
		if (m_hit)
		{
			m_change = !m_change;
			if (m_change)
			{
				ChangeColar(D3DXCOLOR{ 1.0f,0.0f,0.0f,0.5f });
			}
			else
			{
				SetIsColor(false);
			}
			m_damage--;
			if (m_damage <= 0)
			{
				SetIsColor(false);
				m_damage = 0;
				m_hit = false;
			}
		}
	}
}

//--------------------------------------------------
// meteo動作
//--------------------------------------------------
void CBoss::Meteo()
{
	CMotion *pMotion = CMotionModel3D::GetMotion();
	m_Meteosleep++;

	if (m_Meteosleep >= METEOTIME)
	{
	
		CChaseEnemy::Create(GetPos())->SetBossPos(GetPos());
		m_Meteosleep = 0;
		m_Meteo++;
		if (m_Meteo >= METEOMAX)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_KEITAI);
			m_Meteo = 0;
			m_isMeteo = false;
			m_isAction = false;
		}
	}

	if (m_action == NONE)
	{
		if (pMotion != nullptr)
		{//アニメーション設定
			m_action = METEO;
			pMotion->SetNumMotion(m_action);
		}
	}
}

//--------------------------------------------------
// meteo動作
//--------------------------------------------------
void CBoss::Attack()
{
	D3DXVECTOR3 Pos = GetPos();

	if (m_Attacksleep <= ATTACKTIME)
	{

		m_posOld = GetPos();//過去の移動量を保存
		D3DXVECTOR3 rot = GetRot();

		//modelとプレイヤーの当たり判定
		CPlayer*Player = CGame::GetStage()->GetPlayer();

		D3DXVECTOR3 vecPlayerDist = Player->GetPos() - GetPos();
		float distPlayer = D3DXVec3Length(&vecPlayerDist);
		m_AttackMove = vecPlayerDist / distPlayer * 50.0f;
	
		rot.y = atan2f(-vecPlayerDist.x, -vecPlayerDist.z) - D3DX_PI;
		SetRot(rot);
	}
	else if (m_Attacksleep >= ATTACKBACK)
	{
		Pos.z = GetPopPos().z;
		Pos.y = 1500;
		SetPos(Pos);
		m_Attacksleep = 0;
		m_attack++;
	}
	else
	{
		CMoveEffect*MoveEffect = CMoveEffect::Create(m_move);
		MoveEffect->SetSize(D3DXVECTOR3(130.0f, 130.0f, 0.0f));//サイズ設定
		MoveEffect->SetPos({ Pos.x,Pos.y + 30.0f ,Pos.z });
		MoveEffect->SetColar(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));//色設定
		Pos.x += m_AttackMove.x;
		Pos.z += m_AttackMove.z;

		if (Pos.x >= 2000.0f)
		{
			Pos.z = -(float)ATTACKBACK;
		}
		if (Pos.x <= -2000.0f)
		{
			Pos.z = -(float)ATTACKBACK;
		}
		SetPos(Pos);
	}
	
	if (Pos.y <= 0.0f)
	{
		m_isFly = false;
		m_Attacksleep++;
	}
	
	if (Pos.z <= -(float)ATTACKBACK)
	{//画面外連れてく
		Pos.z = GetPopPos().z;
		Pos.y = 1500;
		SetPos(Pos);
		m_Attacksleep = 0;
		m_attack++;
	}
	
	if (m_attack >= (float)ATTACKMAX)
	{
		m_attack = 0;
		m_isAttack = false;
		m_isAction = false;
		SetRot({0.0f,D3DX_PI,0.0f});
	}
	if (m_Attacksleep == ATTACKTIME)
	{
	
		for (int i = 0; i < 3; i++)
		{
			CJetEffect*JetEffect = CJetEffect::Create(m_move);
			JetEffect->SetSize(D3DXVECTOR3(200.0f*i, 200.0f*i, 0.0f));//サイズ設定
			JetEffect->SetColar(D3DXCOLOR(1.0f, 0.3f, 0.3f, 1.0f));//色設定
			JetEffect->SetPos(Pos);
		}
	}
	CMotion *pMotion = CMotionModel3D::GetMotion();
	if (m_action == NONE)
	{
		if (pMotion != nullptr)
		{//アニメーション設定
			m_action = ATTACKMOVE;
			pMotion->SetNumMotion(m_action);
		}
	}
	
}

//--------------------------------------------------
// メテオMove
//--------------------------------------------------
void CBoss::MeteoMove()
{
	D3DXVECTOR3 Pos = GetPos();
	if (m_MeteoMovesleep == 0)
	{
		m_targetPos = CGame::GetStage()->GetPlayer()->GetPos();
		m_Gurabitexi.y = 75.0f;
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_ON);
	}
	if ((m_MeteoMovesleep == METEOMOVETIME))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_JAMP);
	}
	if (m_MeteoMovesleep <= METEOMOVETIME)
	{
		m_posOld = GetPos();//過去の移動量を保存
		D3DXVECTOR3 rot = GetRot();

		//modelとプレイヤーの当たり判定
		CPlayer*Player = CGame::GetStage()->GetPlayer();

		D3DXVECTOR3 vecPlayerDist = Player->GetPos() - GetPos();
		float distPlayer = D3DXVec3Length(&vecPlayerDist);
		m_m_MeteoMoveSpeed = vecPlayerDist / distPlayer * 30.0f;

		rot.y = atan2f(-vecPlayerDist.x, -vecPlayerDist.z) - D3DX_PI;
		SetRot(rot);

	}
	else
	{
		if (!m_isTop)
		{
			m_Gurabitexi.y-=1.0f;
			Pos.x += m_m_MeteoMoveSpeed.x;
			
			Pos.y += m_Gurabitexi.y;
			Pos.z += m_m_MeteoMoveSpeed.z;
			if (Pos.x >= 2000.0f)
			{
				Pos.z = (float)-METEOMOVEBACK;
			}
			if (Pos.x <= -2000.0f)
			{
				Pos.z = (float)-METEOMOVEBACK;
			}
		}
		else
		{
			m_Gurabitexi.y -= 1.0f;
			Pos.y += m_Gurabitexi.y;
		}
		
		SetPos(Pos);
	}

	if (Pos.y >= 1500.0f)
	{//高さ制限
		m_isTop = true;
	}
	
	if (Pos.y <= 0.0f)
	{//ゆか
		if (m_isTop)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_GURA);
			CRenderer::GetCamera()->ShakeCamera(60, 10.0f);
			if (CGame::GetStage()->GetPlayer()->GetMeshHit())
			{
				CGame::GetStage()->GetPlayer()->SetMoveRock(true);
			}
		}
		Pos.y = 0.0f;
		SetPos(Pos);
		m_isTop = false;
		m_isFly = false;
		m_MeteoMovesleep++;
	}


	if (Pos.z <= -METEOMOVEBACK)
	{//画面外連れてく
		m_isTop = false;
		Pos.z = GetPopPos().z;
		Pos.y = 1500;
		SetPos(Pos);
		m_MeteoMovesleep = 0;
		m_MeteoMove++;
	}

	if (m_MeteoMove >= METEOMOVEMAX)
	{
		m_isTop = false;
		m_isAction = false;
		m_MeteoMove = 0;
		m_isMeteoMove = false;
		SetRot({ 0.0f,D3DX_PI,0.0f });
	}

	if (m_MeteoMovesleep == METEOMOVEBACK)
	{
		for (int i = 0; i < 3; i++)
		{
			CJetEffect*JetEffect = CJetEffect::Create(m_move);
			JetEffect->SetSize(D3DXVECTOR3(100.0f*(i+1), 100.0f*(i + 1), 0.0f));//サイズ設定
			JetEffect->SetColar(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));//色設定
			JetEffect->SetPos(Pos);
		}

	}
	CMotion *pMotion = CMotionModel3D::GetMotion();
	if (m_action == NONE)
	{
		if (pMotion != nullptr)
		{//アニメーション設定
			m_action = MOVE;
			pMotion->SetNumMotion(m_action);
		}
	}

}
//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CBoss::Hit(CObject *object)
{
	switch (object->GetType())
	{
	case CObject::ENEMY:
		SearchModelObject(0, ENEMY, [this](CObject*Enemy)
		{
			CChaseEnemy* pEnemy = dynamic_cast<CChaseEnemy*>(Enemy);
			if (pEnemy != nullptr)
			{
				if (pEnemy->GetThrow())
				{
					CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BOM);
					CGame::GetStage()->GetScore()->Add(1000);
					CBoss::Add(-10);
					SetcheckHit(true);
					pEnemy->Uninit();
				}
			}
		});
		break;
	case CObject::PLAYER:
	{
		CPlayer*Player = CGame::GetStage()->GetPlayer();
		if (!Player->GetcheckHit())
		{//ダメージ
			CRenderer::GetCamera()->ShakeCamera(30, 10.0f);
			D3DXVECTOR3 Move = Player->GetMove();
			Player->SetcheckHit(true);
			CGame::GetStage()->GetScore()->Add(-500);
			Player->SetMove({ Move.x,20.0f,Move.z });
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DAMAGE);
		}
		break;
	}
	default:
		break;
	}

}
//--------------------------------------------------
// 当たってないときの判定
//--------------------------------------------------
void CBoss::NotHit()
{
}

//--------------------------------------------------
// Bossの動きのロード
//--------------------------------------------------
void CBoss::BossEventLood()
{

	std::ifstream ifs("data\\BOSS\\KUMA.json");

	int nIndex = 0;

	if (ifs)
	{
		ifs >> JBoss;
		nIndex = JBoss["INDEX"];
		int EventList = 0;
		int ModelType = 0;

		for (int nCntEnemy = 0; nCntEnemy < nIndex; nCntEnemy++)
		{
			std::string name = "BOSSEVENT";
			std::string Number = std::to_string(nCntEnemy);
			name += Number;

			EventList = JBoss[name]["EVENTLIST"];
			ModelType = JBoss[name]["BOSSMOVETYPE"];

			AddeventList(EventList);
			AddeBossMoveType((BOSSMOVETYPE)ModelType);
		}
	}
}  


//--------------------------------------------------
// Hp管理
//--------------------------------------------------
void CBoss::Add(int IsAdd)
{
	CRenderer::GetCamera()->ShakeCamera(30, 10.0f);

	m_Hp += IsAdd;
	m_life->SetDamage(-IsAdd);

	if (m_Hp <= 0)
	{
		DesEvent();
		//
	}
}

//--------------------------------------------------
// Hp管理
//--------------------------------------------------
void CBoss::DesEvent()
{
	CRenderer::GetCamera()->ShakeCamera(60, 30.0f);
	m_DesEvent = true;
	CRenderer::GetCamera()->SetEnd(true);
}

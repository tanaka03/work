//=============================================================================
//
// 加速アイテム
// Author:hamada ryuuga
//
//=============================================================================

#include "dashitem.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"
#include "sound.h"
#include "manager.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CDashitem::CDashitem()
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CDashitem::~CDashitem()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CDashitem::Init()
{
	CBuilding::Init();

	const char* Model = "data/MODEL/Dashitem.x";
	SetModel(Model);
	m_scale = 1.0f;
	m_hit = false;
	m_isScale = false;
	m_isMove = false;
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CDashitem::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CDashitem::Update()
{
	CObjectX::Update();

	// 動作
	Move();

	if (m_isScale)
	{
		m_scale -= 0.1f;
		SetScale({ m_scale ,m_scale,m_scale });
		if (m_scale <= 0.0f)
		{
			Uninit();
		}
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CDashitem::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CDashitem *CDashitem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CDashitem *pPendulum = nullptr;

	pPendulum = new CDashitem;

	if (pPendulum != nullptr)
	{
		pPendulum->SetPos(pos);
		pPendulum->SetRot(rot);
		pPendulum->SetFileName("dash");
		pPendulum->Init();
	}

	return pPendulum;
}

//--------------------------------------------------
// 動作
//--------------------------------------------------
void CDashitem::Move()
{

}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CDashitem::Hit()
{
	D3DXVECTOR3 centerPos = CGame::GetStage()->GetPlayer()->GetPos();

	D3DXVECTOR3 centerMove(0.0f, 0.0f, 150.0f);
	D3DXMATRIX mtx;	// 計算用マトリックス

	//
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_DASH);
	m_isScale = true;
	//CGame::GetStage()->GetPlayer()->SetGravity(false);
	D3DXMatrixRotationYawPitchRoll(&mtx, GetRot().y, GetRot().x, GetRot().z);
	D3DXVec3TransformCoord(&centerMove, &centerMove, &mtx);
	CGame::GetStage()->GetPlayer()->SetMoveDash(centerMove);
}
//--------------------------------------------------
// 当たってないときの判定
//--------------------------------------------------
void CDashitem::NotHit()
{
	m_hit = false;
}



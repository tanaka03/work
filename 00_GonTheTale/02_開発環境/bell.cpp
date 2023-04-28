//=============================================================================
//
// 得点アイテム
// Author:hamada ryuuga
//
//=============================================================================

#include "bell.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"
#include "score.h"
#include "shadow.h"
#include "manager.h"
#include "sound.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CBell::CBell()
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBell::~CBell()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CBell::Init()
{
	CBuilding::Init();

	const char* Model = "data\\MODEL\\Bell\\suzu.x";
	SetModel(Model);
	m_hit = false;
	m_isMove = false;
	Shadow = CShadow::Create(GetPos());
	D3DXVECTOR3 Pos = CGame::GetStage()->GetPlayerHitMesh(GetPos(), GetPos(), true, Shadow);
	Shadow->SetPos(Pos);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBell::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBell::Update()
{
	CObjectX::Update();

	// 動作
	Move();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBell::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBell *CBell::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CBell *pBell = nullptr;

	pBell = new CBell;

	if (pBell != nullptr)
	{
		pBell->SetPos(pos);
		pBell->SetRot(rot);
		pBell->SetFileName("bell");
		pBell->Init();
	}

	return pBell;
}

//--------------------------------------------------
// 動作
//--------------------------------------------------
void CBell::Move()
{

}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CBell::Hit()
{
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_COIN);
	CGame::GetStage()->GetScore()->Add(100);
	Shadow->Release();
	Uninit();
}
//--------------------------------------------------
// 当たってないときの判定
//--------------------------------------------------
void CBell::NotHit()
{
	m_hit = false;
}



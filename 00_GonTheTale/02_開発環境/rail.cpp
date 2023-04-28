//=============================================================================
//
// レール
// Author:hamada ryuuga
//
//=============================================================================

#include "rail.h"
#include "player.h"
#include "game.h"
#include "stage.h"
#include "utility.h"
#include "hamada.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CRail::CRail()
{

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CRail::~CRail()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CRail::Init()
{
	CBuilding::Init();

	const char* Model = "data/MODEL/reil.x";
	SetModel(Model);
	m_hit = false;
	m_isMove = false;
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CRail::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CRail::Update()
{
	CObjectX::Update();

	// 動作
	Move();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CRail::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CRail *CRail::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CRail *pPendulum = nullptr;

	pPendulum = new CRail;

	if (pPendulum != nullptr)
	{
		pPendulum->SetPos(pos);
		pPendulum->SetRot(rot);
		pPendulum->SetFileName("Rail");
		pPendulum->Init();
	}

	return pPendulum;
}

//--------------------------------------------------
// 動作
//--------------------------------------------------
void CRail::Move()
{
	
}

//--------------------------------------------------
// 当たり判定
//--------------------------------------------------
void CRail::Hit()
{

	D3DXMATRIX mtx;
	
	D3DXVECTOR3 centerPos = CGame::GetStage()->GetPlayer()->GetPos();

	D3DXVECTOR3 min = CObjectX::GetVtxMin();
	D3DXVECTOR3 max = CObjectX::GetVtxMax();


	mtx = *hmd::giftmtx(&mtx, GetPos(), GetRot());

	D3DXVECTOR3 PopPos(D3DXVECTOR3(mtx._41, mtx._42, mtx._43));

	D3DXVECTOR3 maxMove = (max+ PopPos) - centerPos;
	D3DXVECTOR3 minMove = (min+ PopPos) - centerPos;

	float MaxLength = D3DXVec3Length(&maxMove);
	float MinLength = D3DXVec3Length(&minMove);

	if (!m_hit)
	{//どっち方向に進むか初回確認
		if (MaxLength < MinLength)
		{
			m_hit = true;
			m_isMove = false;
		}
		else
		{
			m_hit = true;
			m_isMove = true;
		}
	}
	else
	{//確認できたらその方向にホーミングする
		D3DXVECTOR3 centerPosOld = CGame::GetStage()->GetPlayer()->GetPosOld();

		if (m_isMove)
		{
			Homing(&centerPos, centerPos, D3DXVECTOR3(PopPos.x, max.y / 2, PopPos.z + max.z*1.5f), 10);

			CGame::GetStage()->GetPlayer()->SetPos(centerPos);
		}
		else
		{
			Homing(&centerPos, centerPos, D3DXVECTOR3(PopPos.x, max.y / 2, PopPos.z + min.z*1.5f), 10);

			CGame::GetStage()->GetPlayer()->SetPos(centerPos);
		}
	}
}
//--------------------------------------------------
// 当たってないときの判定
//--------------------------------------------------
void CRail::NotHit()
{
	m_hit = false;
}
	


//==================================================
// wood_spawn.cpp
// Author: tutida ryousei
//==================================================
#include"wood_spawn.h"
#include"wood.h"
#include"manager.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CWood_Spawn::CWood_Spawn()
{
	m_Pos = { 0.0f,0.0f,0.0f };
	m_nCoolTime = 0;
	m_nCount = 0;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CWood_Spawn::~CWood_Spawn()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CWood_Spawn::Init()
{
	CBuilding::Init();
	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CWood_Spawn::Uninit()
{
	//CObjectX::Uninit();
	Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CWood_Spawn::Update()
{
	m_nCount++;

	if (m_nCount % m_nCoolTime == 0)
	{	
		// オブジェクトの生成
		CWood::Create(m_Pos, m_fRot, m_fMoveSpeed, m_fRotSpeed);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CWood_Spawn::Draw()
{
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CWood_Spawn *CWood_Spawn::Create(D3DXVECTOR3 pos, float rot, float movespeed, float rotspeed, int cooltime)
{
	CWood_Spawn *pSpawn = nullptr;

	pSpawn = new CWood_Spawn;

	if (pSpawn != nullptr)
	{
		pSpawn->Init();
		pSpawn->SetPos(pos);
		pSpawn->SetRot(rot);
		pSpawn->SetMoveSpeed(movespeed);
		pSpawn->SetRotSpeed(rotspeed);
		pSpawn->SetCoolTime(cooltime);
		pSpawn->SetFileName("Wood");
	}

	return pSpawn;
}
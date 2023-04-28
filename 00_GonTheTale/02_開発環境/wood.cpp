//==================================================
// wood.cpp
// Author: tutida ryousei
//==================================================
#include"wood.h"

#include "manager.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CWood::CWood()
{
	m_Pos = { 0.0f,0.0f,0.0f };
	m_Rot = { 0.0f,0.0f,0.0f };
	m_life = 100;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CWood::~CWood()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CWood::Init()
{


	// モデルの設定
	const char* Model = "data/MODEL/wood.x";
	SetModel(Model);

	// 生成時の角度
	m_Rot.y += m_fSpawnRot;

	return S_OK;
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CWood::Update()
{
	if (m_Pos.y > 0.0f)
	{
		m_Pos.y -= 3.0f;
	}
	else
	{
		// 移動
		m_Pos.x -= sinf(m_fSpawnRot) * m_fMoveSpeed;
		m_Pos.z -= cosf(m_fSpawnRot) * m_fMoveSpeed;

		// 回転
		m_Rot.x -= m_fRotSpeed;
	}
	m_life--;
	if (m_life < 0)
	{
		CObjectX::Uninit();
	}

	CObjectX::SetPos(m_Pos);
	CObjectX::SetRot(m_Rot);
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CWood *CWood::Create(D3DXVECTOR3 pos, float spawnrot, float movespeed, float rotspeed)
{
	CWood *pWood = nullptr;

	pWood = new CWood;

	if (pWood != nullptr)
	{
		pWood->SetPos(pos);
		pWood->SetSpawnRot(spawnrot);
		pWood->SetMoveSpeed(movespeed);
		pWood->SetRotSpeed(rotspeed);
		pWood->Init();
	}

	return pWood;
}
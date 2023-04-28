//==================================================
// ball.cpp
// Author: tutida ryousei
//==================================================
#include"pendulum.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CPendulum::CPendulum()
{
	m_Rot = { 0.0f,0.0f,0.0f };
	m_DestRot = { 0.0f,0.0f,0.0f };
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPendulum::~CPendulum()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CPendulum::Init()
{
	CBuilding::Init();

	// モデルの設定
	if (m_nType == 0)
	{
		const char* Model = "data/MODEL/pendulum.x";
		SetModel(Model);
	}
	else
	{
		const char* Model = "data/MODEL/pendulum2.x";
		SetModel(Model);
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CPendulum::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CPendulum::Update()
{
	CObjectX::Update();

	// 動作
	Move();

	// 角度の設定
	SetRot(m_Rot);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CPendulum::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CPendulum *CPendulum::Create(D3DXVECTOR3 pos, D3DXVECTOR3 destrot, float coefficient, int type)
{
	CPendulum *pPendulum = nullptr;

	pPendulum = new CPendulum;

	if (pPendulum != nullptr)
	{
		pPendulum->SetPos(pos);
		pPendulum->SetDestRot(destrot);
		pPendulum->SetCoefficient(coefficient);
		pPendulum->SetType(type);
		pPendulum->SetFileName("Pendulum");
		pPendulum->Init();
	}

	return pPendulum;
}

//--------------------------------------------------
// 動作
//--------------------------------------------------
void CPendulum::Move()
{
	// X座標
	if (m_Rot.x < m_DestRot.x) {
		if (m_Rot.x < 0)
		{
			// 加速
			m_Rot.x += (m_DestRot.x + m_Rot.x) * m_fCoefficient;
		}
		else
		{
			// 減速
			m_Rot.x += (m_DestRot.x - m_Rot.x) * m_fCoefficient;
		}

		if (m_Rot.x >= m_DestRot.x * 0.95f)
		{
			// 目的の角度の反転
			m_DestRot.x *= -1.0f;
		}
	}
	else {
		if (m_Rot.x > 0)
		{
			// 加速
			m_Rot.x += (m_DestRot.x + m_Rot.x) * m_fCoefficient;
		}
		else
		{
			// 減速
			m_Rot.x += (m_DestRot.x - m_Rot.x) * m_fCoefficient;
		}

		if (m_Rot.x <= m_DestRot.x * 0.95f)
		{
			// 目的の角度の反転
			m_DestRot.x *= -1.0f;
		}
	}

	// Z座標
	if (m_Rot.z < m_DestRot.z) {
		if (m_Rot.z < 0)
		{
			// 加速
			m_Rot.z += (m_DestRot.z + m_Rot.z) * m_fCoefficient;
		}
		else
		{
			// 減速
			m_Rot.z += (m_DestRot.z - m_Rot.z) * m_fCoefficient;
		}

		if (m_Rot.z >= m_DestRot.z * 0.95f)
		{
			// 目的の角度の反転
			m_DestRot.z *= -1.0f;
		}
	}
	else {
		if (m_Rot.z > 0)
		{
			// 加速
			m_Rot.z += (m_DestRot.z + m_Rot.z) * m_fCoefficient;
		}
		else
		{
			// 減速
			m_Rot.z += (m_DestRot.z - m_Rot.z) * m_fCoefficient;
		}

		if (m_Rot.z <= m_DestRot.z * 0.95f)
		{
			// 目的の角度の反転
			m_DestRot.z *= -1.0f;
		}
	}
	 
	// Y座標
	m_Rot.y += m_DestRot.y;
}
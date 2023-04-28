//==================================================
// ball.cpp
// Author:hamada
//==================================================
#include"ball.h"
#include "input.h"

//**************************************************
// マクロ定義
//**************************************************
#define SPEED	(15.0f)
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CBall::CBall()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CBall::~CBall()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CBall::Init()
{
	CBuilding::Init();

	// モデルの設定
	const char* Model = "data/MODEL/ball.x";
	SetModel(Model);

	// 位置の設定
	if (m_nRotType == 0)
	{
		m_Pos = { m_centerPos.x - m_fRadius ,m_centerPos.y,m_centerPos.z };
	}
	else
	{
		m_Pos = { m_centerPos.x + m_fRadius ,m_centerPos.y,m_centerPos.z };
	}

	return	S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CBall::Uninit()
{
	CObjectX::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CBall::Update()
{


	CObjectX::Update();

	// 移動
	Move();

	//SetPos(m_Pos);
	//SetRot(m_Rot);
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CBall::Draw()
{
	CObjectX::Draw();
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CBall *CBall::Create(D3DXVECTOR3 centerpos, float radius, float rotspeed, int rotType)
{
	CBall *pBall = nullptr;

	pBall = new CBall;

	if (pBall != nullptr)
	{
		pBall->SetCenterPos(centerpos);
		pBall->SetRadius(radius);
		pBall->SetRotSpeed(rotspeed);
		pBall->SetRotType(rotType);
		pBall->SetFileName("Ball");
		pBall->SetQuat(true);
		pBall->Init();
		pBall->SetPos(centerpos);
	}

	return pBall;
}

//--------------------------------------------------
// 移動
//--------------------------------------------------
void CBall::Move()
{
	// インプット
	CInput *CInputpInput = CInput::GetKey();

	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 rot = GetRot();

	if ((vec.x == 0.0f) && (vec.z == 0.0f))
	{
		if (CInputpInput->Press(CInput::KEY_RIGHT))
		{
			vec.x += 1.0f;
		}
		if (CInputpInput->Press(CInput::KEY_LEFT))
		{
			vec.x += -1.0f;
		}
		if (CInputpInput->Press(CInput::KEY_UP))
		{

			vec.z += 1.0f;
		}
		if (CInputpInput->Press(CInput::KEY_DOWN))
		{
			vec.z += -1.0f;
		}
	}

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 maxVtx = GetVtxMax();
	D3DXVECTOR3 rotate;

	if (vec.x != 0.0f || vec.z != 0.0f)
	{// 移動とそれに合わせた回転
	 // ベクトルの正規化
		D3DXVec3Normalize(&vec, &vec);
		// キーボード
		pos += vec * SPEED;

		// 移動量に対しての回転涼を求める（z軸）
		rotate.z = vec.x * SPEED / maxVtx.x;
		rot.z += -rotate.z;

		// 移動量に対しての回転涼を求める（x軸）
		rotate.x = vec.z * SPEED / maxVtx.z;
		rot.x += rotate.x;

		rot = RotNormalization(rot);

		SetPos(pos);
		SetRot(rot);
		
		/*float fLength = D3DXVec3Length(&rotate);*/

		//X = Z, Z= -X
		D3DXVECTOR3 axis;    // 回転軸
		D3DXVECTOR3 inverseVec = -(vec);        // move値を反対にする
		D3DXVECTOR3 vecY = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&axis, &inverseVec, &vecY);    // 外積で回転軸を算出。

													 // クオータニオンの計算
		D3DXQUATERNION quaternion;
		D3DXQuaternionRotationAxis(&quaternion, &axis, 0.05f);    // 回転軸と回転角度を指定

		// クオータニオンを適用
		m_quat *= quaternion;


		D3DXQuaternionNormalize(&m_quat, &m_quat);
	}
}

//--------------------------------------------------
// クオータニオン
//--------------------------------------------------
void CBall::quat()
{
	D3DXMATRIX mtx = GetWorldMtx();
	D3DXMATRIX mtxRot;

	// クォータニオンの使用した姿勢の設定
	D3DXMatrixRotationQuaternion(&m_mtxRot, &m_quat);            // クオータニオンによる行列回転
	D3DXMatrixMultiply(&mtx, &mtx, &m_mtxRot);    // 行列掛け算関数(第2引数×第3引数第を１引数に格納)

	SetWorldMtx(mtx);

}
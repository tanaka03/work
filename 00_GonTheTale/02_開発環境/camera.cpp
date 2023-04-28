//=============================================================================
//
// カメラ設定
// Author:hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "camera.h"
#include "input.h"

#include "manager.h"
#include "player.h"

#include "title.h"
#include "game.h"
#include "utility.h"
#include "object.h"

//-----------------------------------------------------------------------------
// 定数
//-----------------------------------------------------------------------------
const D3DXVECTOR3 CCamera::INIT_POSV(0.0f, 0.0f, -750.0f);	// 位置の初期位置
const float CCamera::MOVE_ATTENUATION = 0.1f;	// 減衰係数
const float CCamera::MOVE_ANGLE = 10.0f;	// 減衰係数
const float CCamera::FIELD_OF_VIEW = 45.0f;	// 視野角
const float CCamera::NEAR_VALUE = 10.0f;	// ニア
const float CCamera::FUR_VALUE = 100000.0f;	// ファー

//-----------------------------------------------------------------------------
// コンストラクト
//-----------------------------------------------------------------------------
CCamera::CCamera()
{
	
}

//-----------------------------------------------------------------------------
// デストラクト
//-----------------------------------------------------------------------------
CCamera::~CCamera()
{
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
void CCamera::Init(void)
{
	m_isFree = false;
	m_isAnimation = false;
	m_isLoop = false;
	m_bossEnd = false;
	m_nouAnimation = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//視点　注視点　上方向　設定
	m_posV = D3DXVECTOR3(0.0f, 0.0f, -150.0f);
	m_posR = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_directionR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_directionV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_isFrameCount = 0;
	m_isShakePow = 0.0f;

}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void CCamera::Uninit(void)
{
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CCamera::Update(void)
{
	
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CCamera::Set(int Type)
{
	m_type = Type;
	LPDIRECT3DDEVICE9  pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();//デバイスのポインタ

	//ビューマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxView);
	D3DXVECTOR3 RandomMove = {0.0f,0.0f,0.0f};

	if (m_isFrameCount >= 0)
	{
		m_isFrameCount--;
		RandomMove.x = FloatRandom(m_isShakePow, -m_isShakePow);
		RandomMove.y = FloatRandom(m_isShakePow, -m_isShakePow);
		RandomMove.z = FloatRandom(m_isShakePow, -m_isShakePow);
	}

	//ビューマトリックスの作成
	D3DXMatrixLookAtLH(&m_mtxView,
		&(m_posV+RandomMove),
		&(m_posR+RandomMove),
		&m_vecU);

	//適用
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);

	//プロジェクションマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxProje);

	// プロジェクションマトリックスの作成(平行投影)
	D3DXMatrixOrthoLH(&m_mtxProje,					// プロジェクションマトリックス
		(float)SCREEN_WIDTH,								// 幅
		(float)SCREEN_HEIGHT,								// 高さ
		0.0f,											// ニア
		2000.0f);	

//else
//{
//	// プロジェクションマトリックスの作成(平行投影)
//	D3DXMatrixOrthoLH(&m_MtxProje,					// プロジェクションマトリックス
//		(float)SCREEN_WIDTH,								// 幅
//		(float)SCREEN_HEIGHT,								// 高さ
//		-100.0f,											// ニア
//		2000.0f);											// ファー
//}
//適用
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProje);
}

//-----------------------------------------------------------------------------
//	Animationの再生処理
//-----------------------------------------------------------------------------
void CCamera::PlayAnimation(int Animation, bool Isloop)
{	
	m_nouAnimation = Animation;
	m_isAnimation = true;
	m_isLoop = Isloop;
	
}



//-----------------------------------------------------------------------------
//カメラゆらゆらする設定
//-----------------------------------------------------------------------------
void CCamera::ShakeCamera(int IsFrameCount, float IsShakePow)
{
	m_isFrameCount = IsFrameCount;
	m_isShakePow = IsShakePow;
}

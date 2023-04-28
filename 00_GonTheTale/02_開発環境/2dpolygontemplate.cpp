//============================
//
// ２Dpolygon設定
// Author:hamada ryuuga
//
//============================

#include "2dpolygontemplate.h"
#include "utility.h"
//------------------------------------
// コンストラクタ
//------------------------------------
CTest::CTest() :CObject2d(PRIORITY_BG)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CTest::~CTest()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CTest::Init()
{
	CObject2d::Init();

	m_testrot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CTest::Uninit()
{
	CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CTest::Update()
{
	CObject2d::Update();
	//動き
	CTest::move();
}

//------------------------------------
// 描画
//------------------------------------
void CTest::Draw()
{
	CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CTest *CTest::Create(D3DXVECTOR3 pos, bool b3D)
{
	CTest * pObject = new CTest;

	if (pObject != nullptr)
	{
		D3DXVECTOR3 Poppos = pos;
		if (b3D)
		{
			Poppos = ScreenCastWorld(&Poppos,			// スクリーン座標
				D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f));								// スクリーンサイズ
		}
		pObject->Init();
		pObject->SetPos(Poppos);
		pObject->SetTexture(CTexture::TEXTURE_NONE);//テクスチャ選択
		pObject->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));//moveの設定
		pObject->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));//サイズ設定

		//↓引数(1横の枚数,2縦の枚数,3Animation速度,４基本ゼロだけど表示するまでのタイムラグ,5無限にアニメーション再生するかどうか)
		pObject->SetAnimation(7,1,0,0,false);//Animation画像だった場合これを書く,一枚絵なら消さないとバグる

		pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));//色設定
	
	}
	return pObject;
}


//------------------------------------
// 動き系統
//------------------------------------
void CTest::move()
{
	m_testrot.z+=0.1f;
	//動き入れたいときはここに	SetMove()で変えれるよ
	SetRot(m_testrot);
	m_pos += m_move;
}
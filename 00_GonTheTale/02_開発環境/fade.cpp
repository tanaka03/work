//============================
//
// フェード設定
// Author:hamada ryuuga
//
//============================

#include <stdio.h>
#include <assert.h>
#include "fade.h"


//------------------------------------
// コンストラクタ
//------------------------------------
CFade::CFade() :CObject2d(PRIORITY_FADE)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CFade::~CFade()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CFade::Init(void)
{
	// 現在のモーション番号の保管
	CObject2d::Init();
	m_FadeSp = 0.07f;
	m_FadeSet = 0.0f;

	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CFade::Uninit(void)
{
	// 現在のモーション番号の保管
	 CObject2d::Uninit();
}

//------------------------------------
// 更新
//------------------------------------
void CFade::Update(void)
{
	if (fade != FADENON)
	{
		// 現在のモーション番号の保管
		CObject2d::Update();
		if (fade == FADEOUT)
		{
			m_FadeSet -= m_FadeSp;
		}
		if (fade == FADEIN)
		{
			m_FadeSet += m_FadeSp;
		}

		if (m_FadeSet >= 1.0f)
		{
			fade = FADEOUT;
			m_FadeSet = 1.0f;
			CManager::GetInstance()->SetMode(m_NextMode);

		}
		if (m_FadeSet <= 0.0f)
		{
			fade = FADENON;

			m_FadeSet = 0.0f;

			return;
		}
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_FadeSet));
	}
	
}

//------------------------------------
// 描画
//------------------------------------
void CFade::Draw(void)
{
	 CObject2d::Draw();
}

//------------------------------------
// create
//------------------------------------
CFade* CFade::Create()
{
	CFade * pObject = nullptr;
	pObject = new CFade;

	if (pObject != nullptr)
	{
		pObject->Init();
		pObject->m_NextMode = CManager::MODE_TITLE;
		pObject->SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
		pObject->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		pObject->SetUp(CObject::MODE);
		pObject->fade = FADENON;
	}
	return pObject;
}


//------------------------------------
// 次のモードにいくね
//------------------------------------
void CFade::NextMode(CManager::MODE nextMode)
{
	if (fade == FADENON)
	{
		Init();
		m_NextMode = nextMode;
		SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
		SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		fade = FADEIN;
	}
}

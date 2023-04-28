//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "pause.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
 
#include "manager.h"

//========================
// コンストラクター
//========================
CPause::CPause()
{
}
//========================
// デストラクト
//========================
CPause::~CPause()
{
}

//================
//初期化処理
//================
HRESULT CPause::Init(void)
{
	// オブジェクトの生成
	// @param priority			オブジェクトのプライオリティ
	// @param tex				オブジェクトのテクスチャ
	// @param pos				オブジェクトの位置
	// @param size				オブジェクトの拡縮
	// @param col				オブジェクトの色
	// @return					生成したオブジェクトのポインタ
	auto createObject = [](CObject::PRIORITY priority, CTexture::TEXTURE tex,
		D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXCOLOR col)
	{
		CObject2d* obj = CObject2d::Create(priority);
		obj->SetTexture(tex);
		obj->SetPos(pos);
		obj->SetSize(size);
		obj->SetColar(col);
		return obj;
	};

	m_NextMode = MODE_GAME;
	m_OnPause = false;

	// モード選択時の背景黒くするやつ
	m_Bg = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSEBG,
		CManager::centerPos,
		D3DXVECTOR3(450.0f, CManager::centerPos.y, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	// ゲームの文字
	m_object2d[0] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSEGAME,
		CManager::centerPos,
		D3DXVECTOR3(150.0f, 50.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	float y = 100.0f;

	// チュートリアルの文字
	m_object2d[1] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSERETURN,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y + y, 0.0f),
		D3DXVECTOR3(150.0f, 50.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	y += 100.0f;

	// ランキングの文字
	m_object2d[2] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSETITLE,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y + y, 0.0f),
		D3DXVECTOR3(150.0f, 50.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	// ランキングの文字
	m_object2d[3] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_PAUSEMENU,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y - y, 0.0f),
		D3DXVECTOR3(300.0f, 100.0f, 0.0f),
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	return S_OK;
}

//================
//破棄
//================
void CPause::Uninit(void)
{
	CObject::Release();
}

//==================
//更新処理
//==================
void CPause::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_PAUSE)&& *CManager::GetInstance()->GetFade()->GetFade() == CFade::FADENON)
	{
		if (m_OnPause)
		{
			Set();
			m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
			for (int i = 0; i < 4; i++)
			{
				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
		else
		{
			m_NextMode = 0;
			Set();
			//背景
			m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));
			for (int i = 0; i < 4; i++)
			{//全部一回変える
				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			//選択してるやつ
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		if (m_OnPause)
		{
			switch (m_NextMode)
			{
			case MODE::MODE_GAME:
				//モードの設定
				CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_RETURN:
				//モードの設定
				m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.0f));
				for (int i = 0; i < 4; i++)
				{
					m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
				}
				break;
			case MODE::MODE_TITLE:
				//モードの設定
				CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
				break;
			default:
				break;
			}
			m_OnPause = false;
		}
		if (m_OnPause)
		{
			m_Bg->SetColar(D3DXCOLOR(0.3f, 0.3f, 0.30f, 0.5f));
			for (int i = 0; i < 3; i++)
			{
				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
			}
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		else
		{
			m_Bg->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			for (int i = 0; i < 3; i++)
			{

				m_object2d[i]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			}
		}
	}
	if (m_OnPause)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			//モード選択
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			m_NextMode = (MODE)(m_NextMode - 1);

			if (m_NextMode < MODE::MODE_GAME)
			{
				m_NextMode = MODE::MODE_TITLE;
			}
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			//モード選択
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));

			m_NextMode = (MODE)(m_NextMode + 1);

			if (m_NextMode >= MODE::MODE_END)
			{
				m_NextMode = MODE::MODE_GAME;
			}
			m_object2d[m_NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

#ifdef _DEBUG
#endif // DEBUG
}

//==================
//描画処理
//==================
void CPause::Draw(void)
{
}
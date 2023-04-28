//**************************************************
//
// 制作 ( タイトル )
// Author : hamada ryuuga
//
//**************************************************
#include "title.h"
#include "input.h"
#include "manager.h"
 
#include "fade.h"
#include "sound.h"
 
#include "3dpolygon.h"

#include "player.h"

#include "camera.h"

#include "utility.h"
#include "ranking.h"

//-----------------------------------------------------------------------------
// コンストラクター
//-----------------------------------------------------------------------------
CTitle::CTitle()
{
}

//-----------------------------------------------------------------------------
// デストラクト
//-----------------------------------------------------------------------------
CTitle::~CTitle()
{
}

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT CTitle::Init(void)
{
	// 半分にするだけの処理
	// @param size				オブジェクトのサイズ
	// @return					サイズ * 0.5f
	auto half = [](D3DXVECTOR3 size)
	{
		return size * 0.5f;
	};

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

	D3DXVECTOR3 BGPos;
	BGPos.x = 0.0f;
	BGPos.y = 0.0f;
	BGPos.z -= 30.0f;
	D3DXVECTOR3 EnemyPos = CManager::centerPos;
	m_alpha = 1.2f;

	m_addX = 0;
	m_addY = 0;
	ModeSelect = false;
	NextMode = MODE::MODE_GAME;

	EnemyPos.z -= 30.0f;

	D3DXVECTOR3 Size(3.8f, 3.8f, 3.8f);
	D3DXVECTOR3 Rot(0.0f, 1.57f, 0.0f);

	////GonFoxのTITLE文字
	m_list[0] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_LOOKON,
		D3DXVECTOR3(CManager::centerPos.x, 250.0f, 0.0f),
		D3DXVECTOR3(250.0f, 250.0f, 0.0f),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//ゲームスタートの文字
	m_list[1] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_FOXTITLE,
		D3DXVECTOR3(CManager::centerPos.x, 600.0f, 0.0f),
		half(CManager::centerPos),
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//GonFoxのTITLE文字
	m_list[2] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_TITLE,
		D3DXVECTOR3(CManager::centerPos.x, 250.0f, 0.0f),
		CManager::centerPos * 0.8f,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	/*m_3dpolygon[0] = C3dpolygon::Create(PRIORITY_PLAYER);
	m_3dpolygon[0]->SetTexture(CTexture::TEXTURE_TITLE);
	m_3dpolygon[0]->SetSize(D3DXVECTOR3(10.0f,0.0f,10.0f));
	m_3dpolygon[0]->SetPos(D3DXVECTOR3(0.0f,0.0f,0.0f));
	m_3dpolygon[0]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	m_3dpolygon[0]->SetRot(D3DXVECTOR3(0.0f, 0.0f, 1.50f));*/

	//モード選択時の背景黒くするやつ
	fade = createObject(PRIORITY_UI,
		CTexture::TEXTURE_NONE,
		CManager::centerPos,
		CManager::centerPos,
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	
	float y = 120.0f;
	
	//ゲームの文字
	m_object2d[0] = createObject(PRIORITY_FADE,
		CTexture::TEXTURE_TITLEGAME,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y - y, 0.0f),
		CManager::centerPos,
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	
	//チュートリアルの文字
	m_object2d[1] = createObject(PRIORITY_FADE,
		CTexture::TEXTURE_TITLETUTORIAL,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y, 0.0f),
		CManager::centerPos,
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	
	//ランキングの文字
	m_object2d[2] = createObject(PRIORITY_FADE,
		CTexture::TEXTURE_TITLERANKIN,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y + y, 0.0f),
		CManager::centerPos,
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	
	y += 120.0f;
	
	//おわりの文字
	m_object2d[3] = createObject(PRIORITY_FADE,
		CTexture::TEXTURE_TITLEEND,
		D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y + y, 0.0f),
		CManager::centerPos,
		D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	m_ParticleCount = 0;

	CRanking::SetScore(0);

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TITLE);
	m_Rot = 0.0f;
	
	return S_OK;
}

//-----------------------------------------------------------------------------
// 破棄
//-----------------------------------------------------------------------------
void CTitle::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();

	CObject::Release();
	//CObjectXManager::ReleaseAll();
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void CTitle::Update(void)
{
	D3DXCOLOR darkColor(0.6f, 0.6f, 0.6f, 0.8f);

	if (!ModeSelect)
	{//一回押された	
		if (m_addY <= 10)
		{
			Sizcontroller = true;
		}

		if (m_addY >= 50)
		{
			Sizcontroller = false;
		}

		float a;
		if (Sizcontroller)
		{
			m_addY++;
			m_addX--;
			a = sinf((float)m_alpha);
			m_alpha -= 1.0f / 60;
		}
		else
		{
			m_addY--;
			m_addX++;
			a = sinf((float)m_alpha);
			m_alpha += 1.0f / 60;
		}

		//きつねをもちもちさせるやつ
		D3DXVECTOR3 addPos = D3DXVECTOR3(1.0f + (float)m_addX, 1.0f + (float)m_addY, 0.0f);
		//m_Bg[1]->SetSize(CManager::centerPos *0.8f + addPos);

		//点滅させる
		m_list[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, a));
	}

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		CManager* maneger = CManager::GetInstance();
		maneger->GetSound()->Play(CSound::LABEL_SE_ON);
		if (ModeSelect)
		{//一回押された	
			switch (NextMode)
			{
			case MODE::MODE_GAME:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_GAME);
				break;
			case MODE::MODE_TUTORIAL:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_TUTORIAL);
				break;
			case MODE::MODE_RANKING:
				//モードの設定
				maneger->GetFade()->NextMode(CManager::MODE_RANKING);
				break;
			case MODE::MODE_END:
				//ゲームの終了
				PostQuitMessage(0);
				break;
			default:
				break;
			}
		}
		else
		{
			//画面黒くする
			fade->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f));

			//文字を出し
			for (int i = 0; i < 4; i++)
			{
				m_object2d[i]->SetColar(darkColor);
			}

			//今使ってるやつを明るく
			m_object2d[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			ModeSelect = true;
		}
	}

	if (ModeSelect)
	{
		if (CInputpInput->Trigger(CInput::KEY_UP))
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);
			//モード選択
			m_object2d[NextMode]->SetColar(darkColor);

			NextMode = (MODE)(NextMode - 1);

			if (NextMode < MODE::MODE_GAME)
			{
				NextMode = MODE::MODE_END;
			}

			m_object2d[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		if (CInputpInput->Trigger(CInput::KEY_DOWN))
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);
			//モード選択
			m_object2d[NextMode]->SetColar(darkColor);

			NextMode = (MODE)(NextMode + 1);

			if (NextMode >= MODE::MODE_MAX)
			{
				NextMode = MODE::MODE_GAME;
			}

			m_object2d[NextMode]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定

		//
	}
	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_GAME);
	}

#endif // DEBUG
	m_Rot += 0.05f;

	NormalizeAngle(&m_Rot);
	
	m_list[0]->SetRot(D3DXVECTOR3(0.0f, 0.0f, m_Rot));

}
//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void CTitle::Draw(void)
{

}
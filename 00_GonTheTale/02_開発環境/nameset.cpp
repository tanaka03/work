//**************************************************
//
// 制作 ( 名まえ )
// Author : hamada ryuuga
//
//**************************************************
#include "nameset.h"
#include "input.h"
#include "manager.h"
#include "object2d.h"
#include "ranking.h"
#include "fade.h"
#include "playfab.h"
#include "sound.h"
#include "timer.h"
#include "player.h"

std::string  CNameSet::m_PlayName;

//==================================
// コンストラクター
//==================================
CNameSet::CNameSet()
{
	ON = false;
	if (m_object2d[0] != nullptr)
	{
		m_object2d[0] = nullptr;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_ListName[i] != nullptr)
		{
			m_ListName[i] = nullptr;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (m_PlayNameSet[i] != nullptr)
		{
			m_PlayNameSet[i] = nullptr;
		}
	}
}
//==================================
// デストラクタ
//==================================
CNameSet::~CNameSet()
{
}

//================
//初期化処理
//================
HRESULT CNameSet::Init(void)
{
	m_PlayName = "";
	m_NowPlay = 0;
	m_NemePos = D3DXVECTOR3(CManager::centerPos.x-300.0f, 100.0f, 0.0f);

	m_object2d[0] = CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_NAMEBG);
	m_object2d[0]->SetSize(CManager::centerPos);
	m_object2d[0]->SetPos(CManager::centerPos);

	m_object2d[1] = CObject2d::Create();
	m_object2d[1]->SetTexture(CTexture::TEXTURE_NAMETITLE);
	m_object2d[1]->SetSize(D3DXVECTOR3(500.0f, 175.0f, 0.0f));
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::centerPos.x, 575.0f, 0.0f));

	m_ListName[0] = CName::Create();
	m_ListName[0]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ListName[0]->SetPos(D3DXVECTOR3(CManager::centerPos.x -125.0f, 375.0f, 0.0f));
	m_ListName[0]->SetAlphabet(CName::MAX);

	m_ListName[1] = CName::Create();
	m_ListName[1]->SetSize(D3DXVECTOR3(75.0f, 75.0f, 0.0f));
	m_ListName[1]->SetPos(D3DXVECTOR3(CManager::centerPos.x, 350.0f, 0.0f));

	m_ListName[2] = CName::Create();
	m_ListName[2]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
	m_ListName[2]->SetPos(D3DXVECTOR3(CManager::centerPos.x + 125.0f, 375.0f, 0.0f));
	m_ListName[2]->SetAlphabet(CName::B);


	return S_OK;
}

//================
//破棄
//================
void CNameSet::Uninit(void)
{
	Release();
}

//============================
//更新処理
//============================
void CNameSet::Update(void)
{

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_RIGHT))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);
	}
	if (CInputpInput->Trigger(CInput::KEY_LEFT))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);
	}

	if (CInputpInput->Trigger(CInput::KEY_DELETE))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_BOM);
		if (m_NowPlay > 0)
		{
			if (m_PlayNameSet[m_NowPlay-1] != nullptr)
			{
				m_NowPlay--;
				m_PlayNameSet[m_NowPlay]->Uninit();
				m_PlayName = m_PlayName.substr(0, m_PlayName.length() - 1);
				m_NemePos.x -= 120.0f;
			}
		}
	}

	if (CInputpInput->Trigger(CInput::KEY_DECISION))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_ON);
		if (m_NowPlay >= 5)
		{
			if (!ON)
			{//モードの設定
				ON = true;
				int Score = CTimer::GetMyScore()+ CPlayer::GetHPNow();
				CRanking::SetScore(Score);
				CPlayfab::SetScore(m_PlayName, Score, []
				{
					CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RANKING);
				});
			}
			
			return;
		}
		CNameSet::RankingNeme();
	}	
}
//============================
//描画処理
//============================
void CNameSet::Draw(void)
{
}

//==================================
//rankingに名まえをねじ込む
//==================================
void CNameSet::RankingNeme()
{
	CName::ALPHABET Type = m_ListName[1]->GetAlphabet();

	if (Type >= CName::A && Type <= CName::Z)
	{
		m_PlayName += ('A' + (char)Type);
	}
	else if (Type == CName::MAX)
	{
		//モードの設定
		if (m_PlayName != "")
		{
			if (!ON)
			{//モードの設定
				ON = true;
				int Score = CTimer::GetMyScore() + CPlayer::GetHPNow();
				CRanking::SetScore(Score);
				CPlayfab::SetScore(m_PlayName, Score, []
				{
				
					CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_RANKING);
				});
			}
			
			return;
		}
		else
		{
			return;
		}
	}
	else
	{
		return;
	}

	m_PlayNameSet[m_NowPlay] = CName::Create();
	m_PlayNameSet[m_NowPlay]->SetSize(D3DXVECTOR3(60.0f, 60.0f, 0.0f));
	m_PlayNameSet[m_NowPlay]->SetPos(m_NemePos);
	m_PlayNameSet[m_NowPlay]->SetAlphabet(Type);
	m_PlayNameSet[m_NowPlay]->SetMoveSwitch(false);

	m_NemePos.x += 120.0f;
	m_NowPlay++;

}

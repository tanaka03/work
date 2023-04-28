//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************
#include <stdio.h>
#include "ranking.h"
#include "main.h"
#include "input.h"
#include "manager.h"
#include "texture.h"
#include "object2d.h"
#include "name.h"
#include "fade.h"

#include "playfab.h"

#include "sound.h"

#include "text.h"

#include "playfab/PlayFabError.h"

bool finished = false;

CScore *CRanking::m_Ranking[MAX_RANK];
int CRanking::m_score;
std::string  CRanking::m_PlayName;
std::string CRanking::m_name[5];


//========================
// コンストラクタ
//========================
CRanking::CRanking()
{
}

//========================
// デストラクタ
//========================
CRanking::~CRanking()
{
}

//========================
// 初期化
//========================
inline HRESULT CRanking::Init(void)
{
	for (int i = 0; i < 3; i++)
	{
		m_name[i] = "";
	}
	D3DXVECTOR3 pos = D3DXVECTOR3(CManager::centerPos.x, 100.0f, 0.0f);
	for (int i = 0; i < MAX_RANK - 1; i++)
	{
		m_Ranking[i] = CScore::Create(pos);
		m_Ranking[i]->Set(0);
		pos.y += 100.0f;
	}

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RANKING);
	
	m_NowPlay = 0;
	m_NemePos = D3DXVECTOR3(30.0f, 100.0f, 0.0f);

	m_object2d[0] = CObject2d::Create();
	m_object2d[0]->SetTexture(CTexture::TEXTURE_RANKINBG);
	m_object2d[0]->SetSize(CManager::centerPos);
	m_object2d[0]->SetPos(CManager::centerPos);

	m_object2d[1] = CObject2d::Create();
	m_object2d[1]->SetTexture(CTexture::TEXTURE_RANKIN);
	m_object2d[1]->SetSize(D3DXVECTOR3(100.0f, 300.0f, 0.0f));
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::centerPos.x - 120.0f, 350.0f, 0.0f));

	m_object2d[2] = CObject2d::Create();
	m_object2d[2]->SetTexture(CTexture::TEXTURE_RANKINTITLEOFF);
	m_object2d[2]->SetSize(D3DXVECTOR3(200.0f, 100.0f, 0.0f));
	m_object2d[2]->SetPos(D3DXVECTOR3(200.0f, 150.0f, 0.0f));

	finished = false;

	m_RankingSet = false;
	
	m_Ranking[5] = CScore::Create(pos);
	m_Ranking[5]->Set(m_score);

	GetScore();
	
	return E_NOTIMPL;
}

//========================
//　破棄
//========================
void CRanking::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	Release();
}

//========================
// 更新
//========================
void CRanking::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (finished)
	{
		m_object2d[2]->SetTexture(CTexture::TEXTURE_RANKINTITLEON);

		if (!m_RankingSet)
		{
			std::string Name;
			m_RankingSet = true;
	
			for (int i = 0; i < 3;i++)
			{
				Name += m_name[i];
				Name += "\n";
			}

			CText*Text = CText::Create(D3DXVECTOR3(0.0f, 100.0f, 0.0f), D3DXVECTOR3(640.0f, 200.0f, 0.0f), CText::MAX, 1000, 10, Name.c_str());
			Text->SetRelease(false);
			Text->SetCountXfast(20);
		}

		if (CInputpInput->Trigger(CInput::KEY_SHOT))
		{
			CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
			return;
		}
	}
}

//========================
// 描画
//========================
void CRanking::Draw()
{
}

void CRanking::GetScore()
{
	CPlayfab::GetScore([](const ClientModels::GetLeaderboardResult& resul) {

		for (auto item : resul.Leaderboard)
		{
			if (item.Position <= 4)
			{
				switch (item.Position)
				{
				case 0:
				
					break;
				case 1:
					
					break;
				case 2:
					break;
				case 3:
					break;
				default:
					break;
				}
				m_name[item.Position] += item.DisplayName;//なまえをキャラに変換
														  // 表示
				m_Ranking[item.Position]->Set(item.StatValue);

			}
		}
		finished = true;
	});
}

//========================
//ランキングの値をねじ込む
//========================
void CRanking::SetScore(int nScore)
{
	m_score = nScore;
}
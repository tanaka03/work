//============================
//
// ２Dpolygon設定
// Author:hamada ryuuga
//
//============================

#include "event.h"
#include "words.h"
#include "utility.h"
#include "object2d.h"
#include "game.h"
#include "player.h"
#include "fade.h"

//------------------------------------
// コンストラクタ
//------------------------------------
CEvent::CEvent() :CObject(PRIORITY_BG)
{
}

//------------------------------------
// デストラクタ
//------------------------------------
CEvent::~CEvent()
{
}

//------------------------------------
// 初期化
//------------------------------------
HRESULT CEvent::Init()
{
	

	m_sin = 0;
	m_moveSet = 0;
	m_object2d = CObject2d::Create(PRIORITY_EFFECT);
	m_object2d->SetSize(D3DXVECTOR3(1280.0f, 720.0f, 0.0f));
	m_object2d->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
	m_words[0] = CWords::Create("G", D3DXVECTOR3(m_EventPos.x - 350.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[1] = CWords::Create("A", D3DXVECTOR3(m_EventPos.x - 250.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[2] = CWords::Create("M", D3DXVECTOR3(m_EventPos.x - 150.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[3] = CWords::Create("E", D3DXVECTOR3(m_EventPos.x - 50.0f , m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[4] = CWords::Create("O", D3DXVECTOR3(m_EventPos.x + 50.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[5] = CWords::Create("V", D3DXVECTOR3(m_EventPos.x + 150.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[6] = CWords::Create("E", D3DXVECTOR3(m_EventPos.x + 250.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	m_words[7] = CWords::Create("R", D3DXVECTOR3(m_EventPos.x + 350.0f, m_EventPos.y, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), CFont::FONT_GON);
	
	m_count = 0;
	m_desCount = 0;
	m_moveCount = 0;
	m_arura = 0.0f;
	m_death = 0.0f;
	m_Ismove = false;
	m_IsEventStop = false;
	m_EventPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EventMove = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	return S_OK;
}

//------------------------------------
// 終了
//------------------------------------
void CEvent::Uninit()
{
	Release();
}

//------------------------------------
// 更新
//------------------------------------
void CEvent::Update()
{
	m_arura += 0.01f;
	m_death += 0.05f;
	if (m_death >=D3DX_PI*0.5f)
	{
		m_death = D3DX_PI*0.5f;
	}
	if (m_arura >= 0.8f)
	{
		m_arura = 0.8;
	}
	m_object2d->SetColar(D3DXCOLOR(0.0f, 0.0f, 0.0f, m_arura));
	m_desCount++;
	
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, m_death);

	if (m_desCount >= m_endDesCount)
	{
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
		CEvent::Uninit();
	}

	SinMove();
}

//------------------------------------
// 描画
//------------------------------------
void CEvent::Draw()
{
}

//------------------------------------
// create
//------------------------------------
CEvent *CEvent::Create(D3DXVECTOR3 pos, int EndCount, int EndDesCount, int EndmoveCount)
{
	CEvent * pObject = new CEvent;

	if (pObject != nullptr)
	{

		pObject->SetPos(pos);
		pObject->Init();
		pObject->SetEndCount(EndCount);
		pObject->SetDesCount(EndDesCount);
		pObject->SetEndMove(EndmoveCount);
	
	}
	return pObject;
}


//------------------------------------
// 動き系統
//------------------------------------
void CEvent::move()
{
	
	m_EventPos += m_EventMove;
}

void CEvent::SinMove()
{
	m_sin++;
	D3DXVECTOR3 move;
	m_moveCount++;
	if (m_moveCount >= m_timerCount)
	{
		m_moveCount = 0;

		if (m_moveSet >= 10)
		{
			m_moveSet = 0;
		}
		else
		{
			move.x = -5.0f;
		}
	}
	for (int i = 0; i < 8; i++)
	{
		move.y = cosf((D3DX_PI*2.0f) * 0.01f * (m_sin + (i * 10)));

		m_words[i]->SetMove(D3DXVECTOR3(0.0f, move.y, 0.0f));
	}
}
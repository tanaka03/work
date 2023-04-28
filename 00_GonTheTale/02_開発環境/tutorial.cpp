//=============================================================================
//
// リザルト画面
// Author:hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "tutorial.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"
#include "particle_manager.h"
#include "score.h"
#include "multiply.h"



//=============================================================================
// コンストラクター
//=============================================================================
CTutorial::CTutorial()
{
	m_nEnableTime = 0;
	m_nInterval = 300;
	m_bFire = false;
}

//=============================================================================
// デストラクト
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CTutorial::Init(void)
{
	m_NextTaskCount = 0;
	//m_Stage = CStage::Create(CStage::PATTERN_TITLE);

	//チュートリアル
	m_object2d[0] = CObject2d::Create(PRIORITY_FADE);
	m_object2d[0]->SetTexture(CTexture::TEXTURE_TUTORIAL002);
	m_object2d[0]->SetSize(CManager::centerPos);
	m_object2d[0]->SetPos(D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y, 0.0f));
	m_object2d[0]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//チュートリアル
	m_object2d[1] = CObject2d::Create(PRIORITY_FADE);
	m_object2d[1]->SetTexture(CTexture::TEXTURE_TUTORIAL001);
	m_object2d[1]->SetSize(CManager::centerPos);
	m_object2d[1]->SetPos(D3DXVECTOR3(CManager::centerPos.x, CManager::centerPos.y, 0.0f));
	m_object2d[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_TUTORIAL);
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CTutorial::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();

	CObject::Release();
	//CObjectXManager::ReleaseAll();
}

//=============================================================================
// 更新処理
//=============================================================================
void CTutorial::Update(void)
{
	CInput *CInputpInput = CInput::GetKey();

	if (CInputpInput->Trigger(CInput::KEY_SHOT))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_OFF);
		m_NextTaskCount++;
		if (m_NextTaskCount < MAXTASK)
		{	
			if (true)
			{
			}
			//m_object2d[1]->SetMove(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
		}
		else
		{
			//モードの設定
			CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CTutorial::Draw(void)
{

}
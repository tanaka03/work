//=============================================================================
//
// リザルト画面
// Author:hamada ryuuga
//
//=============================================================================
//-----------------------------------------------------------------------------
// iinclude
//-----------------------------------------------------------------------------
#include "result.h"
#include "input.h"
#include "manager.h"
#include "fade.h"
#include "sound.h"

#include "camera.h"
#include "utility.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CResult::CResult()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CResult::~CResult()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CResult::Init(void)
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

	m_Pos = 0.0f;

	////GonFoxのTITLE文字
	m_object2d[1] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_GAMECLEAR,
		CManager::centerPos,
		CManager::centerPos,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));

	m_object2d[0] = createObject(PRIORITY_UI,
		CTexture::TEXTURE_RESULT_GON,
		D3DXVECTOR3(CManager::centerPos.x, m_Pos, CManager::centerPos.z),
		CManager::centerPos,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	CManager::GetInstance()->GetSound()->Play(CSound::LABEL_BGM_RESULT);
	m_Rot = 0.0f;
	m_Colar = 0.0f;

	m_On = false;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CResult::Uninit(void)
{
	CManager::GetInstance()->GetSound()->Stop();
	CObject::Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CResult::Update(void)
{
	m_Pos += 3;
	if (m_Pos >= CManager::centerPos.y)
	{
		if (!m_On)
		{
			CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_ON);
		}
		m_On = true;

		m_Pos = CManager::centerPos.y;
		m_Colar += 0.05f;
		if (m_Colar >= 1.0f)
		{
			m_Colar = 1.0f;
		}
		m_object2d[1]->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Colar));
	}
	m_object2d[0]->SetPos(D3DXVECTOR3(CManager::centerPos.x, m_Pos, CManager::centerPos.z));

	CInput *CInputpInput = CInput::GetKey();
	if (CInputpInput->Trigger(CInput::KEY_SHOT))
	{
		CManager::GetInstance()->GetSound()->Play(CSound::LABEL_SE_ON);

		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_NAMESET);
	}
#ifdef _DEBUG

	if (CInputpInput->Trigger(CInput::KEY_DEBUG))
	{
		//モードの設定
		CManager::GetInstance()->GetFade()->NextMode(CManager::MODE_TITLE);
	}

#endif // DEBUG
}

//=============================================================================
// 描画処理
//=============================================================================
void CResult::Draw(void)
{
}
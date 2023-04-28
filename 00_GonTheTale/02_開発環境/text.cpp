//============================
//
// テキスト表示するべんり
// Author:hamada ryuuga
//
//============================

#include "text.h"
#include "manager.h"
#include "renderer.h"
#include "hamada.h"
#include "input.h"
#include <Shlwapi.h>

//=============================================================================
// コンストラクタ関数
//=============================================================================
CText::CText(int list) : CObject2d(list)
{
}

//=============================================================================
// デストラクタ関数
//=============================================================================
CText::~CText()
{
}

//=============================================================================
// 初期化関数
//=============================================================================
HRESULT CText::Init()
{
	m_newlineCount = 0;
	m_wordsPopCount = 0;
	m_wordsPopCountX = 0;
	m_AddCount = 0;
	m_Text = "";
	CObject2d::Init();
	
	CObject2d::SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	SetTex(PositionVec4(
		0.0f, 1.0f, 0.0f, 1.0f));

	m_isRelease = false;
	m_DesTimar = 0;
	m_func = nullptr;

	return S_OK;
}

//=============================================================================
// 破棄関数
//=============================================================================
void CText::Uninit()
{


	for (int wordsCount = 0; wordsCount < m_TextSize; wordsCount++)
	{
		if (m_words[wordsCount] != nullptr)
		{
			m_words[wordsCount]->Uninit();
		}
	}
	delete m_words;

	CObject2d::Uninit();
}

//=============================================================================
// 更新関数
//=============================================================================
void CText::Update()
{
	CObject2d::Update();

	m_AddCount++;
	if (m_AddCount >= m_Addnumber)
	{
		if (m_AddLetter <= m_TextSize)
		{
			m_Text += m_ALLText[m_AddLetter];
			std::string Txt = m_Text;
			if (Txt != "")
			{//空白チェック
				if (hmd::is_sjis_lead_byte(m_ALLText[m_AddLetter])
					&& m_AddLetter < m_TextSize)
				{

					m_AddLetter++;
					m_Text += m_ALLText[m_AddLetter];
					m_AddLetter++;
					m_words[m_wordsPopCount] = CWords::Create(m_Text.c_str(),
						D3DXVECTOR3((50.0f * (m_wordsPopCountX + 1)), m_pos.y + m_newlineCount*100.0f, m_pos.z),
						D3DXVECTOR3(20.0f, 20.0f, 0.0f),
						m_FontType);
					m_wordsPopCount++;
					m_wordsPopCountX++;
				}
				else
				{
					if (m_Text != "\n")
					{
						m_AddLetter++;
						m_words[m_wordsPopCount] = CWords::Create(m_Text.c_str(),
							D3DXVECTOR3(50.0f * (m_wordsPopCountX + 1), m_pos.y + m_newlineCount*100.0f, m_pos.z),
							D3DXVECTOR3(20.0f, 20.0f, 0.0f),
							m_FontType);
						m_wordsPopCount++;
						m_wordsPopCountX++;
					}
					else
					{
						m_wordsPopCountX = m_wordsPopCountXfast;
						m_AddLetter++;
						m_newlineCount++;
					}
				}

			}
		}
		m_Text = "";
		m_AddCount = 0;
	}

	if (m_isRelease)
	{
	
		m_DesTimar--;
		

		if (m_DesTimar <= 0)
		{
			if (m_func != nullptr)
			{
				m_func();
			}
			Uninit();
		}
	}
	else
	{
		CInput *CInputpInput = CInput::GetKey();
		if (CInputpInput->Trigger(CInput::KEY_SHOT))
		{
			Uninit();
		}
	}
}

//=============================================================================
// 描画関数
//=============================================================================
void CText::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 0);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	CObject2d::Draw();



	// 新規深度値 <= Zバッファ深度値 (初期設定)
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// αテストを無効に戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// 生成関数
//=============================================================================
CText *CText::Create(D3DXVECTOR3 SetPos, D3DXVECTOR3 SetSize, Type talkType,int DeleteTime, int SpeedText,const char * Text, CFont::FONT Type, int wordsPopCountX,bool Nottimerdelete)
{
	CText * pObject = nullptr;
	pObject = new CText(3);

	if (pObject != nullptr)
	{
		pObject->SetCountXfast(wordsPopCountX);
		pObject->Init();

		switch (talkType)
		{
		case CText::GON:
			pObject->SetTexture(CTexture::TEXTURE_GONBOX);
			break;
		case CText::MASUO:
			pObject->SetTexture(CTexture::TEXTURE_NONE);
			break;
		case CText::MAX:
			pObject->SetTexture(CTexture::TEXTURE_NONE);
			pObject->SetColar(D3DXCOLOR(1.0f, 1.0f, 1.0f,0.0f));
			break;
		default:
			break;
		}

		pObject->SetPos(SetPos);
		pObject->SetSize(SetSize);
		pObject->SetFont(Type);
		pObject->Releasetimer(DeleteTime);
		pObject->TextLetter(Text, SpeedText);
	
		pObject->SetRelease(Nottimerdelete);
	}

	return pObject;
}


//=============================================================================
// けすまでの時間設定関数
//=============================================================================
void CText::Releasetimer(int nTimar)
{
	m_DesTimar = nTimar;
	m_DesTimarMax = m_DesTimar;
	m_isRelease = true;
}

//=============================================================================
// けすまでの時間設定関数
//=============================================================================
void CText::TextLetter(const char * Text, int SpeedText)
{
	m_ALLText = Text;
	m_TextSize = m_ALLText.size();
 	m_Addnumber = SpeedText;
	m_AddLetter = 0;
	m_words = new CWords*[m_TextSize];
	for (int wordsCount = 0; wordsCount < m_TextSize; wordsCount++)
	{
		m_words[wordsCount] = nullptr;
	}

}

//=============================================================================
// 消滅する時のイベント設定
//=============================================================================
void CText::Setfunc(std::function<void(void)> func)
{
	m_func = func;
}

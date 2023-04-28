//=============================================================================
//
// Object
// Author : 浜田琉雅
//
//=============================================================================

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "object.h"
#include "object2d.h"
#include "manager.h"
#include "score.h"
#include <assert.h>
#include "game.h"
#include "pause.h"

//-----------------------------------------------------------------------------
// 静的メンバー変数の宣言
//-----------------------------------------------------------------------------
int CObject::m_AllMember = 0; 
int CObject::m_AllEnemy = 0;

CObject *CObject::m_Top[] = {};
CObject* CObject::m_Current[] = {};

//=============================================================================
// コンストラクト関数
//=============================================================================
CObject::CObject(int nPriority /* PRIORITY_3 */) :
	m_backObject(nullptr),
	m_nextObject(nullptr),
	m_death(false)
{
	m_type = NONE;
	if (m_Top[nPriority] == nullptr)
	{
		m_Top[nPriority] = this;
		m_Current[nPriority] = this;
	}
	else
	{
		this->m_backObject = m_Current[nPriority];
		m_Current[nPriority]->m_nextObject = this;
		m_Current[nPriority] = this;
	}
	m_nPriority = nPriority;
}

//=============================================================================
// デストラクト関数
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// AllUpdate関数
//=============================================================================
void CObject::AllUpdate()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *obj = m_Top[nCnt];

		while (obj)
		{
			CObject	*objnext = obj->m_nextObject;

			if (!obj->m_death)
			{
				obj->Update();
			}

			obj = objnext;
		}

		obj = m_Top[nCnt];

		while (obj)
		{
			CObject	*objnext = obj->m_nextObject;

			if (obj->m_death)
			{
				obj->ReleaseList();
			}
			obj = objnext;
		}
	}
}

//=============================================================================
// Typeのupdate関数
//=============================================================================
void CObject::TypeUpdate(EObjectType Type)
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *obj = m_Top[nCnt];
		while (obj)
		{
			CObject	*objnext = obj->m_nextObject;
			if (obj->GetType() == Type)
			{
				if (!obj->m_death)
				{
					obj->Update();
				}
			}

			obj = objnext;
		}
		obj = m_Top[nCnt];
		while (obj)
		{
			CObject	*objnext = obj->m_nextObject;
			if (obj->m_death)
			{

				obj->ReleaseList();

			}
			obj = objnext;
		}
	}
}

//=============================================================================
// AllDraw関数
//=============================================================================
void CObject::AllDraw()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *obj = m_Top[nCnt];
		while (obj)
		{
			if (!obj->m_death)
			{
				obj->Draw();
			}

			if (obj->m_nextObject == nullptr)
			{
				break;
			}
			else
			{
				obj = obj->m_nextObject;
			}
		}
	}
}

//=============================================================================
// NotBGDraw関数
//=============================================================================
void CObject::TypeDraw(EObjectType Type)
{
	Type;
}

//=============================================================================
// AllUninit関数
//=============================================================================
void CObject::AllUninit()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *obj = m_Top[nCnt];
		if (obj != nullptr)
		{
			while (obj)
			{
				if (obj->m_nextObject == nullptr)
				{
					obj->Uninit();
					obj->Release();
					obj = nullptr;
					break;
				}
				else
				{
					CObject *objnext = obj->m_nextObject;
					obj->Uninit();
					obj->Release();
					obj = nullptr;
					obj = objnext;
				}
			}

		}
		obj = m_Top[nCnt];
		if (obj != nullptr)
		{
			while (obj)
			{
				CObject	*objnext = obj->m_nextObject;

				if (obj->m_death)
				{

					obj->ReleaseList();

				}
				obj = objnext;
			}
		}
	}
}

//=============================================================================
// ModeNotUninit関数
//=============================================================================
void CObject::ModeNotUninit()
{
	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *obj = m_Top[nCnt];

		if (obj == nullptr)
		{
			continue;
		}

		while (obj)
		{
			if (obj->m_type != MODE)
			{
				if (obj->m_nextObject == nullptr)
				{
					obj->Uninit();
					obj = nullptr;
					break;
				}
				else
				{
					CObject *objnext = obj->m_nextObject;
					obj->Uninit();
					obj = objnext;
				}
			}
			else
			{
				if (obj->m_nextObject == nullptr)
				{
					break;
				}
				else
				{
					CObject *objnext = obj->m_nextObject;
					obj = objnext;
				}
			}
		}
	}
}

//=============================================================================
// SelectModelObject関数
//=============================================================================
CObject* CObject::SelectModelObject(int IsNumber, EObjectType Type)
{
	int SetNumber = 0;

	for (int nCnt = 0; nCnt < PRIORITY_MAX; nCnt++)
	{
		CObject *obj = m_Top[nCnt];

		if (obj == nullptr)
		{
			continue;
		}

		while (obj)
		{
			if (obj->m_type == Type)
			{//特定のTypeを探す

				if (obj->m_nextObject == nullptr)
				{
					if (SetNumber >= IsNumber)
					{//一定回数以上なら情報を返す
						return obj;
					}
					break;
				}
				else
				{
					if (SetNumber >= IsNumber)
					{
						//一定回数以上なら情報を返す
						return obj;
					}
					SetNumber++;
					CObject *objnext = obj->m_nextObject;
					obj = objnext;
				}
			}
			else
			{
				if (obj->m_nextObject == nullptr)
				{
					break;
				}
				else
				{
					CObject *objnext = obj->m_nextObject;
					obj = objnext;
				}
			}
		}
	}
	//assert(false);
	return nullptr;
}
//=============================================================================
// 検索関数
//=============================================================================
void CObject::SearchModelObject(int Priority, EObjectType Type, std::function<void(CObject*)> func)
{
	CObject *obj = m_Top[Priority];

	while (obj)
	{
		if (obj->m_type == Type)
		{//特定のTypeを探す

			func(obj);
			
		}

		CObject *objnext = obj->m_nextObject;
		obj = objnext;
	}
}

//=============================================================================
// Set関数
//=============================================================================
void CObject::SetUp(EObjectType Type)
{
	//m_Type = Type;
	switch (Type)
	{
	case EObjectType::ENEMY:
	{	
		m_type = ENEMY;
		break;
	}
	case EObjectType::PLAYER:
	{
		m_type = PLAYER;
		break;
	}
	case EObjectType::BULLET:
		m_type = BULLET;
		break;
	case EObjectType::GON:
		m_type = GON;
		break;
	case EObjectType::MAGIC:
		m_type = MAGIC;
		break;
	case EObjectType::CRYSTAL:
		m_type = CRYSTAL;
		break;
	case EObjectType::BG:
		m_type = BG;
		break;
	case EObjectType::MODE:
		m_type = MODE;
		break;
	case EObjectType::PAUSE:
		m_type = PAUSE;
		break;
	case EObjectType::BUILDING:
		m_type = BUILDING;
		break;
	case EObjectType::MESH:
		m_type = MESH;
		break;

	case EObjectType::BOSS:
	{
		m_type = BOSS;
		break;
	}
	default:
		break;
	}
	
}

void CObject::ReleaseList()
{

	CObject *pDeleteObj = this;

	if (pDeleteObj == nullptr)
	{// 消そうとしてるやつが使われているかどうか
		return;
	}
	else if (m_backObject == nullptr && m_nextObject == nullptr)
	{// オブジェクトが秘湯しかないとき
		m_Top[m_nPriority] = nullptr;
		m_Current[m_nPriority] = nullptr;
	}
	else if (m_backObject == nullptr)
	{// Topが消えた時
		m_Top[m_nPriority] = pDeleteObj->m_nextObject;
		m_Top[m_nPriority]->m_backObject = nullptr;
	}
	else if (m_nextObject == nullptr)
	{// Currentが消えた時
		m_Current[m_nPriority] = pDeleteObj->m_backObject;
		m_Current[m_nPriority]->m_nextObject = nullptr;
	}
	else
	{// 間のオブジェクトが消えた時
		pDeleteObj->m_backObject->m_nextObject = pDeleteObj->m_nextObject;
		pDeleteObj->m_nextObject->m_backObject = pDeleteObj->m_backObject;
	}

	delete pDeleteObj;
}
//=============================================================================
// release関数
//=============================================================================
void CObject::Release()
{
	m_death = true;
}

//=============================================================================
// release関数
//=============================================================================
void CObject::NotRelease()
{
	m_death = false;
}

////=============================================================================
//// objectのデータを取得する関数
////=============================================================================
//CObject**CObject::GetObjectData(int nCount)
//{
//	return nullptr;
//}




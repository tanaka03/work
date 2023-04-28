//=============================================================================
//
// Object
// Author : �l�c����
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
// �ÓI�����o�[�ϐ��̐錾
//-----------------------------------------------------------------------------
int CObject::m_AllMember = 0; 
int CObject::m_AllEnemy = 0;

CObject *CObject::m_Top[] = {};
CObject* CObject::m_Current[] = {};

//=============================================================================
// �R���X�g���N�g�֐�
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
// �f�X�g���N�g�֐�
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// AllUpdate�֐�
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
// Type��update�֐�
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
// AllDraw�֐�
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
// NotBGDraw�֐�
//=============================================================================
void CObject::TypeDraw(EObjectType Type)
{
	Type;
}

//=============================================================================
// AllUninit�֐�
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
// ModeNotUninit�֐�
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
// SelectModelObject�֐�
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
			{//�����Type��T��

				if (obj->m_nextObject == nullptr)
				{
					if (SetNumber >= IsNumber)
					{//���񐔈ȏ�Ȃ����Ԃ�
						return obj;
					}
					break;
				}
				else
				{
					if (SetNumber >= IsNumber)
					{
						//���񐔈ȏ�Ȃ����Ԃ�
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
// �����֐�
//=============================================================================
void CObject::SearchModelObject(int Priority, EObjectType Type, std::function<void(CObject*)> func)
{
	CObject *obj = m_Top[Priority];

	while (obj)
	{
		if (obj->m_type == Type)
		{//�����Type��T��

			func(obj);
			
		}

		CObject *objnext = obj->m_nextObject;
		obj = objnext;
	}
}

//=============================================================================
// Set�֐�
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
	{// �������Ƃ��Ă����g���Ă��邩�ǂ���
		return;
	}
	else if (m_backObject == nullptr && m_nextObject == nullptr)
	{// �I�u�W�F�N�g���铒�����Ȃ��Ƃ�
		m_Top[m_nPriority] = nullptr;
		m_Current[m_nPriority] = nullptr;
	}
	else if (m_backObject == nullptr)
	{// Top����������
		m_Top[m_nPriority] = pDeleteObj->m_nextObject;
		m_Top[m_nPriority]->m_backObject = nullptr;
	}
	else if (m_nextObject == nullptr)
	{// Current����������
		m_Current[m_nPriority] = pDeleteObj->m_backObject;
		m_Current[m_nPriority]->m_nextObject = nullptr;
	}
	else
	{// �Ԃ̃I�u�W�F�N�g����������
		pDeleteObj->m_backObject->m_nextObject = pDeleteObj->m_nextObject;
		pDeleteObj->m_nextObject->m_backObject = pDeleteObj->m_backObject;
	}

	delete pDeleteObj;
}
//=============================================================================
// release�֐�
//=============================================================================
void CObject::Release()
{
	m_death = true;
}

//=============================================================================
// release�֐�
//=============================================================================
void CObject::NotRelease()
{
	m_death = false;
}

////=============================================================================
//// object�̃f�[�^���擾����֐�
////=============================================================================
//CObject**CObject::GetObjectData(int nCount)
//{
//	return nullptr;
//}




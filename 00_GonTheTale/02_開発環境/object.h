//=============================================================================
//
// オブジェクト
// Author : 浜田琉雅
//
//=============================================================================
#ifndef _OBJECT_H_			// このマクロ定義がされてなかったら
#define _OBJECT_H_			// 二重インクルード防止のマクロ定義

#include "renderer.h"

//-----------------------------------------------------------------------------
// オブジェクト基本クラス
//-----------------------------------------------------------------------------
class CObject
{
public:
	// タイプ
	enum EObjectType
	{
		ENEMY = 0,
		PLAYER,
		BULLET,
		GON,
		MAGIC,
		CRYSTAL,
		BG,
		SORCERY,
		BELL,
		MODE,
		RANKUPBULLET,
		PAUSE,
		BUILDING,
		MESH,
		BOSS,
		MAX,
		NONE
	};
	
	// プライオリティの種類
	enum PRIORITY
	{
		PRIORITY_BG = 0,
		PRIORITY_PLAYER,
		PRIORITY_OBJECT,
		PRIORITY_EFFECT,
		PRIORITY_POPEFFECT,
		PRIORITY_UI,
		PRIORITY_FADE,
		PRIORITY_COUNTDOWN,
		PRIORITY_MAX
	};

	CObject(int list = 0);
	virtual ~CObject();
	virtual HRESULT Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void AllUpdate();
	static void TypeUpdate(EObjectType Type);
	static void AllDraw();
	static void AllUninit();

	static void ModeNotUninit();
	static void TypeDraw(EObjectType Type);

	static int& GetMaxEnemy() { return m_AllEnemy; };

	static CObject* GetTop(int IsTop) { return m_Top[IsTop]; }

	static CObject* GetCurrent(int IsCurrent) { return m_Current[IsCurrent]; }
	static CObject* SelectModelObject(int IsNumber, EObjectType Type);
	static void SearchModelObject(int Priority, EObjectType Type,std::function<void(CObject*)> func);


	EObjectType &GetType() { return m_type; }
	CObject* GetNext() { return m_nextObject; }
	bool GetDeath() { return m_death; }
	int * GetId();

	//CObject ** GetObjectData(int nCount);
	void SetUp(EObjectType Type);

	void Release();
	void NotRelease();
	void ReleaseList();

protected:
	CObject *m_nextObject;
	CObject *m_backObject;

	static CObject *m_Top[PRIORITY_MAX];
	static CObject *m_Current[PRIORITY_MAX];
	static int m_AllEnemy;

	EObjectType m_type;
	int m_nPriority;
private:
	//int	m_nID;

	static int m_AllMember;
	bool m_death;
};
#endif
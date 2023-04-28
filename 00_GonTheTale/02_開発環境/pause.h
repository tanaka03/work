//=========================================
// 
// pauseの作成(ヘッダーファイル)
// Author HAMAD
// 
//=========================================
#ifndef _PAUSE_H_
#define _PAUSE_H_


#include "object.h"
#include "object2d.h"

//------------------------------------
// プロトタイプ宣言
//------------------------------------

class CPause :public CObject
{
public:

	//画面(モード)の種類
	enum MODE
	{
		MODE_GAME = 0,			//ゲーム画面	
		MODE_RETURN,
		MODE_TITLE,
		MODE_END,
		MODE_MAX
	};

	CPause();
	~CPause();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	void Set() { m_OnPause = !m_OnPause; };
	bool Get() { return m_OnPause; };
private:
	bool m_OnPause;
	int m_NextMode;
	CObject2d *m_Bg;
	CObject2d *m_object2d[4];

};



#endif 

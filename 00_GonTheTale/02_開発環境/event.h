//=============================================================================
//
// ������
// Author : �l�c����
//
//=============================================================================


#ifndef _EVENT_H_			// ���̃}�N����`������ĂȂ�������
#define _EVENT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object.h"
class  CWords;
class  CObject2d;
class CEvent : public CObject
{
public:

	enum PosType
	{
		TYPE_2D = 0,	// 2d���W�ŕ\��
		TYPE_3D,		// 3d���W�ŕ\��
		MAX			// ���񂽂����H
	};

	CEvent();
	~CEvent() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetEndCount(int EndCount) { m_endCount = EndCount; }
	void SetDesCount(int DesCount) { m_endDesCount = DesCount;}
	void SetEndMove(int EndMove) { m_endmoveCount = EndMove;}
	void SetPos(D3DXVECTOR3 EventPos) { m_EventPos = EventPos; }

	static CEvent* Create(D3DXVECTOR3 pos, int EndCount, int EndDesCount, int EndmoveCount);
private:
	D3DXVECTOR3 m_EventPos;
	D3DXVECTOR3 m_EventMove;

	void move();
	void SinMove();
	int m_count;
	int m_desCount;
	int m_moveCount;
	int m_endCount;
	int m_endDesCount;
	int m_endmoveCount;
	int m_moveSet;
	int m_timerCount = 30;
	int m_sin;
	float m_arura;
	float m_death;
	CWords * m_words[10]; //NowLoading;
	CObject2d * m_object2d; //NowLoading;
	bool m_Ismove;
	bool m_IsEventStop;

	
};
#endif

//=============================================================================
//
// BOSS
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _BOSS_H_
#define	_BOSS_H_

#include"enemy.h"


class  CBossbar;
class CShadow;
class CObject2d;

namespace nl = nlohmann;
//**************************************************
// �N���X
//**************************************************
class  CBoss : public CEnemy
{
public:

	const int METEOTIME = 20;
	const int METEOMAX = 3;

	const int ATTACKTIME = 120;
	const int ATTACKMAX = 3;
	const int ATTACKBACK = 1500;

	const int METEOMOVETIME = 150;
	const int METEOMOVEMAX = 1;
	const int METEOMOVEBACK = 1500;
	enum BOSSMOVETYPE
	{
		NONE = 0,		// �ʏ�
		METEO,		// �U��
		MOVE,		//����
		ATTACKMOVE,		//����
		MAXBOSS			//���񂽂����H
	};

	static CBossbar *m_life;

	CBoss();
	~CBoss() override;

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CBoss *Create(D3DXVECTOR3 pos);
	void Move();
	void quat() {}
	void Hit(CObject *object)override;
	void NotHit()override;

	//	Boss�̃C�x���g�܂ł̎��Ԓǉ�
	void AddeventList(const int IseventList) { m_eventList.push_back(IseventList); }
	//	Boss�̃C�x���g�܂ł̎��ԃZ�b�g
	void SeteventList(const int IsPoptime, const int IseventList) { m_eventList.at(IsPoptime) = IseventList; }
	//	Boss�̃C�x���g�܂ł̎��ԃQ�b�g
	int GeteventList(const int IsPoptime) { return m_eventList.at(IsPoptime); }
	//	Boss�̃C�x���g�܂ł̎��Ԃ̑����擾
	int GeteventListSize() { return m_eventList.size(); }

	//	Boss�̃C�x���g�^�C�v��ǉ�
	void AddeBossMoveType(const BOSSMOVETYPE IsBossMoveType) { m_BossMoveType.push_back(IsBossMoveType); }
	//	Boss�̃C�x���g�^�C�v���Z�b�g
	void SetBossMoveType(const int IsPoptime, const BOSSMOVETYPE IsBossMoveType) { m_BossMoveType.at(IsPoptime) = IsBossMoveType; }
	//	Boss�̃C�x���g�^�C�v���Q�b�g
	int GetBossMoveType(const int IsPoptime) { return m_BossMoveType.at(IsPoptime); }
	//	Boss�̃C�x���g�^�C�v�̑����̎擾
	int GetBossMoveTypetSize() { return m_BossMoveType.size(); }


	void BossEventLood();

	static void Add(int IsAdd);
	static void DesEvent();
	void SetcheckHit(bool length) { m_hit = length; m_damage = 120; }
private:

	void Attack();
	void Meteo();
	void MeteoMove();

	float pointCollar;
	static int m_Hp;
	int m_Meteosleep;
	int m_Meteo;
	int m_Attacksleep;
	int m_attack;
	int m_frameCount;
	int m_nouevent;
	int m_MeteoMovesleep;
	int m_MeteoMove;
	int m_damage;
	std::vector <int>m_eventList;

	bool m_isMeteo;
	bool m_isAttack;
	bool m_isMeteoMove;
	bool m_isTop;
	bool m_hit;
	bool m_isMove;

	bool m_isFly;
	bool m_isAction;

	bool m_change;
	static bool m_DesEvent;

	D3DXVECTOR3 m_AttackMove;
	D3DXVECTOR3 m_targetPos;
	D3DXVECTOR3 m_m_MeteoMoveSpeed;
	D3DXVECTOR3 m_Gurabitexi;
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_posOld;

	BOSSMOVETYPE m_action;
	std::vector <BOSSMOVETYPE>m_BossMoveType;
	nl::json JBoss;//���X�g�̐���

	CShadow *m_shadow;

	CObject2d *m_object2d;
};

#endif // !_PENBULUM_H_



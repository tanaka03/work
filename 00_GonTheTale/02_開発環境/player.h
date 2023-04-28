//=============================================================================
//
// �v���C���[�ݒ�w�b�^�[
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "3dpolygon.h"
//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------

class CHpNumber;
class CBossbar;
class CSelect;
class CEvent;
//-----------------------------------------------------------------------------
// �v���C���[����L�����N�^�[�N���X
//-----------------------------------------------------------------------------
class CPlayer : public C3dpolygon
{
public:


public: // �萔
	static const int MAXLIFE;				// �ő�̗�
	static const float MOVE_ATTENUATION;	// �����W��
	static const float MOVE_ROTATTENUATION;	// ��]�ړ������W��
	static const float SPEED;				// �X�s�[�h
	static const float SPEEDMAX;				// �X�s�[�h
	static const float WIDTH;				// ���f���̔��a
	static const int MAX_PRAYER;			// �ő吔
	static const int MAX_MOVE;				// �A�j���[�V�����̍ő吔
	static const int INVINCIBLE;			// ���G����
	static const int MAX_MODELPARTS;		// ���f���̍ő吔
	static const int HP;				// HP

	enum PlayerType
	{
		DEFAULT_MOVE = 0,	// ��{�̓���
		GRAVITY_MOVE,		// �d�͂ŗ�������
		MAX			// ���񂽂����H
	};

public:
	CPlayer(const int list);;
	~CPlayer();

	HRESULT Init()override;	// ������
	void Uninit()override;	// �j��
	void Update()override;	// �X�V
	void Draw()override;	// �`��

	static CPlayer *Create();
	//------------------------------------
	//���W�̍���������� 
	//------------------------------------
	void SetDifferenceMove(D3DXVECTOR3 move) { m_move = move - m_pos; }
	void SetNowType(PlayerType Type) { m_NowType = Type; }
	void DamageHit(int Damage);

	static int GetHPNow() { return m_HPNow; }
private:
	void Move();		// �ړ�
	void GravityMove();		// �d�͂���ړ�
private:
	D3DXVECTOR3 m_move;
	D3DXVECTOR3 m_posOld;

	//���m�͈�
	D3DXVECTOR2 m_wallmin;
	D3DXVECTOR2 m_wallmax;

	static int m_HPNow;
	int m_jumpCount;
	bool m_loolHit;
	bool m_attack;
	bool m_jump;
	bool m_isDaesh;

	PlayerType m_NowType;

	CSelect*m_Select;
	CEvent *m_Event;
	std::vector<D3DXVECTOR3> m_logPos;
	CBossbar* m_Hp;
	CHpNumber* m_HpNumber;
};
#endif

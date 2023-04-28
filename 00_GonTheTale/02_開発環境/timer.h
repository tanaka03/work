//==================================================
// timer.h
// Author: tutida ryousei
//==================================================
#ifndef _TIMER_H_
#define _TIMER_H_

#include"object.h"

class CNumber;
class CObject2d;

class CTimer : public CObject
{
public:
	CTimer();
	~CTimer();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CTimer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time);
	void SetTimer();		// �^�C�}�[�̐ݒ�
	void ZeroAlpha();		// �擪��0������
	void AddTime(int add);	// ���Ԃ̉��Z

							// �Z�b�^�[
	void SetDestPos(D3DXVECTOR3 destpos) { m_DestPos = destpos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetTimer(int time) { m_nTime = time; }

	// �Q�b�^�[
	bool GetTimeUp() { return m_bTimeUp; }
	int GetTime() { return m_nTime; }
	static int GetMyScore() { return m_Myscore; };
private:
	static const int m_nNumTimer = 3;	// �^�C�}�[�̌���
	int m_nTime;						// ����
	static int m_Myscore;						// ����
	int m_nFrameCount;					// �t���[���J�E���g
	int m_nZeroCount;					// �擪��0�̐�
	int m_aPosTexU[m_nNumTimer];		// �e���̊i�[��
	bool m_bCountType;					// �J�E���g�A�b�v���J�E���g�_�E����
	bool m_bTimeUp;						// �^�C���A�b�v������
	D3DXVECTOR3 m_Pos;					// �ʒu
	D3DXVECTOR3 m_TimePos;				// ���v�̈ʒu
	D3DXVECTOR3 m_DestPos;				// �ړI�̈ʒu
	D3DXVECTOR3 m_size;					// �T�C�Y
	CNumber *m_pNumber[m_nNumTimer];	// �����̏��
	CObject2d *m_pObject2D;				// �I�u�W�F�N�g2D�̏��
};

#endif // !_TIMER_H_

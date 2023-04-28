//==================================================
// timer.h
// Author: tutida ryousei
//==================================================
#ifndef _HPNUMBER_H_
#define _HPNUMBER_H_

#include"object.h"

class CNumber;
class CObject2d;

class CHpNumber : public CObject
{
public:
	CHpNumber();
	~CHpNumber();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CHpNumber *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, int time);
	void SetNumber();		// �^�C�}�[�̐ݒ�
	void ZeroAlpha();		// �擪��0������
	void AddNumber(int add);	// ���Ԃ̉��Z

							// �Z�b�^�[
	void SetDestPos(D3DXVECTOR3 destpos) { m_DestPos = destpos; }
	void SetSize(D3DXVECTOR3 size) { m_size = size; }
	void SetNumber(int time) { m_nNumber = time; }

	// �Q�b�^�[
	bool GetNumberUp() { return m_bNumberUp; }
	int GetNumber() { return m_nNumber; }

private:
	static const int m_nNumNumber = 3;	// �^�C�}�[�̌���
	int m_nNumber;						// ����
	int m_nFrameCount;					// �t���[���J�E���g
	int m_nZeroCount;					// �擪��0�̐�
	int m_aPosTexU[m_nNumNumber];		// �e���̊i�[��
	bool m_bCountType;					// �J�E���g�A�b�v���J�E���g�_�E����
	bool m_bNumberUp;						// �^�C���A�b�v������
	D3DXVECTOR3 m_Pos;					// �ʒu
	D3DXVECTOR3 m_NumberPos;				// ���v�̈ʒu
	D3DXVECTOR3 m_DestPos;				// �ړI�̈ʒu
	D3DXVECTOR3 m_size;					// �T�C�Y
	CNumber *m_pNumber[m_nNumNumber];	// �����̏��
	CObject2d *m_pObject2D;				// �I�u�W�F�N�g2D�̏��
};

#endif // !_TIMER_H_

//============================
//
// �J�����ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "renderer.h"


class CCamera
{
private: // �v���C�x�[�g�萔
	static const D3DXVECTOR3 INIT_POSV;		// �ʒu�̏����ʒu
	static const float MOVE_ATTENUATION;	// �����W��
	static const float FIELD_OF_VIEW;		// ����p
	static const float NEAR_VALUE;			// �j�A
	static const float FUR_VALUE;			// �t�@�[
	static const float MOVE_ANGLE;	// �����W��

public:

	CCamera();
	~CCamera();

	void Init(void);	// ������
	void Uninit(void);	// �j��
	void Update(void);	// �X�V
	void Set(int Type);	// ��ʐݒ�

	void GameInit();
	D3DXMATRIX *GetMtxProje() { return &m_mtxProje; }
	D3DXMATRIX *GetMtxView() { return &m_mtxView; }
	D3DXVECTOR3 *GetPos() { return &m_posV; }
	D3DXVECTOR3 *GetPosR() { return &m_posR; }
	D3DXVECTOR3 *GetRot() { return &m_rot; }
	
	 void SetPos(D3DXVECTOR3 IsposV) { m_posV = IsposV; }
	 void SetPosR(D3DXVECTOR3 IsposR) { m_posR = IsposR; }
	void Setisfree() { m_isFree = !m_isFree; }
	bool Getisfree() {return m_isFree; }
	//	Animation�̓ǂݍ���
	void LandAnimation(std::string);

	//	�����Animation��ǉ�
	void AddAnimation();

	//	Animation�̂������̎擾
	int GetAnimationSize();

	void PlayAnimation(int Animation, bool Isloop);
	void PlayAnimation(std::string AnimationName, bool Isloop, std::function<void()> func = nullptr);

	void ShakeCamera(int IsFrameCount, float IsShakePow);

	void SetEnd(bool IsEnd) { m_bossEnd = IsEnd; }
private:
	int m_type;
	int m_nouAnimation;
	int m_isFrameCount;
	float m_speed = 1.0f;
	float m_rotSpeed = 0.05f;
	float m_rotSpeed2 = D3DX_PI / 2;
	float m_fDistance;					// ����
	float m_fDistanceY;
	float m_isShakePow;

	D3DXVECTOR3 m_posV;				// �ʒu
	D3DXVECTOR3 m_posR;				// �����_
	D3DXVECTOR3 m_vecU;				// �x�N�g��
	D3DXVECTOR3 m_directionV;			// ��]�̌����ʒu
	D3DXVECTOR3 m_directionR;			// ��]�̌��������_
	D3DXVECTOR3 m_rot;					// �ʒu��]
	
	D3DVIEWPORT9 m_viewport;
	D3DXVECTOR3 m_posVDest;
	D3DXVECTOR3 m_posRDest;
	D3DXMATRIX m_mtxProje;				// �v���W�F�N�V�����}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	D3DXMATRIX m_mtxView;				// �r���[�}�g���b�N�X//�|���S���̈ʒu���]�s�񂷂ׂĂ��߂Ă�i�j�J
	
	bool m_isAnimation;
	bool m_isFree;
	bool m_isLoop;
	bool m_bossEnd;

	std::function<void()> m_func;
};


#endif


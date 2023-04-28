//**************************************************
//
// Hackathon ( utility.h )
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _UTILITY_H_	// ���̃}�N����`������ĂȂ�������
#define _UTILITY_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �f�o�b�O�p
//==================================================
#include "main.h"

//--------------------------------------------------
// �o�͂Ƀe�L�X�g���o�͂���B
//--------------------------------------------------
#ifdef _DEBUG
#define DEBUG_PRINT(...) _RPT_BASE(_CRT_WARN, __FILE__, __LINE__, NULL, __VA_ARGS__)
#else
#define DEBUG_PRINT(...) ((void)0)
#endif

//==================================================
// �v���g�^�C�v�錾
//==================================================
//--------------------------------------------------
// �p�x�̐��K��
// ����  : pAngle / �p�x
//--------------------------------------------------
float NormalizeAngle(float *pAngle);

//--------------------------------------------------
// �z�[�~���O
// ����1  : D3DXVECTOR3 *pPosOut / �ʒu
// ����2  : D3DXVECTOR3 &posNow / ���݂̈ʒu
// ����3  : D3DXVECTOR3 &posDest / �ړI�̈ʒu
// ����4  : float fSpeed / ����
// �Ԓl  : bool / �ړI�̈ʒu�ɒ��������ǂ���
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed);

//--------------------------------------------------
// �����_�̃����_��
// ����1  : float fMax / �ő�l
// ����2  : float fMin / �ŏ��l
// �Ԓl  : float / �����_���l
//--------------------------------------------------
float FloatRandom(float fMax, float fMin);

//--------------------------------------------------
// �����̃����_��
// ����1  : int nMax / �ő�l
// ����2  : int nMin / �ŏ��l
// �Ԓl  : int / �����_���l
//--------------------------------------------------
int IntRandom(int nMax, int nMin);

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int nTime / �^�C��
// ����2  : float fCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��sin�J�[�u
//--------------------------------------------------
float SinCurve(int nTime, float fCycle);

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
// ����1  : int nTime / �^�C��
// ����2  : float fCycle / ����
// �Ԓl  : float / 1.0f�`0.0f��cos�J�[�u
//--------------------------------------------------
float CosCurve(int nTime, float fCycle);

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
// ����1  : float fCurve / �J�[�u
// ����2  : float fMax / �ő�l
// ����3  : float fMin / �ŏ��l
// �Ԓl  : float / �J�[�u
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin);

//--------------------------------------------------
// WorldCastScreen
// ����1  : D3DXVECTOR3 *screenPos // �X�N���[�����W
// ����2  : D3DXVECTOR3 screenSize // �X�N���[���T�C�Y
// ����3  : D3DXMATRIX* mtxView // �r���[�}�g���b�N�X
// ����4  : D3DXMATRIX* mtxProjection // �v���W�F�N�V�����}�g���b�N�X
// �Ԓl   : D3DXVECTOR3 2D��3D
//--------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize,									// �X�N���[���T�C�Y
	D3DXMATRIX* mtxView,									// �r���[�}�g���b�N�X
	D3DXMATRIX* mtxProjection);								// �v���W�F�N�V�����}�g���b�N�X

//--------------------------------------------------
// ScreenCastWorld
// ����1  : D3DXVECTOR3  *screenPos // �X�N���[�����W
// ����2  : D3DXVECTOR3 screenSize
// �Ԓl  : D3DXVECTOR3 / 3D��2D
//--------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(D3DXVECTOR3 *screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize);

bool CollisionCircle(D3DXVECTOR3 Pos1,
	                 float fRadius1, 
	                 D3DXVECTOR3 Pos2,
	                 float fRadius2);


// �Z�o�n��
//=============================================================================--------------
// // 2D�̊O��
// ����1  : D3DXVECTOR3  *v1 // 
// ����2  : D3DXVECTOR3*  v2
// �Ԓl  : float/ �O��
//=============================================================================--------------
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2);	// 2D�̊O��

// �Z�o�n��
//=============================================================================--------------
// // 2D�̓���
// ����1  : D3DXVECTOR3  *v1 // 
// ����2  : D3DXVECTOR3*  v2
// �Ԓl  : float / ����
//=============================================================================--------------
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2);	// 2D�̓���




#endif // !_UTILITY_H_

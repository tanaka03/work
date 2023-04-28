//**************************************************
// 
// Hackathon ( utility.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "renderer.h"
#include "utility.h"
#include "camera.h"

//--------------------------------------------------
// �p�x�̐��K��
//--------------------------------------------------
float NormalizeAngle(float *pAngle)
{
	if (*pAngle >= D3DX_PI)
	{// 3.14���傫��
		*pAngle -= D3DX_PI * 2.0f;
	}
	else if (*pAngle <= -D3DX_PI)
	{// -3.14��菬����
		*pAngle += D3DX_PI * 2.0f;
	}
	return *pAngle;
}

//--------------------------------------------------
// �z�[�~���O
//--------------------------------------------------
bool Homing(D3DXVECTOR3 *pPosOut, const D3DXVECTOR3 &posNow, const D3DXVECTOR3 &posDest, float fSpeed)
{
	D3DXVECTOR3 vecDiff = posDest - posNow;

	float fLength = D3DXVec3Length(&vecDiff);

	if (fLength <= fSpeed)
	{// ������蒷������������
		*pPosOut = posDest;
		return true;
	}
	else
	{// ������蒷�����傫����
		*pPosOut = posNow + ((vecDiff / fLength) * fSpeed);
		return false;
	}
}

//--------------------------------------------------
// �����_�̃����_��
//--------------------------------------------------
float FloatRandom(float fMax, float fMin)
{
	return ((rand() / (float)RAND_MAX) * (fMax - fMin)) + fMin;
}

//--------------------------------------------------
// �����̃����_��
//--------------------------------------------------
int IntRandom(int nMax, int nMin)
{
	return (int)((rand() / (float)RAND_MAX) * (nMax - nMin)) + nMin;
}

//--------------------------------------------------
// sin�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float SinCurve(int nTime, float fCycle)
{
	return  (sinf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// cos�J�[�u�̒l��1.0f�`0.0f�ŋA���Ă���
//--------------------------------------------------
float CosCurve(int nTime, float fCycle)
{
	return  (cosf((nTime * fCycle) * (D3DX_PI * 2.0f)) + 1.0f) * 0.5f;
}

//--------------------------------------------------
// �J�[�u�̒l���A���Ă���
//--------------------------------------------------
float Curve(float fCurve, float fMax, float fMin)
{
	return (fCurve * (fMax - fMin)) + fMin;
}

//---------------------------------------------------------------------------
// �X�N���[�����W�����[���h���W�ւ̃L���X�g
//---------------------------------------------------------------------------
D3DXVECTOR3 WorldCastScreen(D3DXVECTOR3 *screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize,									// �X�N���[���T�C�Y
	D3DXMATRIX* mtxView,									// �r���[�}�g���b�N�X
	D3DXMATRIX* mtxProjection)								// �v���W�F�N�V�����}�g���b�N�X
{
	// �ϐ��錾
	D3DXVECTOR3 ScreenPos;

	// �v�Z�p�}�g���b�N�X�̐錾
	D3DXMATRIX InvView, InvPrj, VP, InvViewport;

	// �e�s��̋t�s����Z�o
	D3DXMatrixInverse(&InvView, NULL, mtxView);
	D3DXMatrixInverse(&InvPrj, NULL, mtxProjection);
	D3DXMatrixIdentity(&VP);
	VP._11 = screenSize.x / 2.0f; VP._22 = -screenSize.y / 2.0f;
	VP._41 = screenSize.x / 2.0f; VP._42 = screenSize.y / 2.0f;
	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	// ���[���h���W�ւ̃L���X�g
	D3DXMATRIX mtxWorld = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord(&ScreenPos, screenPos, &mtxWorld);

	return ScreenPos;
}

//---------------------------------------------------------------------------
// �X�N���[�����W�����[���h���W�ւ̃L���X�g
//---------------------------------------------------------------------------
D3DXVECTOR3 ScreenCastWorld(D3DXVECTOR3 *screenPos,			// �X�N���[�����W
	D3DXVECTOR3 screenSize									// �X�N���[���T�C�Y
)															// �v���W�F�N�V�����}�g���b�N�X
{
	D3DXVECTOR3 Camerapos = *(CRenderer::GetCamera()->GetPos());
	D3DXVECTOR3 pos = *screenPos;
	pos.y *= -1;
	pos -= (Camerapos - D3DXVECTOR3(screenSize.x * 0.5f, screenSize.y * 0.5f, 0.0f));
	return pos;
}

//-----------------------------------------------------------------------------
//�~�̓����蔻��
//-----------------------------------------------------------------------------
bool CollisionCircle(D3DXVECTOR3 Pos1, float fRadius1, D3DXVECTOR3 Pos2, float fRadius2)
{
	//�Q���̕��̂̔��a���m�̘a
	float fDiff = fRadius1 + fRadius2;

	//X�̍���
	float fCalculationX = Pos1.x - Pos2.x;
	//Y�̍���
	float fCalculationY = Pos1.y - Pos2.y;

	//���݂̂Q�_�̋���
	float fLength = sqrtf(fCalculationX * fCalculationX + fCalculationY * fCalculationY);

	//�Q���̕��̂̔��a���m�̘a��茻�݂̂Q�_�̋��������������ǂ���
	if (fDiff >= fLength)
	{
		//��������
		return true;
	}

	//�������ĂȂ�
	return false;
}

//=========================================
// 2D�x�N�g���̊O��
// Author: Yuda Kaito
//=========================================
float Vec2Cross(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->z - v1->z * v2->x;
}

//=========================================
// 2D�x�N�g���̓���
// Author: hamada ryuuga
//=========================================
float Vec2Dot(D3DXVECTOR3* v1, D3DXVECTOR3* v2)
{
	return v1->x * v2->x + v1->z * v2->z;
}


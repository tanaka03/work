//============================
//
// ���C���ݒ�w�b�^�[
// Author:hamada ryuuga
//
//============================

#ifndef _LINE_H_
#define _LINE_H_

#include "main.h"
#include "object.h"


#define	MAX_LINE	(4096)
#define	MAX_RECIPE	(5)
#define MAX_TEX (2)
#define BallSpede (1)

//------------------------------------
// �|���S���̍\���̂��`
//------------------------------------

class CLine : public CObject
{
public:
	const int MAXTRAJECTORY = 100;
	CLine(int nPriority = PRIORITY_OBJECT);
	~CLine() override;

	HRESULT Init()override;//������
	void Uninit()override;//�j��
	void Update()override;//�X�V
	void Draw()override;//�`��

	void SetLine(D3DXVECTOR3 Maxpos, D3DXVECTOR3 pos);//�ꏊ.��].�F.�^�C�v

	static CLine* Create();
	typedef struct
	{
		D3DXVECTOR3 pos;	// ���_���W
		D3DXVECTOR3 rot;	// ��]���W
		D3DXMATRIX mtxWorld;// ���[���h�}�g���b�N�X
	} LINE;

private:
	LINE m_Line;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff = NULL;	// ���_�o�b�t�@�[�ւ̃|�C���^
	static D3DXVECTOR3 s_RotMove;
};


#endif


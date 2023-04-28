//=============================================================================
//
// TUTORIAL��ʂ̃w�b�_�[
// Author:hamada ryuuga
//
//=============================================================================
#ifndef _TUTORIAL_H_		//���̃}�N������`����ĂȂ�������
#define _TUTORIAL_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//-----------------------------------------------------------------------------
// include
//-----------------------------------------------------------------------------
#include "main.h"
#include "object.h"

//-----------------------------------------------------------------------------
// �O���錾
//-----------------------------------------------------------------------------
class CObject2d;

//-----------------------------------------------------------------------------
// �`���[�g���A���N���X
//-----------------------------------------------------------------------------
class CTutorial :public CObject
{
	const int MAXTASK = 1;
public:
	CTutorial();
	~CTutorial();
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

private:
	CObject2d *m_object2d[4];
	//CScore*pScore;

	D3DXVECTOR3 m_posOld;
	int m_NextTaskCount;//���̃^�X�N�܂ł̃J�E���g


	int m_nInterval;
	int m_nEnableTime;
	bool m_bFire;


};

#endif

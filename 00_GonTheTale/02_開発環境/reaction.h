//=============================================================================
//
// �U���ݒ�
// Author : �l�c����
//
//=============================================================================


#ifndef _REACTION_H_			// ���̃}�N����`������ĂȂ�������
#define _REACTION_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object.h"

class CArealine;
class CReaction : public CObject
{
public:
	CReaction();
	~CReaction() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	static CReaction* Create();

	void AreaSize(D3DXVECTOR3 Pos, D3DXVECTOR2 Size);
private:
	CArealine*m_area[4];
};
#endif

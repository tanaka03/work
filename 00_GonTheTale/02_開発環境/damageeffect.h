//=============================================================================
//
// effect�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _DAMAGEEFFECT_H_			// ���̃}�N����`������ĂȂ�������
#define _DAMAGEEFFECT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CDamageEffect : public C3dpolygon
{
public:

	static CDamageEffect *CDamageEffect::Create(D3DXVECTOR3 Move);

	CDamageEffect(const int list);
	~CDamageEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	void SetLife(const int &Life) { m_life = Life; };

private:
	void move();
	int m_life;
};

#endif

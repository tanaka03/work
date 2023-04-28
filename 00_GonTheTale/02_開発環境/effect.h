//=============================================================================
//
// effect�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _EFFECT_H_			// ���̃}�N����`������ĂȂ�������
#define _EFFECT_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CEffect : public C3dpolygon
{
public:


	static CEffect *CEffect::Create(D3DXVECTOR3 Move);

	CEffect(const int list);
	~CEffect() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;
	void SetLife(const int &Life) { m_life = Life; };



private:
	void move();
	int m_life;
};

#endif

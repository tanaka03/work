//=============================================================================
//
// BG�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================


#ifndef _3DPOLYGONTEMPLATE_H_			// ���̃}�N����`������ĂȂ�������
#define _3DPOLYGONTEMPLATE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CTest3d : public C3dpolygon
{
public:
	

	static CTest3d *CTest3d::Create();

	CTest3d(const int list);
	~CTest3d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;


private:
	void move();

};

#endif


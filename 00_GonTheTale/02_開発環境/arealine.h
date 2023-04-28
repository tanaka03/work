//=============================================================================
//
//�U���͈�
// Author : �l�c����
//
//=============================================================================


#ifndef _AREALINE_H_			// ���̃}�N����`������ĂȂ�������
#define _AREALINE_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "3dpolygon.h"
#include "texture.h"

class CArealine : public C3dpolygon
{
public:


	static CArealine *CArealine::Create();

	CArealine(const int list);
	~CArealine() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	const D3DXVECTOR3 *GetPos() const override;
	void SetPos(const D3DXVECTOR3 &pos) override;

	void SetDifferenceMove(D3DXVECTOR3 move);

	void SetSizeMove(D3DXVECTOR3 move);
	D3DXVECTOR3 GetSizeMove() { return m_SizeMove; }
private:
	const float Decrease = 0.5f;
	void move();

	D3DXVECTOR3 m_SizeMove;

};

#endif


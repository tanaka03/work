//=============================================================================
//
// 2D�I�u�W�F�N�g
// Author : �l�c����
//
//=============================================================================
#ifndef _OBJECT2D_H_			// ���̃}�N����`������ĂȂ�������
#define _OBJECT2D_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
#include "object.h"
#include "texture.h"

struct PositionVec4
{
	float     P0, P1, P2, P3;
	constexpr PositionVec4() : P0(0.0f), P1(0.0f), P2(0.0f), P3(0.0f) { }
	constexpr PositionVec4(float _P0, float _P1, float _P2, float _P3) : P0(_P0), P1(_P1), P2(_P2), P3(_P3) { }
};

class CObject2d : public CObject
{
private:
	//polygon�̊g��T�C�Y
	static const D3DXVECTOR3 m_Vtx[4];

public:
	static CObject2d *Create(int list = 0);

	CObject2d(int list = 0);
	~CObject2d() override;
	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;
	virtual D3DXVECTOR3 *GetPos();

	virtual void SetPos(const D3DXVECTOR3 &pos);
	virtual void SetMove(const D3DXVECTOR3 &move);

	void SetTexture(CTexture::TEXTURE texture);
	void SetTex(PositionVec4 Tex);
	CTexture::TEXTURE GetTexture(); 
	void SetColar(D3DXCOLOR Colar);

	D3DXCOLOR GetColar() { return m_col; }
	D3DXVECTOR3 GetSize() { return m_size; }

	void SetSize(D3DXVECTOR3 Size) { m_size = Size; }
	D3DXVECTOR3 &GetMove() { return m_move; }

	LPDIRECT3DVERTEXBUFFER9 &GetVtx() { return m_pVtxBuff; }
	void SetRot(D3DXVECTOR3 Rot) { m_rot = Rot; }

	void SetAnimation(const int U, const int V, const int Speed, const int Drawtimer, const bool loop);
	void AnimTexture(int nPattern, int nPatternMax);
protected:
	int  m_nTimer;
	float m_nScale;
	D3DXVECTOR3 m_size;		// �傫��
	D3DXVECTOR3 m_move;		// �ړ���
	D3DXVECTOR3 m_pos;		// �ʒu
	D3DXCOLOR m_col;		// �F
	D3DXVECTOR3 m_rot;		// ��]��
	D3DXMATRIX m_mtxWorld;	// �}�g���b�N�X

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;
	CTexture::TEXTURE m_texture;	// �e�N�X�`���̗񋓌^

	int m_CounterAnim;
	int m_PatternAnimX;
	int m_PatternAnimY;

	/* ������ */
	int m_DivisionX;
	int m_DivisionY;
	int m_DivisionMAX;

	/* �A�j���[�V�������x */
	int m_animationSpeed;
	int m_AnimationSpeedCount;

	int m_Timar;
	int m_TimaCount;

	bool m_OnAnimation;
	bool m_Loop;

};

#endif

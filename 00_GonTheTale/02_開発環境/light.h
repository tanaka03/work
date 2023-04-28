//=========================================
// 
// ���C�g�̍쐬(�w�b�_�[�t�@�C��)
// Author HAMAD
// 
//=========================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//------------------------------------
// �}�N����`
//------------------------------------
#define LIGTH_MAX	(5)

//------------------------------------
// �v���g�^�C�v�錾
//------------------------------------

class CLight
{
public:
	CLight();
	~CLight();
	void Init();		// �|���S���̏���������
	void Uninit();		// �|���S���̏I������
	void Update();		// �|���S���̍X�V����
		
	void Set(D3DLIGHTTYPE type, D3DXCOLOR col, D3DXVECTOR3 vec, int nNum);
	void AllSet();		// �|���S���̍X�V����

	D3DLIGHT9 getlight(int Data) { return m_light[Data]; }
private:

	 D3DLIGHT9 m_light[LIGTH_MAX];	//���C�g���

	
};



#endif // !_LIGHT_H_

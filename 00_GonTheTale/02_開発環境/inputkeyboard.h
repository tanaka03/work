//=============================================================================
//
// ���͏��� [inputkeyboard.h]
// Author1 : KOZUNA HIROHITO
// 
//	���Ō�̍s�����邱�Ƃ𐄏���
//
//=============================================================================

#ifndef _INPUTKEYBOARD_H_		//���̃}�N����`������Ȃ�������
#define _INPUTKEYBOARD_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v(�L�[�{�[�h)
//#pragma comment(lib,"xinput.lib") //���͏����ɕK�v�i�W���C�p�b�g�j
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g�Ɏg�p


//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include <Windows.h>
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")

//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputKeyboard
{
private:
	static const int NUM_KEY_MAX = 256;	//�L�[�̍ő吔�i�L�[�{�[�h�j
public:
	CInputKeyboard();
	~CInputKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//���͏����S���̏�����
	void Uninit(void);									//���͏����S���̏I������
	void Update(void);									//���͏����S���̍X�V����

	bool GetKeyboardPress(int nKey);			//�L�[�{�[�h�v���X����
	bool GetKeyboardTrigger(int nKey);			//�L�[�{�[�h�g���K�[����
	bool GetKeyboardAllPress(void);				//�L�[�{�[�h�S�L�[�v���X����
	bool GetKeyboardAllTrigger(void);			//�L�[�{�[�h�S�L�[�g���K�[����

private:
	LPDIRECTINPUT8 m_pInput;							//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;				//���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
	BYTE m_aKeyState[NUM_KEY_MAX];						//�L�[�{�[�h�̃v���X���
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX];				//�L�[�{�[�h�̃g���K�[���

};
#endif
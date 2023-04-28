//=============================================================================
//
// ���͏��� [inputkeyboard.h]
// Author1 : KOZUNA HIROHITO
// 
//	���Ō�̍s�����邱�Ƃ𐄏���
//
//=============================================================================

#ifndef _INPUTCONTROLLER_H_		//���̃}�N����`������Ȃ�������
#define _INPUTCONTROLLER_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//���C�u�����[�t�@�C���̃����N
//----------------------------------------------------------------------------
#pragma comment(lib,"dinput8.lib")//���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"xinput.lib") //���͏����ɕK�v�i�W���C�p�b�g�j
#pragma comment(lib,"dxguid.lib")		//DirectX�R���|�[�l���g�Ɏg�p

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include <Windows.h>
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#define	 DIRECTINPUT_VERSION (0x0800)	// �r���h���̌x���΍��p�}�N��(���̈ʒu���瓮�����Ȃ�)
#include <Xinput.h>						// �W���C�p�b�g����
#include <dinput.h>						// ���͏����ɕK�v
//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInputController
{
private:
	static const int NUM_KEY_MAX = 256;	//�L�[�̍ő吔�i�L�[�{�[�h�j
	static const int PLAYER_MAX = 4;		//�v���C���[�̍ő�l��
public:

	//�L�[���(�W���C�p�b�h)
	typedef enum
	{
		JOYKEY_UP = 0,				//�\���{�^����
		JOYKEY_DOWN,				//�\���{�^����
		JOYKEY_LEFT,				//�\���{�^����
		JOYKEY_RIGHT,				//�\���{�^���E
		JOYKEY_START,				//�X�^�[�g�{�^��
		JOYKEY_BACK,				//�o�b�N�{�^��
		JOYKEY_LEFT_THUMB,			//���X�e�B�b�N������
		JOYKEY_RIGHT_THUMB,			//�E�X�e�B�b�N������
		JOYKEY_LEFT_SHOULDER,		//L�P�{�^��
		JOYKEY_RIGHT_SHOULDER,		//R�P�{�^��
		JOYKEY_LEFT_TRIGGER,		//L�Q�g���K�[
		JOYKEY_RIGHT_TRIGGER,		//R�Q�g���K�[
		JOYKEY_A,					//A�{�^��
		JOYKEY_B,					//B�{�^��
		JOYKEY_X,					//X�{�^��
		JOYKEY_Y,					//Y�{�^��
		JOYKEY_LEFT_STICK,			//���X�e�B�b�N
		JOYKEY_RIGHT_STICK,			//�E�X�e�B�b�N
		JOYKEY_MAX
	}JOYKEY;

	CInputController();
	~CInputController();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//���͏����S���̏�����
	void Uninit(void);									//���͏����S���̏I������
	void Update(void);									//���͏����S���̍X�V����

	bool GetJoypadPress(JOYKEY Key, int nPlayer);					//�W���C�p�b�h�v���X����
	bool GetJoypadTrigger(JOYKEY Key, int nPlayer);					//�W���C�p�b�h�g���K�[����
	D3DXVECTOR3 GetJoypadStick(JOYKEY Key, int nPlayer);			//�W���C�p�b�h�X�e�B�b�N����
	int GetJoypadTriggerPedal(JOYKEY Key, int nPlayer);				//�W���C�p�b�h�g���K�[�y�_������
	void JoypadVibration(int nTime, WORD nStrength, int nPlayer);	//�W���C�p�b�h�U������

private:

	LPDIRECTINPUT8 m_pInput;							//DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevJoypad;				//���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^
										//�W���C�p�b�h
	XINPUT_STATE m_JoyKeyState[PLAYER_MAX];				//�W���C�p�b�g�̃v���X���
	XINPUT_STATE m_JoyKeyStateTrigger[PLAYER_MAX];		//�W���C�p�b�g�̃g���K�[���
	D3DXVECTOR3 m_JoyStickPos[PLAYER_MAX];				//�W���C�X�e�B�b�N�̌X��
	XINPUT_VIBRATION m_JoyMoter[PLAYER_MAX];			//�W���C�p�b�h�̃��[�^�[
	int m_nTime[PLAYER_MAX];							//�U����������
	WORD m_nStrength[PLAYER_MAX];						//�U���̋��� (0 - 65535)

};
#endif
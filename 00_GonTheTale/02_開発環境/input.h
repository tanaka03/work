//=============================================================================
//
// ���͏��� [input.h]
// Author1 : KOZUNA HIROHITO
// 
//	���Ō�̍s�����邱�Ƃ𐄏���
//
//=============================================================================

#ifndef _INPUT_H_		//���̃}�N����`������Ȃ�������
#define _INPUT_H_		//2�d�C���N���[�h�h�~�̃}�N����`

//----------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "inputkeyboard.h"
#include "inputcontroller.h"
//----------------------------------------------------------------------------
//�N���X��`
//----------------------------------------------------------------------------
class CInput
{
public:
	enum STAN_DART_INPUT_KEY
	{
		KEY_UP = 0,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_DECISION,
		KEY_SHOT,
		KEY_DEBUG,
		KEY_F2,
		KEY_RELOAD,
		KEY_PAUSE,
		KEY_DELETE,
		KEY_MESHUP,
		KEY_MESHDOWN,
		KEY_INVENTORY,
		KEY_DROP,
		KEY_HAVE,
		KEY_SHIFT
	};

	CInput();
	~CInput();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//���͏����S���̏�����
	void Uninit();									//���͏����S���̏I������
	void Update();									//���͏����S���̍X�V����
	static CInput *Create();
	static CInput *GetKey() { return m_Input; }
	bool Press(STAN_DART_INPUT_KEY key);
	bool Trigger(STAN_DART_INPUT_KEY key);

private:
	CInputKeyboard *m_pKeyboard;
	CInputController *m_pKeyJoypad;
	static CInput *m_Input;
};

#endif


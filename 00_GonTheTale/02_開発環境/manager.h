//=============================================================================
//
// �����_���[
// Author : �l�c����
//
//=============================================================================
#ifndef _MANEAGER_H_			// ���̃}�N����`������ĂȂ�������
#define _MANEAGER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#include "renderer.h"
 
class CRenderer;
class CInput;
class CTexture;
class CObject;
class CResult;
class CGame;
class CFade;
class CSound;
class CFont;

HWND GetWnd(void);

class CManager
{
public:
	//���(���[�h)�̎��
	enum LEVEL
	{
		LEVEL_EASY = 0,			//�Q�[�����	
		LEVEL_NORMAL,
		LEVEL_HARD,		//�����L���O���
		LEVEL_END,
		LEVEL_MAX
	};

	static const D3DXVECTOR3 centerPos;

	//���(���[�h)�̎��
	enum MODE
	{
		MODE_TITLE = 0,		//�^�C�g�����
		MODE_GAME,			//�Q�[�����
		MODE_RESULT,		//���U���g���
		MODE_FADE,			//�t�F�[�h���
		MODE_RANKING,		//�����L���O���
		MODE_GAMEOVER,
		MODE_TUTORIAL,
		MODE_NAMESET,
		MODE_MAX
	};

public: // �ÓI�����o�[�ϐ�
	static CManager* m_manager;

public: // �ÓI�֐�
	static CManager* GetInstance();
	
private: // �V���O���g��
	CManager();

public:	// �����o�[�֐�
	~CManager();

	HRESULT Init(HWND hWnd, bool bWindow, HINSTANCE hInstance);
	void Uninit();
	void Update();
	void Draw();

	CRenderer *GetRenderer();
	CTexture* GetTexture();	// �e�N�X�`���̏��̎擾
	CFade* GetFade();	// 
	MODE* GetMode();	//
	void SetMode(CManager::MODE mode);
	CSound * GetSound();


	CFont * GetFont();


	static LEVEL* GameLevel() { return m_Level; }
	static void SetLevel(LEVEL* Level) { m_Level = Level; }
	static LEVEL* m_Level;

private:
	CTexture *m_pTexture;
	CRenderer * m_cRenderer;
	CFade* m_Fade;
	CObject*m_Game;
	CSound*m_Sound;
	MODE m_mode;
	CInput *m_Input;

	CFont *m_pFont;
};



#endif

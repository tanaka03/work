//**************************************************
//
// sound.h
// Author  : katsuki mizuki
//
//**************************************************
#ifndef _SOUND_H_	//���̃}�N����`������ĂȂ�������
#define _SOUND_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include <xaudio2.h>

//==================================================
// ��`
//==================================================
class CSound
{
	/* ����`�� */
public:
	enum ELabel
	{
		LABEL_NONE = -1,
		LABEL_BGM_TITLE = 0,	// �^�C�g��
		LABEL_BGM_GAME,			// game
		LABEL_BGM_RESULT,		// ���U���g
		LABEL_BGM_TUTORIAL,
		LABEL_BGM_RANKING,
		LABEL_SE_OFF,	//�L�����Z��
		LABEL_SE_ON,	//���艹
		LABEL_SE_BOM,	//�N���e�B�J��
		LABEL_SE_BOM1,  //�q�b�g
		LABEL_MAX,
	};

	struct SParam
	{
		char *pFileName;	// �t�@�C����
		int loop;			// ���[�v
	};

	static const SParam PARAM[];	// �p�����[�^�̏��

	/* �������o�֐��� */
public:
	CSound();	// �f�t�H���g�R���X�g���N�^
	~CSound();	// �f�X�g���N�^

public:
	HRESULT Init(HWND hWnd);
	void Uninit();
	HRESULT Play(ELabel sound);
	void Stop(ELabel label);
	void Stop();

private:
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// �`�����N�̃`�F�b�N
	HRESULT LoadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// �`�����N�f�[�^�̓ǂݍ���

	/* �������o�ϐ��� */
private: 
	IXAudio2* m_pXAudio2;							// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice;		// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_pSourceVoice[LABEL_MAX];	// �\�[�X�{�C�X
	BYTE* m_pDataAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_sizeAudio[LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y
};

#endif // !_SOUND_H_

//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "sound.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const CSound::SParam CSound::PARAM[] =
{// �e���f�ނ̃p�����[�^
	{ "data/BGM/Chattotata.wav", -1},		// �^�C�g���P
	{ "data/BGM/Hallowe'en Dance.wav", -1 },		// game�Q
	{ "data/BGM/yukiguni.wav", -1 },				// ���U���g�T
	{ "data/BGM/rizaruto.wav", -1 },			// �`���[�g���A���U
	{ "data/BGM/0930_BGM/rezalt.wav", -1 },			// �����L���O�V
	{ "data/SE/move.wav", 0 },		//�L�����Z��
	{ "data/SE/select.wav", 0 },		//���艹
	{ "data/SE/coin07.wav", 0 },		//�N���e�B�J��
	{ "data/SE/poka01.wav", 0 }		//�q�b�g
	
}; 

static_assert(sizeof(CSound::PARAM) / sizeof(CSound::PARAM[0]) == CSound::LABEL_MAX, "aho");

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CSound::CSound() :
	m_pMasteringVoice(nullptr),
	m_pXAudio2(nullptr)
{
	memset(m_pDataAudio, 0, sizeof(m_pDataAudio));
	memset(m_pSourceVoice, 0, sizeof(m_pSourceVoice));
	memset(m_sizeAudio, 0, sizeof(m_sizeAudio));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CSound::~CSound()
{
	assert(m_pMasteringVoice == nullptr);
	assert(m_pXAudio2 == nullptr);

	for (int i = 0; i < LABEL_MAX; i++)
	{
		assert(m_pDataAudio[i] == nullptr);
		assert(m_pSourceVoice[i] == nullptr);
	}
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	// COM���C�u�����̏�����
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	if (FAILED(XAudio2Create(&m_pXAudio2, 0)))
	{// XAudio2�I�u�W�F�N�g�̍쐬
		MessageBox(hWnd, "XAudio2�I�u�W�F�N�g�̍쐬�Ɏ��s�I", "�x���I", MB_ICONWARNING);

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	if (FAILED(m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice)))
	{// �}�X�^�[�{�C�X�̐���
		MessageBox(hWnd, "�}�X�^�[�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);

		if (m_pXAudio2 != nullptr)
		{// null�`�F�b�N
			// XAudio2�I�u�W�F�N�g�̊J��
			m_pXAudio2->Release();
			m_pXAudio2 = nullptr;
		}

		// COM���C�u�����̏I������
		CoUninitialize();

		return E_FAIL;
	}

	HANDLE hFile = INVALID_HANDLE_VALUE;
	DWORD dwChunkSize = 0;
	DWORD dwChunkPosition = 0;
	DWORD dwFiletype = 0;
	WAVEFORMATEXTENSIBLE wfx;
	XAUDIO2_BUFFER buffer;

	// �T�E���h�f�[�^�̏�����
	for (int i = 0; i < LABEL_MAX; i++)
	{
		hFile = INVALID_HANDLE_VALUE;
		dwChunkSize = 0;
		dwChunkPosition = 0;
		dwFiletype = 0;

		// �o�b�t�@�̃N���A
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		/* ���T�E���h�f�[�^�t�@�C���̐����� */

		hFile = CreateFile(PARAM[i].pFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// �t�@�C���|�C���^��擪�Ɉړ�
			MessageBox(hWnd, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		/* ��WAVE�t�@�C���̃`�F�b�N�� */

		if (FAILED(CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		if (FAILED(LoadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition)))
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		/* ���t�H�[�}�b�g�`�F�b�N�� */

		if (FAILED(CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition)))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		if (FAILED(LoadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition)))
		{
			MessageBox(hWnd, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		/* ���I�[�f�B�I�f�[�^�ǂݍ��݁� */

		if (FAILED(CheckChunk(hFile, 'atad', &m_sizeAudio[i], &dwChunkPosition)))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		m_pDataAudio[i] = (BYTE*)malloc(m_sizeAudio[i]);

		//m_pDataAudio[i] = new BYTE[m_sizeAudio[i]];

		if (FAILED(LoadChunkData(hFile, m_pDataAudio[i], m_sizeAudio[i], dwChunkPosition)))
		{
			MessageBox(hWnd, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		/* ���\�[�X�{�C�X�̐����� */

		if (FAILED(m_pXAudio2->CreateSourceVoice(&m_pSourceVoice[i], &(wfx.Format))))
		{
			MessageBox(hWnd, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
			return S_FALSE;
		}

		// �o�b�t�@�̒l�ݒ�
		buffer.AudioBytes = m_sizeAudio[i];
		buffer.pAudioData = m_pDataAudio[i];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = PARAM[i].loop;

		// �I�[�f�B�I�o�b�t�@�̓o�^
		m_pSourceVoice[i]->SubmitSourceBuffer(&buffer);

		// �t�@�C�����N���[�Y
		CloseHandle(hFile);
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSound::Uninit()
{
	// �ꎞ��~
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (m_pSourceVoice[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		// �ꎞ��~
		m_pSourceVoice[i]->Stop(0);

		// �\�[�X�{�C�X�̔j��
		m_pSourceVoice[i]->DestroyVoice();
		m_pSourceVoice[i] = nullptr;

		// �I�[�f�B�I�f�[�^�̊J��
		free(m_pDataAudio[i]);
		//delete m_pDataAudio[i];
		m_pDataAudio[i] = nullptr;
	}

	// �}�X�^�[�{�C�X�̔j��
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = nullptr;

	if (m_pXAudio2 != nullptr)
	{// null�`�F�b�N
		// XAudio2�I�u�W�F�N�g�̊J��
		m_pXAudio2->Release();
		m_pXAudio2 = nullptr;
	}

	// COM���C�u�����̏I������
	CoUninitialize();
}

//=============================================================================
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
//=============================================================================
HRESULT CSound::Play(CSound::ELabel label)
{
	XAUDIO2_BUFFER buffer;

	// �o�b�t�@�̒l�ݒ�
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_sizeAudio[label];
	buffer.pAudioData = m_pDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = PARAM[label].loop;

	// �Z�O�����g��~(���x���w��)
	Stop(label);

	// �I�[�f�B�I�o�b�t�@�̓o�^
	m_pSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// �Đ�
	m_pSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// �Z�O�����g��~(���x���w��)
//=============================================================================
void CSound::Stop(CSound::ELabel label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// ��Ԏ擾
	m_pSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// �Đ���
		// �ꎞ��~
		m_pSourceVoice[label]->Stop(0);

		// �I�[�f�B�I�o�b�t�@�̍폜
		m_pSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// �Z�O�����g��~(�S��)
//=============================================================================
void CSound::Stop()
{
	// �ꎞ��~
	for (int i = 0; i < LABEL_MAX; i++)
	{
		if (m_pSourceVoice[i] == nullptr)
		{
			continue;
		}

		// �ꎞ��~
		m_pSourceVoice[i]->Stop(0);
	}
}

//=============================================================================
// �`�����N�̃`�F�b�N
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead = 0;
	DWORD dwChunkType = 0;
	DWORD dwChunkDataSize = 0;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType = 0;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^��擪�Ɉړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (!ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL))
		{// �`�����N�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (!ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL))
		{// �`�����N�f�[�^�̓ǂݍ���
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;

			if (!ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL))
			{// �t�@�C���^�C�v�̓ǂݍ���
				hr = HRESULT_FROM_WIN32(GetLastError());
			}

			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
				return HRESULT_FROM_WIN32(GetLastError());
			}
			break;
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// �`�����N�f�[�^�̓ǂݍ���
//=============================================================================
HRESULT CSound::LoadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// �t�@�C���|�C���^���w��ʒu�܂ňړ�
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (!ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL))
	{// �f�[�^�̓ǂݍ���
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

//=============================================================================
//
// ���C��
// Author : �l�c����
//
//=============================================================================
#ifndef _MAIN_H_			// ���̃}�N����`������ĂȂ�������
#define _MAIN_H_			// ��d�C���N���[�h�h�~�̃}�N����`

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <assert.h>

#ifdef _DEBUG
#define CHECK_MEM_LEAK
#endif // _DEBUG:

//���i�g�p�֎~
#ifdef CHECK_MEM_LEAK
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif // CHECK_MEM_LEAK

#endif

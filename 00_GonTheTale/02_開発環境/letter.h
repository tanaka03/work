//============================
//
// ����ݒ�
// Author:hamada ryuuga
//
//============================
#ifndef _LETTER_H_			// ���̃}�N����`������ĂȂ�������
#define _LETTER_H_			// ��d�C���N���[�h�h�~�̃}�N����`

//=====================================
// �C���N���[�h
//=====================================
#include <string>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <locale.h>

#include <iostream>
#include <fstream>
#include "nlohmann/json.hpp"

//=====================================
// �v���g�^�C�v�錾
//=====================================
// ����֐�
std::string WStringToString(std::wstring oWString);
std::wstring StringToWString(std::string oString);
std::string UTF8toSjis(std::string srcUTF8);
std::string SjistoUTF8(std::string srcSjis);

#endif
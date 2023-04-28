//=============================================================================
//
// プリコンパイル.h
// Author : 浜田琉雅
//
//=============================================================================


#ifndef _PRECOMPILE_H_			// このマクロ定義がされてなかったら
#define _PRECOMPILE_H_			// 二重インクルード防止のマクロ定義

//ここに書く
#include <Windows.h>
#include <tchar.h> // _T
#include <d3d9.h>

#include <assert.h>
#include <string>
#include <windows.h>
#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <sstream>

//ライブラリ
//#include "imgui.h"
//#include "imgui_impl_dx9.h"
//#include "imgui_impl_win32.h"
//#define IMGUI_DEFINE_MATH_OPERATORS
//#include <imgui_internal.h>

#include <nlohmann/json.hpp>

//ライブラリinput
#define	 DIRECTINPUT_VERSION (0x0800)						//ビルド時の警告対策用マクロ(この位置から動かさない)
#include <Xinput.h>						// ジョイパット処理
#include <dinput.h>						// 入力処理に必要

#endif

//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************
#ifndef _PLAYFAB_H_
#define _PLAYFAB_H_


#include "playfab/PlayFabError.h"
#include "playfab/PlayFabClientDataModels.h"
#include "playfab/PlayFabClientApi.h"
#include "playfab/PlayFabSettings.h"
#include "playfab/PlayFabApiSettings.h"
#include "playfab/PlayFabClientDataModels.h"
#include "playfab/PlayFabClientApi.h"
#include "playfab/PlayFabSettings.h"
#include "playfab/PlayFabApiSettings.h"
#include <windows.h>
#include <functional>
#include <iphlpapi.h>
#include <string>

#include <thread>
#pragma comment(lib, "iphlpapi.lib")

#include "score.h"
#include <string>       // ヘッダファイルインクルード

using namespace PlayFab;
using namespace ClientModels;

//=============================================================================
//プロトタイプ宣言
//=============================================================================

class CPlayfab : public CObject
{

public:
	static LoginWithCustomIDRequest IdSet(char*Id);
	static void APIUp();

	static std::string GetMACAddr();
	static void GetMasterData(std::function<void()> func);
	static std::string GetMasterValue(const char* key){ return m_Data.at(key); }

	static void GetScore(std::function<void(const ClientModels::GetLeaderboardResult& resul)> func);
	static void SetScore(const std::string playName,const int score, std::function<void(void)> func);
	static std::map<std::string, std::string> m_Data;
	
	
	static std::string m_PlayName;

	

};
#endif
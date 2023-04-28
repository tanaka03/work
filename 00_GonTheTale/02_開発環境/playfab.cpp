//**************************************************
//
// 制作 ( ランキング )
// Author  : hamada ryuuga
//
//**************************************************

#include "playfab.h"
#include "ranking.h"
#include "manager.h"

//=============================================================================
//プロトタイプ宣言
//=============================================================================


std::string CPlayfab::m_PlayName;
std::map<std::string, std::string>CPlayfab::m_Data;


void OnLoginFail(const PlayFabError& error, void*)
{
	printf("Something went wrong with your first API call.\n");
	printf("Here's some debug information:\n");
	printf(error.GenerateErrorReport().c_str());
	printf("\n");

}

//========================
//ログイン
//========================

LoginWithCustomIDRequest CPlayfab::IdSet(char*Id)
{
	PlayFabSettings::staticSettings->titleId = (Id);

	LoginWithCustomIDRequest request;
	request.CreateAccount = true;
	if (m_PlayName =="")
	{
		request.CustomId = GetMACAddr();
	}
	else
	{
		request.CustomId = m_PlayName;
	}

	return request;
}


//========================
//オンライン更新
//========================
void CPlayfab::APIUp()
{
	PlayFabClientAPI::Update();
}

//========================
// 任意のネットワークアダプタのMACアドレスを取得
//========================
std::string CPlayfab::GetMACAddr()
{
	PIP_ADAPTER_INFO adapterInfo;
	DWORD dwBufLen = sizeof(IP_ADAPTER_INFO);

	adapterInfo = (IP_ADAPTER_INFO *)malloc(sizeof(IP_ADAPTER_INFO));
	if (adapterInfo == NULL)
	{
		return "";
	}

	if (GetAdaptersInfo(adapterInfo, &dwBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(adapterInfo);
		adapterInfo = (IP_ADAPTER_INFO *)malloc(dwBufLen);
		if (adapterInfo == NULL) {
			return "";
		}
	}

	char pOutMacAddr[64];
	if (GetAdaptersInfo(adapterInfo, &dwBufLen) == NO_ERROR)
	{
		PIP_ADAPTER_INFO pAdapterInfo = adapterInfo;
		sprintf(pOutMacAddr, "%02X:%02X:%02X:%02X:%02X:%02X",
			pAdapterInfo->Address[0], pAdapterInfo->Address[1],
			pAdapterInfo->Address[2], pAdapterInfo->Address[3],
			pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

		pAdapterInfo = pAdapterInfo->Next;
	}
	else
	{
		// macアドレスが見つからない場合は固定文字列
		sprintf(pOutMacAddr, "user");
	}
	free(adapterInfo);
	return std::string(pOutMacAddr);
}

//========================
// GetScore
//========================
void CPlayfab::GetScore(std::function<void(const ClientModels::GetLeaderboardResult&)> func)
{
	LoginWithCustomIDRequest request = IdSet("323A0");
	HWND Wnd = GetWnd();
	PlayFabClientAPI::LoginWithCustomID(request, [func](PlayFab::ClientModels::LoginResult result, void* customData) {
		
		GetLeaderboardRequest req;

		req.StatisticName = "unde";//ゲームマネージャーでランキング名のやつ
		
		PlayFabClientAPI::GetLeaderboard(req,
			[func](const ClientModels::GetLeaderboardResult& resul, void*)
		{
			func(resul);
		});
	}, [Wnd](const PlayFabError& error, void*customData)
	{//失敗時
		MessageBox(Wnd, "ネット接続失敗", "ネット接続失敗", MB_OK);
	});

}
//========================
// GetMasterData
//========================
void CPlayfab::GetMasterData(std::function<void()> func)
{

	LoginWithCustomIDRequest request = IdSet("323A0");

	PlayFabClientAPI::LoginWithCustomID(request, [func](PlayFab::ClientModels::LoginResult result, void* customData) {

		GetTitleDataRequest req;

		PlayFabClientAPI::GetTitleData(req,
			[func](const ClientModels::GetTitleDataResult& result, void*)
		{//成功時
			func();
			m_Data = result.Data;
		});
	});
	
}

//========================
// SetScore
//========================
void CPlayfab::SetScore(const std::string playName, const int score ,std::function<void(void)> func)
{
	m_PlayName = playName;
	HWND Wnd = GetWnd();
	LoginWithCustomIDRequest request = IdSet("323A0");

	PlayFabClientAPI::LoginWithCustomID(request, [playName, score, func, Wnd](PlayFab::ClientModels::LoginResult result, void* customData) {

		UpdateUserTitleDisplayNameRequest Namereq;
		
		Namereq.DisplayName = playName;

		PlayFabClientAPI::UpdateUserTitleDisplayName(Namereq, [](const UpdateUserTitleDisplayNameResult result, void*)
		{
			//成功

		});
		
		UpdatePlayerStatisticsRequest Scorereq;
		StatisticUpdate statistic;
		statistic.StatisticName = "unde";//ゲームマネージャーでランキング名のやつ

		statistic.Value = score;//小さい順にするためにの-１かける

		Scorereq.Statistics.push_back(statistic);

		PlayFabClientAPI::UpdatePlayerStatistics(Scorereq,
			[func](const ClientModels::UpdatePlayerStatisticsResult&, void*)
		{//成功時

			func();

		},[func, Wnd](const PlayFabError& error, void*customData)
		{//失敗時
			MessageBox(Wnd, "ネット接続失敗", "ネット接続失敗", MB_OK);
			func();

		});

		
	}, OnLoginFail);


}

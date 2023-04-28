//**************************************************
//
// ���� ( �����L���O )
// Author  : hamada ryuuga
//
//**************************************************

#include "playfab.h"
#include "ranking.h"
#include "manager.h"

//=============================================================================
//�v���g�^�C�v�錾
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
//���O�C��
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
//�I�����C���X�V
//========================
void CPlayfab::APIUp()
{
	PlayFabClientAPI::Update();
}

//========================
// �C�ӂ̃l�b�g���[�N�A�_�v�^��MAC�A�h���X���擾
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
		// mac�A�h���X��������Ȃ��ꍇ�͌Œ蕶����
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

		req.StatisticName = "unde";//�Q�[���}�l�[�W���[�Ń����L���O���̂��
		
		PlayFabClientAPI::GetLeaderboard(req,
			[func](const ClientModels::GetLeaderboardResult& resul, void*)
		{
			func(resul);
		});
	}, [Wnd](const PlayFabError& error, void*customData)
	{//���s��
		MessageBox(Wnd, "�l�b�g�ڑ����s", "�l�b�g�ڑ����s", MB_OK);
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
		{//������
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
			//����

		});
		
		UpdatePlayerStatisticsRequest Scorereq;
		StatisticUpdate statistic;
		statistic.StatisticName = "unde";//�Q�[���}�l�[�W���[�Ń����L���O���̂��

		statistic.Value = score;//���������ɂ��邽�߂ɂ�-�P������

		Scorereq.Statistics.push_back(statistic);

		PlayFabClientAPI::UpdatePlayerStatistics(Scorereq,
			[func](const ClientModels::UpdatePlayerStatisticsResult&, void*)
		{//������

			func();

		},[func, Wnd](const PlayFabError& error, void*customData)
		{//���s��
			MessageBox(Wnd, "�l�b�g�ڑ����s", "�l�b�g�ڑ����s", MB_OK);
			func();

		});

		
	}, OnLoginFail);


}

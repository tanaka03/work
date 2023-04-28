//**************************************************
//
// ���� ( �����L���O )
// Author  : hamada ryuuga
//
//**************************************************
#ifndef _RANKING_H_
#define _RANKING_H_

#include "score.h"
#include <string>       // �w�b�_�t�@�C���C���N���[�h
//=============================================================================
//�}�N����`
//=============================================================================
#define MAX_RANK	(6)	//�����N��
#define MAX_RANKSCORE	(8)	//����

//=============================================================================
//�v���g�^�C�v�錾
//=============================================================================

class CScore;
class CObject2d;
class CName;

class CRanking : public CObject
{
public:
	CRanking();
	~CRanking();
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	static void SetScore(int nScore);
	static void SetPlayNeme(const std::string PlayName) { m_PlayName = PlayName; };
	static void SetName(int number, std::string Name) { m_name[number] = Name; };

	static void GetScore();

	static int GetMyScore() { return m_score; };


private:

	static int m_score;
	static CScore *m_Ranking[MAX_RANK];
	static std::string m_PlayName;
	static	std::string m_name[5];
	
	CObject2d *m_object2d[4];

	CName*m_ListName[3];
	CName*m_PlayNameSet[10];

	D3DXVECTOR3 m_NemePos;

	int m_NowPlay;

	bool m_OnrankingSet;
	bool m_RankingSet;
};



#endif

//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
//particle.h
// Author : Tanaka Kouta
// Author : Hamada Ryuuga
//＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝
#ifndef _PARTICLE_H_		//このマクロが定義されてなかったら
#define _PARTICLE_H_		//2重インクルード防止のマクロ定義

#pragma push_macro("new")
#undef new
#include <d3dx9.h>
#pragma pop_macro("new")
#include "object2d.h"

//-------------------------------------------------
// パーティクルクラス
// Author : Tanaka Kouta
// Author : Yuda Kaito
// Author ; hamada 
// 概要 : パーティクルの処理を担当するクラス
//-------------------------------------------------
class CParticle : public CObject2d
{
public:	// 定数
	static const int maxNumber = 21000;
	static const int numType = 10;
public:	// 静的変数
public:	// 列挙型
		//エフェクトの種別
	enum PARTICLETYPE
	{
		PARTICLETYPE_NONE = 0,
		PARTICLETYPE_NORMAL,
		PARTICLETYPE_PLAYER,
		PARTICLETYPE_MAX
	};
public: // 構造体

	//-------------------------------------------------
	// テクスチャ情報
	// Author : 
	// 概要 : テクスチャに関するデータ構造体
	//-------------------------------------------------
	struct ParticleTex
	{
		D3DXVECTOR3 pos;
		D3DXCOLOR col;
		float size;
	};

	//-------------------------------------------------
	// エフェクトのカラー構造体
	// Author : 唐�ｱ結斗
	// Author ; hamada 
	// 概要 : エフェクトの色関係の構造体
	//-------------------------------------------------
	struct Color	// ※新規追加構造体(ファイルに追加後消してください)
	{
		D3DXCOLOR colBigin;			// 始まりの色
		D3DXCOLOR colRandamMax;		// ランダムな色の範囲(最大)
		D3DXCOLOR colRandamMin;		// ランダムな色の範囲(最小)
		D3DXCOLOR colTransition;	// 色の遷移量
		D3DXCOLOR destCol;			// 目的の色
		int nEndTime;				// 遷移完了までの時間			※新規追加変数(ファイルに追加後消してください)
		int nCntTransitionTime;		// 遷移カウント					※新規追加変数(ファイルに追加後消してください)
		bool bColTransition;		// カラー遷移					※新規追加変数(ファイルに追加後消してください)
		bool bColRandom;			// ランダムカラー				※新規追加変数(ファイルに追加後消してください)
		bool bRandomTransitionTime;	// 遷移時間の乱数				※新規追加変数(ファイルに追加後消してください)
	};

	//-------------------------------------------------
	// エフェクトのαブレンドの種別の列挙型
	// Author : 唐�ｱ結斗
	// Author ; hamada
	// 概要 : 乗算、加算、減算
	//-------------------------------------------------
	enum ALPHABLENDTYPE
	{
		TYPE_ADD = 0,		// 加算
		TYPE_SUB,			// 減算
		TYPE_NONE,			// 乗算
		MAX_TYPE,			// 種別の最大数
	};

	//-------------------------------------------------
	//エフェクトの構造体の定義
	// Author : Tanaka Kouta
	// Author : Yuda Kaito
	// Author : Hamada Ryuga
	// Author : 唐�ｱ結斗
	//-------------------------------------------------
	struct Info
	{
		D3DXVECTOR3 maxPopPos;		// 発生位置(最大)			※新規追加変数(ファイルに追加後消してください)
		D3DXVECTOR3 minPopPos;		// 発生位置(最小)			※新規追加変数(ファイルに追加後消してください)
		D3DXVECTOR3 move;			// 移動量
		D3DXVECTOR3 moveTransition;	// 移動量の推移量
		D3DXVECTOR3 rot;			// 向き
		PARTICLETYPE type;			// エフェクトの種類
		Color color;				// カラー					※新規追加変数(ファイルに追加後消してください)
		ALPHABLENDTYPE alphaBlend;	// αブレンディングの種別
		float fWidth;				// 幅
		float fHeight;				// 高さ
		float fAngle;				// 角度
		float fAttenuation;			// 減衰値
		float fRadius;				// 半径
		float fWeight;				// 重さ
		float fWeightTransition;	// 重さの推移量
		float fScale;				// 全体的な大きさ
		int nLife;					// 寿命
		int nMaxLife;				// 最大寿命
		int nMoveTime;				
		int nIdxTex;				// テクスチャの番号
		bool bUseWeight;			// 重さを使用するかどうか
		bool bBackrot;				// 逆回転させるかどうか
		bool bTexturerot;			// テクスチャ回転させるかどうか
	};

public:
	CParticle();
	~CParticle();

	HRESULT Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	static CParticle* Create(const Info& inParticle, const D3DXVECTOR3& inPos);
	void LoadTex();
	DWORD FloattoDword(float fVal);

private:	// メンバー変数
	Info m_data;
	int m_idx;
};
#endif

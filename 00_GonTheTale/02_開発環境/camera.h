//============================
//
// カメラ設定ヘッター
// Author:hamada ryuuga
//
//============================

#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "renderer.h"


class CCamera
{
private: // プライベート定数
	static const D3DXVECTOR3 INIT_POSV;		// 位置の初期位置
	static const float MOVE_ATTENUATION;	// 減衰係数
	static const float FIELD_OF_VIEW;		// 視野角
	static const float NEAR_VALUE;			// ニア
	static const float FUR_VALUE;			// ファー
	static const float MOVE_ANGLE;	// 減衰係数

public:

	CCamera();
	~CCamera();

	void Init(void);	// 初期化
	void Uninit(void);	// 破棄
	void Update(void);	// 更新
	void Set(int Type);	// 画面設定

	void GameInit();
	D3DXMATRIX *GetMtxProje() { return &m_mtxProje; }
	D3DXMATRIX *GetMtxView() { return &m_mtxView; }
	D3DXVECTOR3 *GetPos() { return &m_posV; }
	D3DXVECTOR3 *GetPosR() { return &m_posR; }
	D3DXVECTOR3 *GetRot() { return &m_rot; }
	
	 void SetPos(D3DXVECTOR3 IsposV) { m_posV = IsposV; }
	 void SetPosR(D3DXVECTOR3 IsposR) { m_posR = IsposR; }
	void Setisfree() { m_isFree = !m_isFree; }
	bool Getisfree() {return m_isFree; }
	//	Animationの読み込み
	void LandAnimation(std::string);

	//	からのAnimationを追加
	void AddAnimation();

	//	Animationのさいずの取得
	int GetAnimationSize();

	void PlayAnimation(int Animation, bool Isloop);
	void PlayAnimation(std::string AnimationName, bool Isloop, std::function<void()> func = nullptr);

	void ShakeCamera(int IsFrameCount, float IsShakePow);

	void SetEnd(bool IsEnd) { m_bossEnd = IsEnd; }
private:
	int m_type;
	int m_nouAnimation;
	int m_isFrameCount;
	float m_speed = 1.0f;
	float m_rotSpeed = 0.05f;
	float m_rotSpeed2 = D3DX_PI / 2;
	float m_fDistance;					// 距離
	float m_fDistanceY;
	float m_isShakePow;

	D3DXVECTOR3 m_posV;				// 位置
	D3DXVECTOR3 m_posR;				// 注視点
	D3DXVECTOR3 m_vecU;				// ベクトル
	D3DXVECTOR3 m_directionV;			// 回転の向き位置
	D3DXVECTOR3 m_directionR;			// 回転の向き注視点
	D3DXVECTOR3 m_rot;					// 位置回転
	
	D3DVIEWPORT9 m_viewport;
	D3DXVECTOR3 m_posVDest;
	D3DXVECTOR3 m_posRDest;
	D3DXMATRIX m_mtxProje;				// プロジェクションマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	D3DXMATRIX m_mtxView;				// ビューマトリックス//ポリゴンの位置や回転行列すべてをつめてるナニカ
	
	bool m_isAnimation;
	bool m_isFree;
	bool m_isLoop;
	bool m_bossEnd;

	std::function<void()> m_func;
};


#endif


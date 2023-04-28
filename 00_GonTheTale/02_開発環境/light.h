//=========================================
// 
// ライトの作成(ヘッダーファイル)
// Author HAMAD
// 
//=========================================
#ifndef _LIGHT_H_
#define _LIGHT_H_

//------------------------------------
// マクロ定義
//------------------------------------
#define LIGTH_MAX	(5)

//------------------------------------
// プロトタイプ宣言
//------------------------------------

class CLight
{
public:
	CLight();
	~CLight();
	void Init();		// ポリゴンの初期化処理
	void Uninit();		// ポリゴンの終了処理
	void Update();		// ポリゴンの更新処理
		
	void Set(D3DLIGHTTYPE type, D3DXCOLOR col, D3DXVECTOR3 vec, int nNum);
	void AllSet();		// ポリゴンの更新処理

	D3DLIGHT9 getlight(int Data) { return m_light[Data]; }
private:

	 D3DLIGHT9 m_light[LIGTH_MAX];	//ライト情報

	
};



#endif // !_LIGHT_H_

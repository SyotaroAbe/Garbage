//=========================================================
//
// ゴミゲージ処理 [uigage.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _UIGAGE_H_     // このマクロ定義がされてなかったら
#define _UIGAGE_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "object.h"

//===============================================
// 前方宣言
//===============================================
class CObject2D;

//===============================================
// マクロ定義
//===============================================
#define AMOUNT_OF_RISE	(0.01f)				// ゲージ上昇量

//===============================================
// ゴミゲージクラス
//===============================================
class CUiGage
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CUiGage();						// デフォルトコンストラクタ
	CUiGage(int nPriority = 5);		// オーバーロードされたコンストラクタ
	~CUiGage();						// デストラクタ

	enum TEX
	{
		TEX_OUTSIDE = 0,	// 外側
		TEX_INSIDE,			// 内側
		TEX_MAX
	};

	static CUiGage *Create(int nIdx, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos, int nPriority);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(float fGarbage);
	bool GetMax(void);

private:	// 自分のみアクセス可能 [アクセス指定子]
	static CObject2D *m_apObject2D[TEX_MAX];		// オブジェクト2Dクラスのポインタ
	static const char *m_apTextureData[TEX_MAX];	// テクスチャファイル名
	static int m_aIdxTexture[TEX_MAX];				// 使用するテクスチャの番号

	float m_fTexU;									// テクスチャ座標の開始位置（U値）
	float m_fTexV;									// テクスチャ座標の開始位置（V値）
	float m_fGarbage;								// ゴミの量
};

#endif
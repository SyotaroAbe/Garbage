//=========================================================
//
// フィーバー描画処理 [fever.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _FEVER_H_     // このマクロ定義がされてなかったら
#define _FEVER_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "object2D.h"

//===============================================
// フィーバー描画クラス
//===============================================
class CFever : public CObject2D
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CFever();						// デフォルトコンストラクタ
	CFever(int nPriority = 0);		// オーバーロードされたコンストラクタ
	~CFever();						// デストラクタ

	static CFever *Create(int nPriority = 5);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	bool GetEndAnim(void) { return m_bEndAnim; }

private:	// 自分のみアクセス可能 [アクセス指定子]
	static int m_IdxTexture;			// 使用するテクスチャの番号
	bool m_bEndAnim;					// アニメーションが終了したか
};

#endif
//=========================================================
//
// ゴミステーション処理 [dumpster.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _DUMPSTER_H_     // このマクロ定義がされてなかったら
#define _DUMPSTER_H_     // 2重インクルード防止のマクロ定義する

#include "objectX.h"

//===============================================
// マクロ定義
//===============================================
#define MAX_DUMPSTER			(2)			// 最大ゴミステーション配置数
#define DUMPSTER_LENTH			(2500.0f)	// ゴミを回収できる範囲

//===============================================
// ゴミステーションクラス
//===============================================
class CDumpster : public CObjectX
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CDumpster();					// デフォルトコンストラクタ
	CDumpster(int nPriority = 3);	// オーバーロードされたコンストラクタ
	~CDumpster();					// デストラクタ

	static HRESULT Load(void);
	static void Unload(void);
	static CDumpster *Create(D3DXVECTOR3 pos, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	// 自分のみアクセス可能 [アクセス指定子]
	static int m_nIdxXFile;					// 使用するXファイルの番号
	bool m_bRockon;							// ターゲットの範囲内かどうか
};

#endif
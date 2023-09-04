//=========================================================
//
// ライト処理 [light.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _LIGHT_H_  // このマクロ定義がされてなかったら
#define _LIGHT_H_  // ２重インクルード防止のマクロを定義する

//===============================================
// マクロ定義
//===============================================
#define MAX_LGHT	(3)		// ライトの数

//===============================================
// ライトクラス
//===============================================
class CLight
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CLight();	// デフォルトコンストラクタ
	~CLight();	// デストラクタ

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);

private:	// 自分のみアクセス可能 [アクセス指定子]
	D3DLIGHT9 m_aLight[MAX_LGHT];	// ライトの情報
};

#endif
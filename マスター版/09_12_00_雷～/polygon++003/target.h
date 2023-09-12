//=========================================================
//
// ターゲット処理 [target.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _TARGET_H_     // このマクロ定義がされてなかったら
#define _TARGET_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "object2D.h"
#include "objectBillboard.h"
#include "garbage.h"

//===============================================
// マクロ定義
//===============================================
#define MAX_TARGET		(256)			// ターゲットの最大数
#define TARGET_SIZEX	(45.0f)			// 幅（半分）
#define TARGET_SIZEY	(45.0f)			// 高さ（半分）

//===============================================
// ターゲットクラス
//===============================================
class CTarget : public CObjectBillboard
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CTarget();						// デフォルトコンストラクタ
	CTarget(int nPriority = 2);		// オーバーロードされたコンストラクタ
	~CTarget();						// デストラクタ

	// ターゲットの状態
	typedef enum
	{
		STATE_NONE = 0,		// なし
		STATE_ROCKON,		// ロックオン
		STATE_MAX
	}STATE;

	static CTarget *Create(D3DXVECTOR3 pos, CGarbage::SEPARATION state, int nID, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

	void SetState(CGarbage::SEPARATION state);
	static CGarbage::SEPARATION GetState(void) { return m_state; }
	bool GetWithinRange(void) { return m_bWithinRange; }
	bool WithinRangeGarbage(void);

private:	// 自分のみアクセス可能 [アクセス指定子]
	static int m_nIdxTexture;					// 使用するテクスチャの番号
	static int m_nCntObjTarget[MAX_TARGET];		// ターゲットしているオブジェクトの番号保存
	static CGarbage::SEPARATION m_state;		// ターゲットの状態

	D3DXVECTOR3 m_LocalPos;				// 初期位置から見ての距離
	bool m_bWithinRange;				// ゴミがターゲットの範囲内
	float m_fMaltiRivision;				// 位置補正値
};

#endif
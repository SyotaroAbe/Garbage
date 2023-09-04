//=========================================================
//
// ごみ処理 [garbage.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _GARBAGE_H_     // このマクロ定義がされてなかったら
#define _GARBAGE_H_     // 2重インクルード防止のマクロ定義する

#include "main.h"
#include "objectX.h"
#include "particle.h"

//===============================================
// ごみクラス
//===============================================
class CGarbage : public CObjectX
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CGarbage();						// デフォルトコンストラクタ
	CGarbage(int nPriority = 3);	// オーバーロードされたコンストラクタ
	~CGarbage();					// デストラクタ

	// ゴミの種類
	typedef enum
	{
		TYPE_BAG = 0,				// 鞄
		TYPE_BUCKET,				// バケツ
		TYPE_HAT,					// 帽子
		//TYPE_SWIMRING,				// 浮き輪
		//TYPE_TAKOYAKI_MACHINE,		// タコ焼き機
		//TYPE_CAN,					// 缶
		//TYPE_POT,					// 鍋
		//TYPE_MIRROR,				// 鏡
		//TYPE_BOTTLE,				// ボトル
		//TYPE_TUBE,					// チューブ
		//TYPE_PLASTIC_BAG,			// ポリ袋
		//TYPE_EGGPACK,				// 卵パック
		TYPE_MAX
	}TYPE;

	// ゴミの分別
	typedef enum
	{
		SEPARATION_NONE = 0,		// なし
		SEPARATION_BURN,			// 燃えるゴミ
		SEPARATION_NONFLAMMABLE,	// 燃えないゴミ
		SEPARATION_PLASTIC,			// プラスチックゴミ
		SEPARATION_MAX
	}SEPARATION;

	// ゴミの状態
	typedef enum
	{
		STATE_NONE = 0,		// なし
		STATE_NORMAL,		// 通常状態
		STATE_ROCKON,		// ロックオン
		STATE_SEPARATION,	// 分別
		STATE_DISPOSE,		// 捨てる
		STATE_COLLECT,		// 回収
		STATE_INPLAYER,		// 描画しない
		STATE_DUMPSTER,		// ゴミステーション行き
		STATE_DELETE,		// 破棄
		STATE_MAX
	}STATE;

	static HRESULT Load(void);
	static void Unload(void);
	static CGarbage *Create(D3DXVECTOR3 pos, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Separation(SEPARATION separation);

	D3DXVECTOR3 GetMove(void) { return m_move; }
	int GetNumAll(void) { return m_nNumAll; }

private:	// 自分のみアクセス可能 [アクセス指定子]
	static int m_aIdxXFile[TYPE_MAX];		// 使用するXファイルの番号
	static int m_nNumAll;					// 総数
	static int m_nRandCounter;				// randリセット用

	D3DXVECTOR3 m_posDest;					// 目的の位置
	D3DXVECTOR3 m_posDiff;					// 目的の位置までの差分
	TYPE m_type;							// ゴミの種類
	STATE m_state;							// ゴミの状態
	SEPARATION m_separation;				// 分別の種類
	SEPARATION m_rockonType;				// ロックオン時の分別
	bool m_bLand;							// 地についているかどうか
	float m_fMoveDiff;						// 位置の補正係数
	int m_nWaitCounter;						// 静止している時間
	int m_nIdxDumpster;						// ゴミステーションの番号
	CParticle::TYPE particleType;			// パーティクルの種類
};

#endif
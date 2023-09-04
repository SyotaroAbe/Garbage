//=========================================================
//
// チュートリアル画面処理 [tutorial.h]
// Author = 阿部翔大郎
//
//=========================================================
#ifndef _TUTORIAL_H_     // このマクロ定義がされてなかったら
#define _TUTORIAL_H_     // 2重インクルード防止のマクロ定義する

#include "manager.h"

//===============================================
// 前方宣言
//===============================================
class CPlayer;
class CNumber;
class CScore;
class CMeshField;
class CTarget;
class CDumpster;
class CUiGage;
class CUiTarget;
class CFileLoad;

//===============================================
// チュートリアル画面クラス
//===============================================
class CTutorial : public CScene
{
public:		// 誰でもアクセス可能 [アクセス指定子]
	CTutorial();						// デフォルトコンストラクタ
	~CTutorial();						// デストラクタ

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CNumber *GetNumber() { return m_pNumber; }
	static CScore *GetScore() { return m_pScore; }
	static CGarbage *GetGarbage() { return m_pGarbage; }
	static CMeshField *GetMeshField() { return m_pMeshField; }
	static CFileLoad *GetLoad() { return m_pFileLoad; }
	static CTarget *GetTarget() { return m_pTarget; }
	static CDumpster *GetDumpster(int nIdx) { return m_pDumpster; }
	static CUiGage *GetUiGage() { return m_pUiGage; }
	static CUiTarget *GetUiTarget() { return m_pUiTarget; }

private:	// 自分のみアクセス可能 [アクセス指定子]
	static CPlayer *m_pPlayer;						// プレイヤークラスのポインタ
	static CNumber *m_pNumber;						// ナンバークラスのポインタ
	static CScore *m_pScore;						// スコアクラスのポインタ
	static CGarbage *m_pGarbage;					// ゴミクラスのポインタ
	static CMeshField *m_pMeshField;				// メッシュフィールドクラスのポインタ
	static CFileLoad *m_pFileLoad;					// ロードクラスのポインタ
	static CTarget *m_pTarget;						// ターゲットクラスのポインタ
	static CDumpster *m_pDumpster;					// ゴミステーションクラスのポインタ
	static CUiGage *m_pUiGage;						// ゴミゲージクラスのポインタ
	static CUiTarget *m_pUiTarget;					// ターゲットUIクラスのポインタ

	bool m_bFade;		// フェードに入ったか
};

#endif
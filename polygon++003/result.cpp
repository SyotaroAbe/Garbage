//=========================================================
//
// リザルト画面処理 [result.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "result.h"
#include "bg.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "ranking.h"
#include "rankIn.h"
#include "manager.h"
#include "sound.h"

//===============================================
// 静的メンバ変数
//===============================================
CBg *CResult::m_pBg = NULL;						// 背景クラスのポインタ
CRanking *CResult::m_pRanking = NULL;			// ランキングクラスのポインタ
CRankIn *CResult::m_pRankIn = NULL;				// ランクインクラスのポインタ

//===============================================
// コンストラクタ
//===============================================
CResult::CResult() : CScene()
{
	// 値のクリア
	m_bFade = false;
}

//===============================================
// デストラクタ
//===============================================
CResult::~CResult()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CResult::Init(HWND hWnd)
{
	// 背景の生成
	m_pBg = CBg::Create(CBg::TYPE_RESULT);

	// ランキングの生成
	m_pRanking = CRanking::Create(6);

	// ランクインの生成
	m_pRankIn = CRankIn::Create();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CResult::Uninit(void)
{
	if (m_pRanking != NULL)
	{
		// ランキングの終了処理
		m_pRanking->Uninit();
		delete m_pRanking;
		m_pRanking = NULL;
	}

	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//===============================================
// 更新処理
//===============================================
void CResult::Update(void)
{
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true)
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_TITLE);	// ゲームタイトル画面へ移行

			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_ENTER);

			m_bFade = true;
		}
	}

	if (m_pRanking != NULL)
	{
		// ランキングの更新処理
		m_pRanking->Update();
	}
}

//===============================================
// 描画処理
//===============================================
void CResult::Draw(void)
{
	if (m_pRanking != NULL)
	{
		// ランキングの描画処理
		m_pRanking->Draw();
	}
}
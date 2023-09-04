//=========================================================
//
// チュートリアル画面処理 [tutorial.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "tutorial.h"
#include "renderer.h"
#include "fade.h"
#include "manager.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "score.h"
#include "time.h"
#include "garbage.h"
#include "meshfield.h"
#include "target.h"
#include "uigage.h"
#include "uitarget.h"
#include "fileload.h"
#include "dumpster.h"

//===============================================
// 静的メンバ変数
//===============================================
CPlayer *CTutorial::m_pPlayer = NULL;					// プレイヤークラスのポインタ
CNumber *CTutorial::m_pNumber = NULL;					// ナンバークラスのポインタ
CScore *CTutorial::m_pScore = NULL;						// スコアクラスのポインタ
CGarbage *CTutorial::m_pGarbage = NULL;					// ゴミクラスのポインタ
CMeshField *CTutorial::m_pMeshField = NULL;				// メッシュフィールドクラスのポインタ
CTarget *CTutorial::m_pTarget = NULL;					// ターゲットクラスのポインタ
CDumpster *CTutorial::m_pDumpster = NULL;				// ゴミステーションクラスのポインタ
CUiGage *CTutorial::m_pUiGage = NULL;					// ゴミゲージクラスのポインタ
CUiTarget *CTutorial::m_pUiTarget = NULL;				// ターゲットUIクラスのポインタ
CFileLoad *CTutorial::m_pFileLoad = NULL;				// ロードクラスのポインタ

//===============================================
// コンストラクタ
//===============================================
CTutorial::CTutorial() : CScene()
{
	// 値のクリア
	m_bFade = false;
}

//===============================================
// デストラクタ
//===============================================
CTutorial::~CTutorial()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CTutorial::Init(HWND hWnd)
{
	// ロードの生成
	m_pFileLoad = new CFileLoad;

	if (m_pFileLoad != NULL)
	{// 使用されている
	 // ロードの読み込み処理
		if (FAILED(m_pFileLoad->Init(hWnd)))
		{// 読み込み処理が失敗した場合
			return -1;
		}
	}

	// カメラの初期化処理
	CManager::GetCamera()->Init();

	// メッシュフィールドの生成
	CMeshField::load(hWnd);

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);

	// ごみの生成
	CGarbage::Load();

	// ゴミステーションの読み込みと生成
	CDumpster::Load();
	m_pDumpster = CDumpster::Create(D3DXVECTOR3(300.0f, 0.0f, -200.0f), 2);

	// ターゲットの生成
	m_pTarget = CTarget::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGarbage::SEPARATION_NONE, -1, 5);

	// ターゲットUIの生成
	m_pUiTarget = CUiTarget::Create(5);

	// スコアの生成
	m_pScore = CScore::Create(6);

	// ゴミゲージの生成
	m_pUiGage = CUiGage::Create(6);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTutorial::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		// ファイル読み込みの終了処理
		m_pFileLoad->Uninit();
		delete m_pFileLoad;
		m_pFileLoad = NULL;
	}

	if (m_pScore != NULL)
	{
		// スコアの終了処理
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}

	if (m_pUiGage != NULL)
	{
		// ゴミゲージの終了処理
		delete m_pUiGage;
		m_pUiGage = NULL;
	}

	if (m_pUiTarget != NULL)
	{
		// ターゲットUIの終了処理
		delete m_pUiTarget;
		m_pUiTarget = NULL;
	}

	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//===============================================
// 更新処理
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true)
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_GAME);	// ゲーム画面へ移行
			m_bFade = true;
		}
	}

	if (m_pScore != NULL)
	{
		// スコアの更新処理
		m_pScore->Update();
	}

	if (m_pUiGage != NULL)
	{
		// ゴミゲージの更新処理
		m_pUiGage->Update();
	}

	if (m_pUiTarget != NULL)
	{
		// ターゲットUIの更新処理
		m_pUiTarget->Update();
	}
}

//===============================================
// 描画処理
//===============================================
void CTutorial::Draw(void)
{
	if (m_pScore != NULL)
	{
		// スコアの描画処理
		m_pScore->Draw();
	}

	if (m_pUiGage != NULL)
	{
		// ゴミゲージの描画処理
		m_pUiGage->Draw();
	}
}
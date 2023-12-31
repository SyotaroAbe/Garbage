//=========================================================
//
// タイトル画面処理 [title.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "title.h"
#include "bg.h"
#include "input.h"
#include "renderer.h"
#include "fade.h"
#include "sound.h"
#include "meshfield.h"
#include "manager.h"
#include "camera.h"
#include "garbage.h"
#include "player.h"
#include "logo.h"
#include "pressenter.h"

//===============================================
// マクロ定義
//===============================================
#define TIME_FADERANKING		(800)			// 自動フェード時間

//===============================================
// 静的メンバ変数
//===============================================
CPlayer *CTitle::m_pPlayer = NULL;				// プレイヤークラスのポインタ
CBg *CTitle::m_pBg = NULL;						// 背景クラスのポインタ
CLogo *CTitle::m_pLogo = NULL;					// タイトルロゴ描画クラスのポインタ
CPressEnter *CTitle::m_pPressEnter = NULL;		// PressEnter描画クラスのポインタ

//===============================================
// コンストラクタ
//===============================================
CTitle::CTitle() : CScene()
{
	// 値のクリア
	m_nTimeFade = 0;
	m_bFade = false;
}

//===============================================
// デストラクタ
//===============================================
CTitle::~CTitle()
{
	
}

//===============================================
// 初期化処理
//===============================================
HRESULT CTitle::Init(HWND hWnd)
{
	// カメラの初期化処理
	CManager::GetCamera()->Init();

	//// 背景の生成
	//m_pBg = CBg::Create(CBg::TYPE_TITLE, 6);

	// メッシュフィールドの生成
	CMeshField::RandArrange();

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);

	// ごみの生成
	CGarbage::Load();

	// タイトルロゴの生成
	m_pLogo = CLogo::Create();

	// PressEnterの生成
	m_pPressEnter = CPressEnter::Create();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTitle::Uninit(void)
{
	// 全てのオブジェクトの破棄
	CObject::ReleaseAll();
}

//===============================================
// 更新処理
//===============================================
void CTitle::Update(void)
{
	m_nTimeFade++;		// 時間をカウント

	if (m_pLogo->GetEndAnim() == true && (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true))
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// ゲーム画面へ移行
			m_bFade = true;

			// 点滅設定
			m_pPressEnter->SetBrightnessFade(true);

			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_ENTER);
		}
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_Q) == true || CManager::GetKeyboardInput()->GetPress(DIK_Z) == true
		|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_LB, 0) || CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_LEFT, 0)
		|| CManager::GetKeyboardInput()->GetPress(DIK_E) == true || CManager::GetKeyboardInput()->GetPress(DIK_C) == true
		|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_RB, 0) || CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_RIGHT, 0))
	{// プレイヤー（カメラ）を操作中
		m_nTimeFade = 0;		//	カウントをリセット
	}
	else if(m_nTimeFade > TIME_FADERANKING)
	{// 一定時間経過
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_RESULT);	// ランキング画面へ移行
			m_bFade = true;
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CTitle::Draw(void)
{
	
}
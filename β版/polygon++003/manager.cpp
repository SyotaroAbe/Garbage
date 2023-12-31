//=========================================================
//
// マネージャ処理 [manager.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "debugproc.h"
#include "sound.h"
#include "camera.h"
#include "light.h"
#include "object3D.h"
#include "objectBillboard.h"
#include "objectX.h"
#include "texture.h"
#include "garbage.h"
#include "xfile.h"
#include "edit.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"

//===============================================
// 静的メンバ変数
//===============================================
CManager *CManager::m_pManager = NULL;				// マネージャクラスのポインタ
CRenderer *CManager::m_pRenderer = NULL;			// レンダラークラスのポインタ
CInputKeyboard *CManager::m_pKeyboardInput = NULL;	// キーボード入力クラスのポインタ
CInputGamePad *CManager::m_pInputGamePad = NULL;	// ゲームパッド入力クラスのポインタ
CDebugProc *CManager::m_pDebugProc = NULL;			// デバッグ表示クラスのポインタ
CSound *CManager::m_pSound = NULL;					// サウンドクラスのポインタ
CCamera *CManager::m_pCamera = NULL;				// カメラクラスのポインタ
CLight *CManager::m_pLight = NULL;					// ライトクラスのポインタ
CTexture *CManager::m_pTexture = NULL;				// テクスチャクラスのポインタ
CXFile *CManager::m_pXFile = NULL;					// Xファイルクラスのポインタ
CEdit *CManager::m_pEdit = NULL;					// エディットクラスのポインタ
CGarbage *CManager::m_pGarbage = NULL;				// ゴミクラスのポインタ
CScene * CManager::m_pScene = NULL;					// シーンクラスのポインタ
HWND CManager::m_hWnd = NULL;						// ウインドウ保存用

CScene::MODE CScene::m_mode = CScene::MODE_TITLE;	// 現在の画面モード

//***********************************************************
// シーンクラス
//***********************************************************
//===============================================
// コンストラクタ
//===============================================
CScene::CScene()
{
	
}

//===============================================
// デストラクタ
//===============================================
CScene::~CScene()
{

}

//===============================================
// 生成処理
//===============================================
CScene *CScene::Create(HWND hWnd, MODE mode)
{
	CScene *pScene = NULL;

	// シーンの生成
	switch (mode)
	{
	case MODE_TITLE:	// タイトル画面
		pScene = new CTitle;
		break;

	case MODE_GAME:		// ゲーム画面
		pScene = new CGame;
		break;

	case MODE_RESULT:	// リザルト画面
		pScene = new CResult;
		break;
	}

	if (pScene != NULL)
	{// 使用されている
		// シーンの初期化処理
		pScene->Init(hWnd);

		// モードの設定
		pScene->SetMode(mode);
	}

	return pScene;
}

//===============================================
// シーン設定処理
//===============================================
void CScene::SetMode(MODE mode)
{
	m_mode = mode;
}

//***********************************************************
// マネージャクラス
//***********************************************************
//===============================================
// コンストラクタ
//===============================================
CManager::CManager()
{
	// 値のクリア
	m_nCountFPS = 0;
	m_bEdit = false;
}

//===============================================
// デストラクタ
//===============================================
CManager::~CManager()
{

}

//===============================================
// 初期化処理
//===============================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// ウインドウを保存
	m_hWnd = hWnd;

	// レンダラーの生成
	m_pRenderer = new CRenderer;

	// レンダラーの初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// キーボード入力の生成
	m_pKeyboardInput = new CInputKeyboard;

	// キーボード入力の初期化処理
	if (FAILED(m_pKeyboardInput->Init(hInstance, hWnd)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// ゲームパッド入力の生成
	m_pInputGamePad = new CInputGamePad;

	// ゲームパッド入力の初期化処理
	if (FAILED(m_pInputGamePad->Init(hInstance, hWnd)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// サウンドの生成
	m_pSound = new CSound;

	// サウンドの初期化処理
	if (FAILED(m_pSound->Init(hWnd)))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// カメラの生成
	m_pCamera = new CCamera;

	// カメラの初期化処理
	if (FAILED(m_pCamera->Init()))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// ライトの生成
	m_pLight = new CLight;

	// ライトの初期化処理
	if (FAILED(m_pLight->Init()))
	{// 初期化処理が失敗した場合
		return -1;
	}

	// テクスチャの生成
	m_pTexture = new CTexture;

	// テクスチャの読み込み処理
	if (FAILED(m_pTexture->Load()))
	{// 読み込み処理が失敗した場合
		return -1;
	}

	// Xファイルの生成
	m_pXFile = new CXFile;

	// Xファイルの読み込み処理
	if (FAILED(m_pXFile->Load()))
	{// 読み込み処理が失敗した場合
		return -1;
	}

	// シーン生成
	m_pScene = CScene::Create(hWnd, CScene::MODE_TITLE);

	// デバッグ表示の生成
	m_pDebugProc = new CDebugProc;

	// デバッグ表示の初期化処理
	m_pDebugProc->Init();

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CManager::Uninit(void)
{
	if (m_pScene != NULL)
	{// 使用されている
		// シーンの終了処理
		m_pScene->Uninit();
		delete m_pScene;
		m_pScene = NULL;
	}

	if (m_pRenderer != NULL)
	{// メモリが使用されている
		// キーボード入力の終了処理
		m_pKeyboardInput->Uninit();
		delete m_pKeyboardInput;
		m_pKeyboardInput = NULL;

		// ゲームパッド入力の終了処理
		m_pInputGamePad->Uninit();
		delete m_pInputGamePad;
		m_pInputGamePad = NULL;

		// レンダラーの終了処理
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;

		// サウンドの終了処理
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;

		// カメラの終了処理
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = NULL;

		// ライトの終了処理
		m_pLight->Uninit();
		delete m_pLight;
		m_pLight = NULL;

		// テクスチャの破棄
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;

		// Xファイルの破棄
		m_pXFile->Unload();
		delete m_pXFile;
		m_pXFile = NULL;

		// デバッグ表示の終了処理
		m_pDebugProc->Uninit();
		delete m_pDebugProc;
		m_pDebugProc = NULL;

		// メモリを開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//===============================================
// 更新処理
//===============================================
void CManager::Update(void)
{
	if (m_pRenderer != NULL)
	{// メモリが使用されている
		// FPSの表示
		m_pDebugProc->Print(" FPS：%d\n\n", m_nCountFPS);

		// キーボード入力の更新処理
		m_pKeyboardInput->Update();
		
		//if (CManager::GetKeyboardInput()->GetTrigger(DIK_R) == true)
		//{// ENTERキー入力
		//	// リセット
		//	CObject::Reset();
		//}
		//else if(CManager::GetKeyboardInput()->GetTrigger(DIK_F2) == true)
		//{// F2キー入力
		//	// エディット切り替え
		//	m_bEdit = m_bEdit ? false : true;
		//	m_pEdit->Set(m_bEdit);
		//}

		// ゲームパッド入力の更新処理
		m_pInputGamePad->Update();

		// レンダラーの更新処理
		m_pRenderer->Update();

		if (CGame::GetPauseState() == false || CGame::GetPauseCamera() == true)
		{// ポーズ状態
			// カメラの更新処理
			m_pCamera->Update();
		}

		// ライトの更新処理
		m_pLight->Update();

		// デバッグ表示の更新処理
		m_pDebugProc->Update();

		if (m_pScene != NULL)
		{
			// シーンの更新処理
			m_pScene->Update();
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{// メモリが使用されている
		// レンダラーの描画処理
		m_pRenderer->Draw();

		if (m_pScene != NULL)
		{
			// シーンの描画処理
			m_pScene->Draw();
		}
	}
}

//===============================================
// リセット処理
//===============================================
void CManager::Reset(void)
{
	// 敵の生成
	//m_pEnemy->Create(3)->SetPos(D3DXVECTOR3(700.0f, 250.0f, 0.0f));
	//m_pEnemy->Create(3)->SetPos(D3DXVECTOR3(800.0f, 250.0f, 0.0f));

	// アイテムの生成
	//CItem::Create(4)->Set(CItem::TYPE_TREASURE, D3DXVECTOR3(700.0f, 450.0f, 0.0f));
	//CItem::Create(4)->Set(CItem::TYPE_COIN, D3DXVECTOR3(800.0f, 450.0f, 0.0f));
}

//===============================================
// FPS設定処理
//===============================================
void CManager::SetFPS(int nCountFPS)
{
	m_nCountFPS = nCountFPS;
}

//===============================================
// シーン設定処理
//===============================================
void CManager::SetMode(CScene::MODE mode)
{
	int nScore;

	// サウンドの停止
	GetSound()->Stop();

	// シーンを代入
	CScene *pScenePrev = m_pScene;

	if (mode == CScene::MODE_RESULT)
	{// 次のモードがリザルト
		nScore = CGame::GetScore()->Get();
	}

	// 現在のモードの破棄
	if (pScenePrev != NULL)
	{
		pScenePrev->Uninit();
	}

	// 新しいモードの生成
	m_pScene = CScene::Create(m_hWnd, mode);

	if (mode == CScene::MODE_RESULT)
	{// 次のモードがリザルト
		// ランキングの設定
		CResult::GetRanking()->Add(nScore);
	}

	// メモリの開放
	delete pScenePrev;
	pScenePrev = NULL;
}

//===============================================
// シーン取得処理
//===============================================
CScene::MODE CManager::GetMode(void)
{
	return CScene::MODE_GAME;
}

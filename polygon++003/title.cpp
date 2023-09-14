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

//===============================================
// 静的メンバ変数
//===============================================
CBg *CTitle::m_pBg = NULL;						// 背景クラスのポインタ

//===============================================
// コンストラクタ
//===============================================
CTitle::CTitle() : CScene()
{
	// 値のクリア
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
	// 背景の生成
	m_pBg = CBg::Create(CBg::TYPE_TITLE, 6);

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
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true)
	{
		if (m_bFade == false)
		{// フェードバグ防止
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// ゲーム画面へ移行
			m_bFade = true;

			// サウンドの再生
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_ENTER);
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CTitle::Draw(void)
{
	
}
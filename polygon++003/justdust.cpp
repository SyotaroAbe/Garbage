//=========================================================
//
// JustDust表示処理 [justdust.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "justdust.h"
#include "manager.h"
#include "texture.h"
#include "tutorial.h"
#include "game.h"
#include "target.h"

//===============================================
// マクロ定義
//===============================================
#define SIZE_X				(63.0f)		// 横サイズ
#define SIZE_Y				(53.0f)		// 縦サイズ
#define DIFF_SIZE			(500.0f)	// サイズ
#define TIME_SCALLSIZE		(30)		// サイズ変更時間
#define SCALL_DIFF			(0.3f)		// サイズの値の補正

//===============================================
// 静的メンバ変数
//===============================================
int CJustDust::m_nIdxTexture = 0;				// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CJustDust::CJustDust() : CObjectBillboard(5)
{
	// 値のクリア
	m_nTime = 0;
	m_bScall = false;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CJustDust::CJustDust(int nPriority) : CObjectBillboard(nPriority)
{
	// 値のクリア
	m_nTime = 0;
	m_bScall = false;
}

//===============================================
// デストラクタ
//===============================================
CJustDust::~CJustDust()
{
	
}

//===============================================
// 生成処理
//===============================================
CJustDust *CJustDust::Create(int nPriority)
{
	CJustDust *pUi;

	// 背景の生成
	pUi = new CJustDust(nPriority);

	// 種類の設定
	pUi->SetType(TYPE_BULLET);

	// サイズの設定
	pUi->SetSize(DIFF_SIZE, DIFF_SIZE);

	// 初期化処理
	pUi->Init(D3DXVECTOR3(650.0f, 600.0f, 0.0f), nPriority);

	// テクスチャの割り当て
	pUi->BindTexture(m_nIdxTexture);

	return pUi;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CJustDust::Init(D3DXVECTOR3 pos, int nPriority)
{
	// オブジェクト2Dの初期化処理
	CObjectBillboard::Init(pos);

	// テクスチャの設定
	m_nIdxTexture = CManager::GetTexture()->Regist("data\\TEXTURE\\JustDust.png");

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CJustDust::Uninit(void)
{
	// オブジェクト2Dの終了処理
	CObjectBillboard::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CJustDust::Update(void)
{
	D3DXVECTOR3 posTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ターゲットの位置

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{// チュートリアル
		posTarget = CTutorial::GetTarget()->GetPos();
	}
	else if (CManager::GetMode() == CScene::MODE_GAME)
	{// ゲーム画面
		posTarget = CGame::GetTarget()->GetPos();
	}

	// オブジェクト2Dの位置設定処理
	CObjectBillboard::SetPos(D3DXVECTOR3(posTarget.x - 150.0f, posTarget.y + 50.0f, posTarget.z));

	if (m_nTime > TIME_SCALLSIZE)
	{
		m_bScall = m_bScall ? false : true;		// サイズ切り替え
		m_nTime = 0;							// 値を初期化
	}

	if (m_bScall == false)
	{
		// 拡大処理
		CObjectBillboard::ScalingSize(DIFF_SIZE, 1.0f);
	}
	else
	{
		m_nTime++;		// 時間をカウント

		// 縮小処理
		CObjectBillboard::ScalingSize(SIZE_X, SCALL_DIFF);
	}

	// オブジェクト2Dの更新処理
	CObjectBillboard::Update();
}

//===============================================
// 描画処理
//===============================================
void CJustDust::Draw(void)
{
	if (m_bScall == true)
	{
		// オブジェクト2Dの描画処理
		CObjectBillboard::Draw();
	}
}

//===============================================
// 設定処理
//===============================================
void CJustDust::Set(bool bScall)
{
	m_bScall = bScall;
}
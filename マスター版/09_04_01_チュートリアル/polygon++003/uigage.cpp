//=========================================================
//
// ゴミゲージ処理 [uigage.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "uigage.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "input.h"

//===============================================
// マクロ定義
//===============================================
#define SIZE_X			(100.0f)			// 横サイズ
#define SIZE_Y			(100.0f)			// 縦サイズ
#define MAX_GARBAGE		(1.0f)				// 最大ゴミ量

//===============================================
// 静的メンバ変数
//===============================================
CObject2D *CUiGage::m_apObject2D[TEX_MAX];				// オブジェクト2Dクラスのポインタ
const char *CUiGage::m_apTextureData[TEX_MAX] = {};		// テクスチャファイル名
int CUiGage::m_aIdxTexture[TEX_MAX] = {};				// 使用するテクスチャの番号

//===============================================
// コンストラクタ
//===============================================
CUiGage::CUiGage()
{
	// 値のクリア
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_fGarbage = 0.0f;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CUiGage::CUiGage(int nPriority)
{
	// 値のクリア
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_fGarbage = 0.0f;
}

//===============================================
// デストラクタ
//===============================================
CUiGage::~CUiGage()
{
	
}

//===============================================
// 生成処理
//===============================================
CUiGage *CUiGage::Create(int nIdx, int nPriority)
{
	CUiGage *pUi;

	// 背景の生成
	pUi = new CUiGage(nPriority);

	// 初期化処理
	pUi->Init(D3DXVECTOR3(150.0f, 600.0f, 0.0f), nPriority);

	return pUi;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CUiGage::Init(D3DXVECTOR3 pos, int nPriority)
{
	// テクスチャファイル名
	const char *m_apTextureData[TEX_MAX] =
	{
		{ "data\\TEXTURE\\gage002.png" },	// 外側
		{ "data\\TEXTURE\\gage001.png" }	// 内側
	};

	for (int nCntObj = 0; nCntObj < TEX_MAX; nCntObj++)
	{
		m_apObject2D[nCntObj] = new CObject2D(nPriority);

		m_apObject2D[nCntObj]->SetSize(SIZE_X, SIZE_Y);

		// オブジェクト2Dの初期化処理
		m_apObject2D[nCntObj]->Init(pos);

		// テクスチャの設定
		m_aIdxTexture[nCntObj] = CManager::GetTexture()->Regist(m_apTextureData[nCntObj]);

		// テクスチャの割り当て
		m_apObject2D[nCntObj]->BindTexture(m_aIdxTexture[nCntObj]);
	}

	// テクスチャ座標の更新処理
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CUiGage::Uninit(void)
{
	
}

//===============================================
// 更新処理
//===============================================
void CUiGage::Update(void)
{
#if _DEBUG
	if (CManager::GetKeyboardInput()->GetPress(DIK_1) == true)
	{// 1キー
		// 設定処理
		Set(AMOUNT_OF_RISE);
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_2) == true)
	{// 2キー
		// 設定処理
		Set(-MAX_GARBAGE);
	}
#endif
}

//===============================================
// 描画処理
//===============================================
void CUiGage::Draw(void)
{
	if (m_fGarbage == MAX_GARBAGE)
	{// ゴミの量が最大
		// 色の更新処理（赤）
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		// 色の更新処理（白）
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(m_fGarbage, 1.0f - m_fGarbage * 0.5f, 1.0f - m_fGarbage, 1.0f));
	}
}

//===============================================
// 設定処理
//===============================================
void CUiGage::Set(float fGarbage)
{
	m_fGarbage += fGarbage;

	if (m_fGarbage > MAX_GARBAGE)
	{// 最大量を超えた
		m_fGarbage = MAX_GARBAGE;
	}
	else if (m_fGarbage < 0.0f)
	{// 最少量を超えた
		m_fGarbage = 0.0f;
	}

	// 位置の更新処理
	m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(150.0f, 700.0f - m_fGarbage * SIZE_Y, 0.0f), SIZE_X, m_fGarbage * SIZE_Y);

	// テクスチャ座標の更新処理
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 0.0f, 1.0f, 1.0f, m_fGarbage, 0.0f);
}

//===============================================
// ゲージが最大であるか取得処理
//===============================================
bool CUiGage::GetMax(void)
{
	if (m_fGarbage >= MAX_GARBAGE)
	{// 最大量を超えた
		return true;
	}

	return false;
}
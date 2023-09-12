//=========================================================
//
// ゴミステーション処理 [dumpster.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "dumpster.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "xfile.h"
#include "game.h"
#include "player.h"
#include "tutorial.h"

//===============================================
// マクロ定義
//===============================================
#define DELETE_POSITION			(650.0f)	// 床を破棄する位置

//===============================================
// 静的メンバ変数
//===============================================
int CDumpster::m_nIdxXFile = 0;			// 使用するXファイルの番号

//===============================================
// コンストラクタ
//===============================================
CDumpster::CDumpster() : CObjectX(4)
{
	// 値のクリア
	m_bRockon = false;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CDumpster::CDumpster(int nPriority) : CObjectX(nPriority)
{
	// 値のクリア
	m_bRockon = false;
}

//===============================================
// デストラクタ
//===============================================
CDumpster::~CDumpster()
{
	
}

//===============================================
// モデルの生成（読み込み）
//===============================================
HRESULT CDumpster::Load(void)
{
	// Ｘファイルに読み込み
	m_nIdxXFile = CManager::GetXFile()->Regist("data\\MODEL\\Dumpster001.x");

	return S_OK;
}

//===============================================
// モデルの破棄
//===============================================
void CDumpster::Unload(void)
{
	
}

//===============================================
// 生成処理
//===============================================
CDumpster *CDumpster::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority)
{
	CDumpster *pGarbage = NULL;

	// ゴミの生成
	pGarbage = new CDumpster(nPriority);

	// 種類の設定
	pGarbage->SetType(CObject::TYPE_DUMPSTER);

	// 初期化処理
	pGarbage->Init(pos);

	// 向きの設定
	pGarbage->SetRot(rot);

	return pGarbage;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CDumpster::Init(D3DXVECTOR3 pos)
{
	// オブジェクトXの初期化処理
	CObjectX::Init(pos);

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CDumpster::Uninit(void)
{
	// オブジェクトXの終了処理
	CObjectX::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CDumpster::Update(void)
{
	// 前回の位置を保存
	m_posOld = m_pos;

	if (CManager::GetMode() == CScene::MODE_TUTORIAL && (m_pos.x <= CTutorial::GetPlayer()->GetPos().x + DUMPSTER_LENTH && m_pos.x >= CTutorial::GetPlayer()->GetPos().x - DUMPSTER_LENTH
		&& m_pos.z <= CTutorial::GetPlayer()->GetPos().z + DUMPSTER_LENTH && m_pos.z >= CTutorial::GetPlayer()->GetPos().z - DUMPSTER_LENTH)
		|| CManager::GetMode() == CScene::MODE_GAME && (m_pos.x <= CGame::GetPlayer()->GetPos().x + DUMPSTER_LENTH && m_pos.x >= CGame::GetPlayer()->GetPos().x - DUMPSTER_LENTH
		&& m_pos.z <= CGame::GetPlayer()->GetPos().z + DUMPSTER_LENTH && m_pos.z >= CGame::GetPlayer()->GetPos().z - DUMPSTER_LENTH))
	{// ターゲットがゴミステーションを利用できる範囲内に入った
		m_bRockon = true;	// ターゲットの範囲内へ切り替える
	}
	else
	{
		m_bRockon = false;	// ターゲットの範囲外へ切り替える
	}

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (CTutorial::GetPlayer()->GetPos().z < m_pos.z - DELETE_POSITION)
		{// 床が画面外へいった
			// 終了処理
			Uninit();
		}
	}
}

//===============================================
// 描画処理
//===============================================
void CDumpster::Draw(void)
{
	if (m_bRockon == true)
	{// ターゲットの範囲内
		// オブジェクトXの描画処理（赤色）
		CObjectX::DrawXFile(m_nIdxXFile, CXFile::COL_RED);
	}
	else
	{// ターゲットの範囲外
		// オブジェクトXの描画処理（通常色）
		CObjectX::DrawXFile(m_nIdxXFile, CXFile::COL_NORMAL);
	}
}
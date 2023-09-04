//=========================================================
//
// ターゲット処理 [target.cpp]
// Author = 阿部翔大郎
//
//=========================================================
#include "target.h"
#include "rockon.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "objectBillboard.h"
#include "texture.h"
#include "camera.h"
#include "player.h"
#include "debugproc.h"
#include "garbage.h"
#include "game.h"
#include "tutorial.h"

//===============================================
// マクロ定義
//===============================================
#define DISTANCE_PLAYER		(-400.0f)		// プレイヤーとの距離
#define SPEED_TARGET		(23.0f)			// 移動速度
#define MAX_LENTH			(270.0f)		// 最大位置
#define ROT_DIFF			(0.5f)			// 曲がる角度の差分
#define POS_DIFF			(0.1f)			// 位置の値の補正

//===============================================
// 静的メンバ変数
//===============================================
int CTarget::m_nIdxTexture = 0;											// 使用するテクスチャの番号
int CTarget::m_nCntObjTarget[MAX_TARGET] = {};							// ターゲットしているオブジェクトの番号保存
CGarbage::SEPARATION CTarget::m_state = CGarbage::SEPARATION_NONE;		// ターゲットの状態

//===============================================
// コンストラクタ
//===============================================
CTarget::CTarget() : CObjectBillboard(3)
{
	// 値のクリア
	m_LocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bWithinRange = false;
}

//===============================================
// コンストラクタ（オーバーロード）
//===============================================
CTarget::CTarget(int nPriority) : CObjectBillboard(nPriority)
{
	// 値のクリア
	m_LocalPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bWithinRange = false;
}

//===============================================
// デストラクタ
//===============================================
CTarget::~CTarget()
{
	
}

//===============================================
// 生成処理
//===============================================
CTarget *CTarget::Create(D3DXVECTOR3 pos, CGarbage::SEPARATION state, int nID, int nPriority)
{
	CTarget *pTarget;

	// 弾の生成
	pTarget = new CTarget(nPriority);

	// 種類の設定
	pTarget->SetType(TYPE_TARGET);

	// サイズの設定
	pTarget->SetSize(TARGET_SIZEX, TARGET_SIZEY);

	// 初期化処理
	pTarget->Init(pos);

	// 状態の設定
	pTarget->SetState(state);

	// テクスチャの割り当て
	pTarget->BindTexture(m_nIdxTexture);

	return pTarget;
}

//===============================================
// 初期化処理
//===============================================
HRESULT CTarget::Init(D3DXVECTOR3 pos)
{
	// ビルボードの初期化処理
	CObjectBillboard::Init(pos);

	float fPlayerRot = 0.0f;
	D3DXVECTOR3 playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		fPlayerRot = CTutorial::GetPlayer()->GetRot().y;	// プレイヤーの向きを取得
		playerPos = CTutorial::GetPlayer()->GetPos();		// プレイヤーの位置
	}
	else if (CManager::GetMode() == CScene::MODE_GAME)
	{
		fPlayerRot = CGame::GetPlayer()->GetRot().y;	// プレイヤーの向きを取得
		playerPos = CGame::GetPlayer()->GetPos();		// プレイヤーの位置
	}

	// プレイヤーの前方位置をターゲットの位置に設定
	m_pos.x = playerPos.x + m_LocalPos.x + sinf(fPlayerRot) * DISTANCE_PLAYER;
	m_pos.z = playerPos.z + m_LocalPos.z + cosf(fPlayerRot) * DISTANCE_PLAYER;
	m_pos.y = 0.0f;

	// テクスチャの設定
	m_nIdxTexture = CManager::GetTexture()->Regist("data\\TEXTURE\\target000.png");

	return S_OK;
}

//===============================================
// 終了処理
//===============================================
void CTarget::Uninit(void)
{
	// ビルボードの終了処理
	CObjectBillboard::Uninit();
}

//===============================================
// 更新処理
//===============================================
void CTarget::Update(void)
{
	// 前回の位置を保存
	m_posOld = m_pos;

	float fCameraRot = CManager::GetCamera()->GetRot().y;		// カメラの向きを取得
	D3DXVECTOR3 fPosDiff;										// 目的の位置までの差分を保存
	float fPlayerRot = 0.0f;									// プレイヤーの向きを取得
	D3DXVECTOR3 playerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// プレイヤーの位置
	CPlayer::TURN playerTurn = CPlayer::TURN_NONE;				// プレイヤーの方向変更情報

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		fPlayerRot = CTutorial::GetPlayer()->GetRot().y;
		playerPos = CTutorial::GetPlayer()->GetPos();
		playerTurn = CTutorial::GetPlayer()->GetTurn();
	}
	else if (CManager::GetMode() == CScene::MODE_GAME)
	{
		fPlayerRot = CGame::GetPlayer()->GetRot().y;
		playerPos = CGame::GetPlayer()->GetPos();
		playerTurn = CGame::GetPlayer()->GetTurn();
	}

	// プレイヤーの前方位置をターゲットの位置に設定
	m_pos.x = playerPos.x + m_LocalPos.x + sinf(fPlayerRot) * DISTANCE_PLAYER;
	m_pos.z = playerPos.z + m_LocalPos.z + cosf(fPlayerRot) * DISTANCE_PLAYER;
	m_pos.y = 0.0f;

	// ゴミとターゲットの当たり判定
	if (WithinRangeGarbage() == true)
	{// ゴミがターゲットの範囲内
		// オブジェクトビルボードの色設定
		CObjectBillboard::SetCol(D3DXCOLOR(0.9f, 0.8f, 0.2f, 1.0f));	// 黄
		m_bWithinRange = true;
	}
	else
	{
		// オブジェクトビルボードの色設定
		CObjectBillboard::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// 白
		m_bWithinRange = false;
	}

	// ターゲット位置変更
	if (CManager::GetKeyboardInput()->GetPress(DIK_A) == true
		|| CManager::GetInputGamePad()->GetJoyStickLX(0) < 0)
	{
		if (CManager::GetKeyboardInput()->GetPress(DIK_W) == true
			|| CManager::GetInputGamePad()->GetJoyStickLY(0) > 0)
		{// Wキー入力
			m_LocalPos.x += sinf(D3DX_PI * ROT_LEFTUP + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
			m_LocalPos.z += cosf(D3DX_PI * ROT_LEFTUP + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		}
		else if (CManager::GetKeyboardInput()->GetPress(DIK_S) == true
				|| CManager::GetInputGamePad()->GetJoyStickLY(0) < 0)
		{// Sキー入力
			m_LocalPos.x += sinf(D3DX_PI * ROT_LEFTDOWN + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
			m_LocalPos.z += cosf(D3DX_PI * ROT_LEFTDOWN + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		}
		else
		{// Aキー入力
			m_LocalPos.x += sinf(D3DX_PI * ROT_LEFT + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
			m_LocalPos.z += cosf(D3DX_PI * ROT_LEFT + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		}
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_D) == true
			|| CManager::GetInputGamePad()->GetJoyStickLX(0) > 0)
	{
		if (CManager::GetKeyboardInput()->GetPress(DIK_W) == true
			|| CManager::GetInputGamePad()->GetJoyStickLY(0) > 0)
		{// Wキー入力
			m_LocalPos.x += sinf(D3DX_PI * ROT_RIGHTUP + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
			m_LocalPos.z += cosf(D3DX_PI * ROT_RIGHTUP + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		}
		else if (CManager::GetKeyboardInput()->GetPress(DIK_S) == true
				|| CManager::GetInputGamePad()->GetJoyStickLY(0) < 0)
		{// Sキー入力
			m_LocalPos.x += sinf(D3DX_PI * ROT_RIGHTDOWN + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
			m_LocalPos.z += cosf(D3DX_PI * ROT_RIGHTDOWN + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		}
		else
		{// Dキー入力
			m_LocalPos.x += sinf(D3DX_PI * ROT_RIGHT + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
			m_LocalPos.z += cosf(D3DX_PI * ROT_RIGHT + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		}
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_W) == true
			|| CManager::GetInputGamePad()->GetJoyStickLY(0) > 0)
	{// Wキー入力
		m_LocalPos.x += sinf(D3DX_PI * ROT_UP + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		m_LocalPos.z += cosf(D3DX_PI * ROT_UP + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_S) == true
			|| CManager::GetInputGamePad()->GetJoyStickLY(0) < 0)
	{// Sキー入力
		m_LocalPos.x += sinf(D3DX_PI * ROT_DOWN + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
		m_LocalPos.z += cosf(D3DX_PI * ROT_DOWN + (ROT_CAMERA * fCameraRot)) * SPEED_TARGET;
	}

	// ターゲット種類変更
	if (CManager::GetKeyboardInput()->GetPress(DIK_LEFT) == true
		|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_X, 0) == true)
	{// 左キーが押された
		// 燃えるゴミ
		SetState(CGarbage::SEPARATION_BURN);
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_UP) == true
		|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_Y, 0) == true)
	{// 上キーが押された
		// 燃えないゴミ
		SetState(CGarbage::SEPARATION_NONFLAMMABLE);
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_RIGHT) == true
		|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_B, 0) == true)
	{// 右キーが押された
		// プラスチックゴミ
		SetState(CGarbage::SEPARATION_PLASTIC);
	}
	else
	{// 入力されていない
		// なし
		SetState(CGarbage::SEPARATION_NONE);
	}

	D3DXVECTOR3 posDest = m_LocalPos;		// 目的の位置

	// ターゲット位置の補正
	if (fPlayerRot <= D3DX_PI * ROT_LEFT + ROT_DIFF && fPlayerRot >= D3DX_PI * ROT_LEFT - ROT_DIFF)
	{// プレイヤーが初期位置から見て左向き
		if (playerTurn != CPlayer::TURN_BACK)
		{// プレイヤーが折り返ししない
			// X座標の位置を初期化する
			posDest.x = 0.0f;
		}
	}
	else if (fPlayerRot <= D3DX_PI * ROT_RIGHT + ROT_DIFF && fPlayerRot >= D3DX_PI * ROT_RIGHT - ROT_DIFF)
	{// プレイヤーが初期位置から見て右向き
		if (playerTurn != CPlayer::TURN_BACK)
		{// プレイヤーが折り返ししない
			// X座標の位置を初期化する
			posDest.x = 0.0f;
		}
	}
	else if ((fPlayerRot <= D3DX_PI + ROT_DIFF && fPlayerRot >= D3DX_PI - ROT_DIFF)
		|| (fPlayerRot <= -D3DX_PI + ROT_DIFF && fPlayerRot >= -D3DX_PI - ROT_DIFF))
	{// プレイヤーが初期位置から見て下向き
		if (playerTurn != CPlayer::TURN_BACK)
		{// プレイヤーが折り返ししない
			// Z座標の位置を初期化する
			posDest.z = 0.0f;
		}
	}
	else if (fPlayerRot <= ROT_DIFF && fPlayerRot >= -ROT_DIFF)
	{// プレイヤーが初期位置から見て上向き
		if (playerTurn != CPlayer::TURN_BACK)
		{// プレイヤーが折り返ししない
			// Z座標の位置を初期化する
			posDest.z = 0.0f;
		}
	}

	// 目的の位置までの差分を計算
	fPosDiff.x = posDest.x - m_LocalPos.x;
	fPosDiff.z = posDest.z - m_LocalPos.z;

	// 角度の補正
	m_LocalPos.x += fPosDiff.x * POS_DIFF;
	m_LocalPos.z += fPosDiff.z * POS_DIFF;

	// 移動位置制限
	if (m_LocalPos.x > MAX_LENTH)
	{// X座標の最大値を超えた
		m_LocalPos.x = MAX_LENTH;
	}
	else if (m_LocalPos.x < -MAX_LENTH)
	{// X座標の最小値を超えた
		m_LocalPos.x = -MAX_LENTH;
	}

	if (m_LocalPos.z > MAX_LENTH)
	{// Ｚ座標の最大値を超えた
		m_LocalPos.z = MAX_LENTH;
	}
	else if (m_LocalPos.z < -MAX_LENTH)
	{// Ｚ座標の最小値を超えた
		m_LocalPos.z = -MAX_LENTH;
	}

	// デバッグ表示表示
	CManager::GetDebugProc()->Print(" ターゲット総数：%d\n", CRockon::GetNumAll());
	CManager::GetDebugProc()->Print(" ターゲットの位置：（%f, %f, %f）\n", m_pos.x, m_pos.y, m_pos.z);
}

//===============================================
// 描画処理
//===============================================
void CTarget::Draw(void)
{
	// ビルボードの描画処理
	CObjectBillboard::Draw();
}

//===============================================
// 設定処理
//===============================================
void CTarget::Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move)
{
	m_pos = pos;
	m_move = move;
}

//===============================================
// 状態の設定処理
//===============================================
void CTarget::SetState(CGarbage::SEPARATION state)
{
	m_state = state;

	// 分別ごとに色を設定する
	switch (m_state)
	{
	case CGarbage::SEPARATION_NONE:			// なし
		// オブジェクトビルボードの色設定
		//CObjectBillboard::SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// なし
		break;

	case CGarbage::SEPARATION_BURN:			// 燃えるゴミ
		// オブジェクトビルボードの色設定
		CObjectBillboard::SetCol(D3DXCOLOR(0.9f, 0.5f, 0.2f, 1.0f));	// オレンジ
		break;

	case CGarbage::SEPARATION_NONFLAMMABLE:	// 燃えないゴミ
		// オブジェクトビルボードの色設定
		CObjectBillboard::SetCol(D3DXCOLOR(0.4f, 0.9f, 1.0f, 1.0f));	// 水色
		break;

	case CGarbage::SEPARATION_PLASTIC:		// プラスチックゴミ
		// オブジェクトビルボードの色設定
		CObjectBillboard::SetCol(D3DXCOLOR(0.2f, 1.0f, 0.2f, 1.0f));	// 緑
		break;
	}
}

//===============================================
// ゴミとターゲットの当たり判定処理
//===============================================
bool CTarget::WithinRangeGarbage(void)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		CObject *pObj = CObject::GetTop(nCntPriority);		// 先頭のオブジェクトを代入

		while (pObj != NULL)
		{// 使用されている			// 種類を取得
			CObject::TYPE type = pObj->GetType();	// 種類を取得
			CObject *pObjectNext = pObj->GetNext();	// 次のオブジェクトを保存

			if (type == TYPE_GARBAGE)
			{// ゴミ
				if (pObj->GetPos().x <= m_pos.x + TARGET_SIZEX + TARGET_SIZEX && pObj->GetPos().x >= m_pos.x - TARGET_SIZEX - TARGET_SIZEX
					&& pObj->GetPos().z <= m_pos.z + TARGET_SIZEY + TARGET_SIZEY && pObj->GetPos().z >= m_pos.z - TARGET_SIZEY - TARGET_SIZEY)
				{// ターゲットの範囲内に入った
					return true;
				}
			}

			pObj = pObjectNext;	// 次のオブジェクトを代入
		}
	}

	return false;
}
//=========================================================
//
// ���ݏ��� [garbage.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "garbage.h"
#include "manager.h"
#include "renderer.h"
#include "score.h"
#include "objectX.h"
#include "player.h"
#include "input.h"
#include "particle.h"
#include "debugproc.h"
#include "xfile.h"
#include "target.h"
#include "rockon.h"
#include "dumpster.h"
#include "game.h"
#include "effect.h"
#include "uigage.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CGarbage::m_aIdxXFile[TYPE_MAX] = {};			// �g�p����X�t�@�C���̔ԍ�
int CGarbage::m_nNumAll = 0;						// ����
int CGarbage::m_nRandCounter = 0;					// rand���Z�b�g�p

//===============================================
// �}�N����`
//===============================================
#define MAX_GABAGE		(1024)		// �S�~�̍ő吔
#define MOVE_DIFF		(0.02f)		// �ʒu�̕␳�W���i�����傫�����f�����ς��j
#define JUMP_HEIGHT		(16.85f)	// �W�����v��
#define ADD_SCORE		(100)		// �������̃X�R�A
#define SUB_SCORE		(-50)		// �s�������̃X�R�A

#define DISPOSE_LENTHZ			(150.0f)	// �S�~������ł���͈�(Z)
#define DISPOSE_LENTHX			(300.0f)	// �S�~������ł���͈�(X)
#define DISPOSE_DISTANCE		(250.0f)	// �S�~������ł���v���C���[����̑O������
#define DIFF_DISPOSE			(10.0f)		// �S�~������ł���͈͂̌덷

#define DIFF_HEIGHT			(100.0f)	// �S�~������̖ړI�̍���
#define GRAVITY_DISPOSE		(10.0f)		// �̂Ă鎞�̏d��
#define WAIT_TIME			(60)		// �̂Ă����ƂɐÎ~���Ă��鎞��

//===============================================
// �R���X�g���N�^
//===============================================
CGarbage::CGarbage() : CObjectX(4)
{
	// �l�̃N���A
	m_posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_BAG;
	m_state = STATE_NONE;
	m_separation = SEPARATION_NONE;
	m_rockonType = SEPARATION_NONE;
	m_bLand = false;
	m_fMoveDiff = 0.0f;
	m_nIdxDumpster = 0;
	particleType = CParticle::TYPE_BURN;

	m_nNumAll++;	// �������J�E���g�A�b�v
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CGarbage::CGarbage(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_type = TYPE_BAG;
	m_state = STATE_NONE;
	m_separation = SEPARATION_NONE;
	m_rockonType = SEPARATION_NONE;
	m_bLand = false;
	m_fMoveDiff = 0.0f;
	m_nIdxDumpster = 0;
	particleType = CParticle::TYPE_BURN;

	m_nNumAll++;		// �������J�E���g�A�b�v
}

//===============================================
// �f�X�g���N�^
//===============================================
CGarbage::~CGarbage()
{
	m_nNumAll--;		// �������J�E���g�_�E��
}

//===============================================
// ���f���̐����i�ǂݍ��݁j
//===============================================
HRESULT CGarbage::Load(void)
{
	// �w�t�@�C���ɓǂݍ���
	m_aIdxXFile[TYPE_BAG] = CManager::GetXFile()->Regist("data\\MODEL\\Stage_Illumination.x");
	m_aIdxXFile[TYPE_BUCKET] = CManager::GetXFile()->Regist("data\\MODEL\\Chair001.x");
	m_aIdxXFile[TYPE_HAT] = CManager::GetXFile()->Regist("data\\MODEL\\Camera001.x");

	return S_OK;
}

//===============================================
// �e�N�X�`���̔j��
//===============================================
void CGarbage::Unload(void)
{
	
}

//===============================================
// ��������
//===============================================
CGarbage *CGarbage::Create(D3DXVECTOR3 pos, int nPriority)
{
	CGarbage *pGarbage = NULL;

	if (MAX_GABAGE > m_nNumAll)
	{// �����ɒB���Ă��Ȃ�
		// �S�~�̐���
		pGarbage = new CGarbage(nPriority);

		// ��ނ̐ݒ�
		pGarbage->SetType(CObject::TYPE_GARBAGE);

		// ����������
		pGarbage->Init(pos);
	}
	else
	{
		m_nNumAll = MAX_GABAGE;		// ������߂�
	}

	return pGarbage;
}

//===============================================
// ����������
//===============================================
HRESULT CGarbage::Init(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�gX�̏���������
	CObjectX::Init(pos);

	// ��ނ̐ݒ�
	srand(m_nRandCounter);					// rand�̒l�����Z�b�g
	m_type = (TYPE)(rand() % TYPE_MAX);		// rand�̒l���擾

	// ��Ԃ̐ݒ�
	m_state = STATE_NORMAL;

	// ���ʂ̎��
	switch (m_type)
	{
	case TYPE_BAG:		// ��
		// �R���Ȃ��S�~
		m_separation = SEPARATION_NONFLAMMABLE;
		break;

	case TYPE_BUCKET:	// �o�P�c
		// �R����S�~
		m_separation = SEPARATION_BURN;
		break;

	default:			// ���̑�
		// �v���X�`�b�N�S�~
		m_separation = SEPARATION_PLASTIC;
		break;
	}

	m_nRandCounter++;	// rand���l�ύX

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CGarbage::Uninit(void)
{
	// �I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CGarbage::Update(void)
{
	// �O��̈ʒu��ۑ�
	m_posOld = m_pos;

	D3DXVECTOR3 PlayerPos = CGame::GetPlayer()->GetPos();			// �v���C���[�̈ʒu���擾
	D3DXVECTOR3 PlayerRot = CGame::GetPlayer()->GetRot();			// �v���C���[�̌������擾

	//�d�͏���
	m_move.y -= MOVE_GRAVITY;

	if (m_pos.y < LAND_POS)
	{// ���n����
		// �ʒu��߂�
		m_pos.y = LAND_POS;
		m_move.y = 0.0f;
	}

	// ��ԕʂɏ�������
	switch (m_state)
	{
	case STATE_NORMAL:			// �ʏ���
		if (m_pos.x <= CGame::GetTarget()->GetPos().x + TARGET_SIZEX + TARGET_SIZEX && m_pos.x >= CGame::GetTarget()->GetPos().x - TARGET_SIZEX - TARGET_SIZEX
			&& m_pos.z <= CGame::GetTarget()->GetPos().z + TARGET_SIZEY + TARGET_SIZEY && m_pos.z >= CGame::GetTarget()->GetPos().z - TARGET_SIZEY - TARGET_SIZEY)
		{// �^�[�Q�b�g�͈͓̔��ɓ�����
			if (CGame::GetTarget()->GetState() != SEPARATION_NONE)
			{// ���ʂ̐ݒ肪����Ă���
				CRockon::Create(m_pos, CTarget::GetState(), 0, 5);		// ���̈ʒu�Ƀ^�[�Q�b�g��ݒ�
				m_state = STATE_SEPARATION;								// ���ʏ�Ԃ�
				m_rockonType = CTarget::GetState();
			}
		}
		break;

	case STATE_ROCKON:			// ���b�N�I���\
		// �S�~����
		if (CManager::GetKeyboardInput()->GetPress(DIK_LEFT) == true
			|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_X, 0) == true)
		{// ���L�[�������ꂽ
			// �R����S�~
			CRockon::Create(m_pos, SEPARATION_BURN, 0, 5);			// ���̈ʒu�Ƀ^�[�Q�b�g��ݒ�
			m_rockonType = SEPARATION_BURN;
		}
		else if (CManager::GetKeyboardInput()->GetPress(DIK_UP) == true
			|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_Y, 0) == true)
		{// ��L�[�������ꂽ
			// �R���Ȃ��S�~
			CRockon::Create(m_pos, SEPARATION_NONFLAMMABLE, 0, 5);	// ���̈ʒu�Ƀ^�[�Q�b�g��ݒ�
			m_rockonType = SEPARATION_NONFLAMMABLE;
		}
		else if (CManager::GetKeyboardInput()->GetPress(DIK_RIGHT) == true
			|| CManager::GetInputGamePad()->GetPress(CInputGamePad::BUTTON_B, 0) == true)
		{// �E�L�[�������ꂽ
			// �v���X�`�b�N�S�~
			CRockon::Create(m_pos, SEPARATION_PLASTIC, 0, 5);		// ���̈ʒu�Ƀ^�[�Q�b�g��ݒ�
			m_rockonType = SEPARATION_PLASTIC;
		}

		if (m_pos.x >= CGame::GetTarget()->GetPos().x + TARGET_SIZEX + TARGET_SIZEX || m_pos.x <= CGame::GetTarget()->GetPos().x - TARGET_SIZEX - TARGET_SIZEX
			|| m_pos.z >= CGame::GetTarget()->GetPos().z + TARGET_SIZEY + TARGET_SIZEY || m_pos.z <= CGame::GetTarget()->GetPos().z - TARGET_SIZEY - TARGET_SIZEY)
		{// �^�[�Q�b�g�͈̔͊O�֊O�ꂽ
			m_state = STATE_NORMAL;		// �ʏ��Ԃɂ���
		}
		break;

	case STATE_SEPARATION:		// ����
		if ((m_rockonType == SEPARATION_BURN && (CManager::GetKeyboardInput()->GetRelease(DIK_LEFT) == true || CManager::GetInputGamePad()->GetRelease(CInputGamePad::BUTTON_X, 0) == true))
			|| (m_rockonType == SEPARATION_NONFLAMMABLE && (CManager::GetKeyboardInput()->GetRelease(DIK_UP) == true || CManager::GetInputGamePad()->GetRelease(CInputGamePad::BUTTON_Y, 0) == true))
			|| (m_rockonType == SEPARATION_PLASTIC && (CManager::GetKeyboardInput()->GetRelease(DIK_RIGHT) == true || CManager::GetInputGamePad()->GetRelease(CInputGamePad::BUTTON_B, 0) == true)))
		{// �L�[�𗣂���
			if (CGame::GetUiGage()->GetMax() == false)
			{// �S�~�Q�[�W���ő傶��Ȃ�
				m_posDest.y = DIFF_HEIGHT;		// �ړI�̍�����ݒ�
				m_state = STATE_DISPOSE;		// �̂Ă�
			}
			else
			{
				m_state = STATE_NORMAL;		// �ʏ��Ԃ֖߂�
			}
		}
		//// �v���C���[�̏�ň�莞�ԐÎ~������
		//m_pos = PlayerPos;
		//m_pos.y = DIFF_HEIGHT;

		//m_nWaitCounter--;	// ���Ԃ��f�N�������g

		//if (m_nWaitCounter <= 0)
		//{// �ݒ肵�����ԂɒB����
		//	m_state = STATE_COLLECT;		// ���ʏ�Ԃ�
		//}
		break;

	case STATE_DISPOSE:			// �̂Ă�
		m_fMoveDiff += MOVE_DIFF;	// �␳�W�������Z����

		// �ړI�̈ʒu��ݒ�
		m_posDest.x = PlayerPos.x;
		m_posDest.z = PlayerPos.z;

		m_posDiff = m_posDest - m_pos;	// �ړI�̈ʒu�܂ł̍���

		m_pos += m_posDiff * m_fMoveDiff;	// �ʒu�̕␳

		CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f), 20, 25, 3);

		if (m_pos.x <= m_posDest.x + DIFF_DISPOSE
			&& m_pos.x >= m_posDest.x - DIFF_DISPOSE
			&& m_pos.z <= m_posDest.z + DIFF_DISPOSE
			&& m_pos.z >= m_posDest.z - DIFF_DISPOSE)
		{// �ړI�̈ʒu�ɂȂ���
			m_state = STATE_COLLECT;		// ���
			m_nWaitCounter = WAIT_TIME;		// �Î~���Ă��鎞�Ԃ�ݒ�
			m_fMoveDiff = 0.0f;				// �␳�W����������
		}
		break;

	case STATE_COLLECT:			// ���
		m_pos.y -= GRAVITY_DISPOSE;		// �d�͂�t�^

		if (m_pos.y <= LAND_POS + 50.0f)
		{// �v���C���[�Ɋђ�
			// �p�[�e�B�N���̐���
			CParticle::Create(3)->Set(D3DXVECTOR3(m_pos.x - sinf(D3DX_PI * ROT_UP + (1.0f * m_rot.y) * 5.0f), m_pos.y, 
				m_pos.z - cosf(D3DX_PI * ROT_UP + (1.0f * m_rot.y) * 5.0f)), particleType);

			// �ݒ菈��
			CGame::GetUiGage()->Set(AMOUNT_OF_RISE);

			Separation(m_rockonType);		// ���ʏ����i�X�R�A�ɉ��Z�����j

			m_state = STATE_INPLAYER;		// �`�悵�Ȃ���Ԃɂ���
		}
		break;

	case STATE_INPLAYER:		// �`�悵�Ȃ�
		m_pos = CGame::GetPlayer()->GetPos();	// �S�~�̈ʒu���v���C���[�Ɠ���������

		for (int nCntDumpster = 0; nCntDumpster < MAX_DUMPSTER; nCntDumpster++)
		{
			if (CGame::GetDumpster(nCntDumpster)->GetPos().x <= m_pos.x + DUMPSTER_LENTH && CGame::GetDumpster(nCntDumpster)->GetPos().x >= m_pos.x - DUMPSTER_LENTH
				&& CGame::GetDumpster(nCntDumpster)->GetPos().z <= m_pos.z + DUMPSTER_LENTH && CGame::GetDumpster(nCntDumpster)->GetPos().z >= m_pos.z - DUMPSTER_LENTH)
			{// �^�[�Q�b�g���S�~�X�e�[�V�����𗘗p�ł���͈͓��ɓ�����
				if (CManager::GetKeyboardInput()->GetTrigger(DIK_SPACE) == true
					|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true)
				{// SPACE�L�[�������ꂽ
					m_posDest.y = DIFF_HEIGHT;		// �ړI�̍�����ݒ�
					m_nIdxDumpster = nCntDumpster;	// �S�~�X�e�[�V�����̔ԍ���ۑ�

					m_state = STATE_DUMPSTER;		// �S�~�X�e�[�V����
				}
			}
		}
		break;

	case STATE_DUMPSTER:		// �S�~�X�e�[�V����
		m_fMoveDiff += MOVE_DIFF;	// �␳�W�������Z����

		// �ړI�̈ʒu��ݒ�
		m_posDest.x = CGame::GetDumpster(m_nIdxDumpster)->GetPos().x;
		m_posDest.z = CGame::GetDumpster(m_nIdxDumpster)->GetPos().z;

		m_posDiff = m_posDest - m_pos;	// �ړI�̈ʒu�܂ł̍���

		m_pos += m_posDiff * m_fMoveDiff;	// �ʒu�̕␳

		// �G�t�F�N�g�̐���
		CEffect::Create(m_pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXCOLOR(0.0f, 1.0f, 0.2f, 1.0f), 20, 25, 3);

		if (m_pos.x <= m_posDest.x + DIFF_DISPOSE
			&& m_pos.x >= m_posDest.x - DIFF_DISPOSE
			&& m_pos.z <= m_posDest.z + DIFF_DISPOSE
			&& m_pos.z >= m_posDest.z - DIFF_DISPOSE)
		{// �ړI�̈ʒu�ɂȂ���
			m_state = STATE_DELETE;			// �j��
		}
		break;

	case STATE_DELETE:			// �j��
		m_pos.y -= GRAVITY_DISPOSE;		// �d�͂�t�^

		if (m_pos.y <= LAND_POS + 50.0f)
		{// �v���C���[�Ɋђ�
			// �p�[�e�B�N���̐���
			CParticle::Create(1)->Set(D3DXVECTOR3(m_pos.x - sinf(D3DX_PI * ROT_UP + (1.0f * m_rot.y) * 5.0f), m_pos.y,
				m_pos.z - cosf(D3DX_PI * ROT_UP + (1.0f * m_rot.y) * 5.0f)), particleType);

			CGame::GetScore()->Add(ADD_SCORE);		// �X�R�A���Z

			// �ݒ菈��
			CGame::GetUiGage()->Set(-1.0f);

			// �I������
			Uninit(); 
		}
		break;
	}
}

//===============================================
// �`�揈��
//===============================================
void CGarbage::Draw(void)
{
	if (m_state != STATE_INPLAYER)
	{// �`�悵�Ȃ���Ԃ���Ȃ�
		if (m_state == STATE_ROCKON)
		{// ���b�N�I���\���
			// �I�u�W�F�N�gX�̕`�揈���i�ԁj
			CObjectX::DrawXFile(m_aIdxXFile[m_type], CXFile::COL_RED);
		}
		else
		{// ����ȊO
			// ���ʂ̎�ޕʂɐF��ς���
			switch (m_separation)
			{
			case SEPARATION_BURN:			// �R����S�~
				// �I�u�W�F�N�gX�̕`�揈���i���j
				CObjectX::DrawXFile(m_aIdxXFile[m_type], CXFile::COL_YELLOW);
				break;

			case SEPARATION_NONFLAMMABLE:	// �R���Ȃ��S�~
				// �I�u�W�F�N�gX�̕`�揈���i�΁j
				CObjectX::DrawXFile(m_aIdxXFile[m_type], CXFile::COL_GREEN);
				break;

			case SEPARATION_PLASTIC:		// �v���X�`�b�N�S�~
				// �I�u�W�F�N�gX�̕`�揈���i�j
				CObjectX::DrawXFile(m_aIdxXFile[m_type], CXFile::COL_BLUE);
				break;

			default:						// ����ȊO
				// �I�u�W�F�N�gX�̕`�揈��
				CObjectX::DrawXFile(m_aIdxXFile[m_type], CXFile::COL_NORMAL);
				break;
			}
		}
	}
}

//===============================================
// ���ʏ���
//===============================================
void CGarbage::Separation(SEPARATION separation)
{
	m_rockonType = separation;	// ���b�N�I�����̕��ʂ̎��

	if (m_separation == separation)
	{// �ݒ肳�ꂽ���ʂ̎�ނƓ��͂������ʂ̎�ނ���v
		CManager::GetDebugProc()->Print(" ����");
		CGame::GetScore()->Add(ADD_SCORE);		// �X�R�A���Z
	}
	else
	{// �s��v
		CManager::GetDebugProc()->Print(" �s����");
		CGame::GetScore()->Add(SUB_SCORE);		// �X�R�A���Z
	}
}
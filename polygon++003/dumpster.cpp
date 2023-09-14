//=========================================================
//
// �S�~�X�e�[�V�������� [dumpster.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "dumpster.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "xfile.h"
#include "game.h"
#include "target.h"
#include "tutorial.h"
#include "player.h"

//===============================================
// �}�N����`
//===============================================
#define DELETE_POSITION			(550.0f)	// ����j������ʒu

//===============================================
// �ÓI�����o�ϐ�
//===============================================
int CDumpster::m_nIdxXFile = 0;			// �g�p����X�t�@�C���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CDumpster::CDumpster() : CObjectX(4)
{
	// �l�̃N���A
	m_bRockon = false;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CDumpster::CDumpster(int nPriority) : CObjectX(nPriority)
{
	// �l�̃N���A
	m_bRockon = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CDumpster::~CDumpster()
{
	
}

//===============================================
// ���f���̐����i�ǂݍ��݁j
//===============================================
HRESULT CDumpster::Load(void)
{
	// �w�t�@�C���ɓǂݍ���
	m_nIdxXFile = CManager::GetXFile()->Regist("data\\MODEL\\Dumpster001.x");

	return S_OK;
}

//===============================================
// ���f���̔j��
//===============================================
void CDumpster::Unload(void)
{
	
}

//===============================================
// ��������
//===============================================
CDumpster *CDumpster::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority)
{
	CDumpster *pGarbage = NULL;

	// �S�~�̐���
	pGarbage = new CDumpster(nPriority);

	// ��ނ̐ݒ�
	pGarbage->SetType(CObject::TYPE_DUMPSTER);

	// ����������
	pGarbage->Init(pos);

	// �����̐ݒ�
	pGarbage->SetRot(rot);

	return pGarbage;
}

//===============================================
// ����������
//===============================================
HRESULT CDumpster::Init(D3DXVECTOR3 pos)
{
	// �I�u�W�F�N�gX�̏���������
	CObjectX::Init(pos);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CDumpster::Uninit(void)
{
	// �I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//===============================================
// �X�V����
//===============================================
void CDumpster::Update(void)
{
	// �O��̈ʒu��ۑ�
	m_posOld = m_pos;

	if (CManager::GetMode() == CScene::MODE_TUTORIAL 
		&& (m_pos.x <= CTutorial::GetTarget()->GetPos().x + DUMPSTER_LENTH && m_pos.x >= CTutorial::GetTarget()->GetPos().x - DUMPSTER_LENTH
		&& m_pos.z <= CTutorial::GetTarget()->GetPos().z + DUMPSTER_LENTH && m_pos.z >= CTutorial::GetTarget()->GetPos().z - DUMPSTER_LENTH)
		|| CManager::GetMode() == CScene::MODE_GAME 
		&& (m_pos.x <= CGame::GetTarget()->GetPos().x + DUMPSTER_LENTH && m_pos.x >= CGame::GetTarget()->GetPos().x - DUMPSTER_LENTH
		&& m_pos.z <= CGame::GetTarget()->GetPos().z + DUMPSTER_LENTH && m_pos.z >= CGame::GetTarget()->GetPos().z - DUMPSTER_LENTH))
	{// �^�[�Q�b�g���S�~�X�e�[�V�����𗘗p�ł���͈͓��ɓ�����
		m_bRockon = true;	// �^�[�Q�b�g�͈͓̔��֐؂�ւ���
	}
	else
	{
		m_bRockon = false;	// �^�[�Q�b�g�͈̔͊O�֐؂�ւ���
	}

	if (CManager::GetMode() == CScene::MODE_TUTORIAL)
	{
		if (CTutorial::GetPlayer()->GetPos().z < m_pos.z - DELETE_POSITION)
		{// ��ʊO�ւ�����
			// �I������
			Uninit();
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CDumpster::Draw(void)
{
	if (m_bRockon == true)
	{// �^�[�Q�b�g�͈͓̔�
		// �I�u�W�F�N�gX�̕`�揈���i�ΐF�j
		CObjectX::DrawXFile(m_nIdxXFile, CXFile::COL_GREEN);
	}
	else
	{// �^�[�Q�b�g�͈̔͊O
		// �I�u�W�F�N�gX�̕`�揈���i�ʏ�F�j
		CObjectX::DrawXFile(m_nIdxXFile, CXFile::COL_NORMAL);
	}
}
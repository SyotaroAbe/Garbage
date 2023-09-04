//=========================================================
//
// �`���[�g���A����ʏ��� [tutorial.cpp]
// Author = �����đ�Y
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
// �ÓI�����o�ϐ�
//===============================================
CPlayer *CTutorial::m_pPlayer = NULL;					// �v���C���[�N���X�̃|�C���^
CNumber *CTutorial::m_pNumber = NULL;					// �i���o�[�N���X�̃|�C���^
CScore *CTutorial::m_pScore = NULL;						// �X�R�A�N���X�̃|�C���^
CGarbage *CTutorial::m_pGarbage = NULL;					// �S�~�N���X�̃|�C���^
CMeshField *CTutorial::m_pMeshField = NULL;				// ���b�V���t�B�[���h�N���X�̃|�C���^
CTarget *CTutorial::m_pTarget = NULL;					// �^�[�Q�b�g�N���X�̃|�C���^
CDumpster *CTutorial::m_pDumpster = NULL;				// �S�~�X�e�[�V�����N���X�̃|�C���^
CUiGage *CTutorial::m_pUiGage = NULL;					// �S�~�Q�[�W�N���X�̃|�C���^
CUiTarget *CTutorial::m_pUiTarget = NULL;				// �^�[�Q�b�gUI�N���X�̃|�C���^
CFileLoad *CTutorial::m_pFileLoad = NULL;				// ���[�h�N���X�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CTutorial::CTutorial() : CScene()
{
	// �l�̃N���A
	m_bFade = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTutorial::~CTutorial()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CTutorial::Init(HWND hWnd)
{
	// ���[�h�̐���
	m_pFileLoad = new CFileLoad;

	if (m_pFileLoad != NULL)
	{// �g�p����Ă���
	 // ���[�h�̓ǂݍ��ݏ���
		if (FAILED(m_pFileLoad->Init(hWnd)))
		{// �ǂݍ��ݏ��������s�����ꍇ
			return -1;
		}
	}

	// �J�����̏���������
	CManager::GetCamera()->Init();

	// ���b�V���t�B�[���h�̐���
	CMeshField::load(hWnd);

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);

	// ���݂̐���
	CGarbage::Load();

	// �S�~�X�e�[�V�����̓ǂݍ��݂Ɛ���
	CDumpster::Load();
	m_pDumpster = CDumpster::Create(D3DXVECTOR3(300.0f, 0.0f, -200.0f), 2);

	// �^�[�Q�b�g�̐���
	m_pTarget = CTarget::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), CGarbage::SEPARATION_NONE, -1, 5);

	// �^�[�Q�b�gUI�̐���
	m_pUiTarget = CUiTarget::Create(5);

	// �X�R�A�̐���
	m_pScore = CScore::Create(6);

	// �S�~�Q�[�W�̐���
	m_pUiGage = CUiGage::Create(6);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTutorial::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		// �t�@�C���ǂݍ��݂̏I������
		m_pFileLoad->Uninit();
		delete m_pFileLoad;
		m_pFileLoad = NULL;
	}

	if (m_pScore != NULL)
	{
		// �X�R�A�̏I������
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = NULL;
	}

	if (m_pUiGage != NULL)
	{
		// �S�~�Q�[�W�̏I������
		delete m_pUiGage;
		m_pUiGage = NULL;
	}

	if (m_pUiTarget != NULL)
	{
		// �^�[�Q�b�gUI�̏I������
		delete m_pUiTarget;
		m_pUiTarget = NULL;
	}

	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//===============================================
// �X�V����
//===============================================
void CTutorial::Update(void)
{
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true)
	{
		if (m_bFade == false)
		{// �t�F�[�h�o�O�h�~
			CRenderer::GetFade()->Set(CScene::MODE_GAME);	// �Q�[����ʂֈڍs
			m_bFade = true;
		}
	}

	if (m_pScore != NULL)
	{
		// �X�R�A�̍X�V����
		m_pScore->Update();
	}

	if (m_pUiGage != NULL)
	{
		// �S�~�Q�[�W�̍X�V����
		m_pUiGage->Update();
	}

	if (m_pUiTarget != NULL)
	{
		// �^�[�Q�b�gUI�̍X�V����
		m_pUiTarget->Update();
	}
}

//===============================================
// �`�揈��
//===============================================
void CTutorial::Draw(void)
{
	if (m_pScore != NULL)
	{
		// �X�R�A�̕`�揈��
		m_pScore->Draw();
	}

	if (m_pUiGage != NULL)
	{
		// �S�~�Q�[�W�̕`�揈��
		m_pUiGage->Draw();
	}
}
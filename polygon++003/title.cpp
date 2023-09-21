//=========================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author = �����đ�Y
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
#include "fileload.h"
#include "camera.h"
#include "garbage.h"
#include "player.h"
#include "logo.h"
#include "pressenter.h"

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CPlayer *CTitle::m_pPlayer = NULL;				// �v���C���[�N���X�̃|�C���^
CBg *CTitle::m_pBg = NULL;						// �w�i�N���X�̃|�C���^
CFileLoad *CTitle::m_pFileLoad = NULL;			// ���[�h�N���X�̃|�C���^
CLogo *CTitle::m_pLogo = NULL;					// �^�C�g�����S�`��N���X�̃|�C���^
CPressEnter *CTitle::m_pPressEnter = NULL;		// PressEnter�`��N���X�̃|�C���^

//===============================================
// �R���X�g���N�^
//===============================================
CTitle::CTitle() : CScene()
{
	// �l�̃N���A
	m_bFade = false;
}

//===============================================
// �f�X�g���N�^
//===============================================
CTitle::~CTitle()
{
	
}

//===============================================
// ����������
//===============================================
HRESULT CTitle::Init(HWND hWnd)
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

	//// �w�i�̐���
	//m_pBg = CBg::Create(CBg::TYPE_TITLE, 6);

	// ���b�V���t�B�[���h�̐���
	CMeshField::load(hWnd);

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 4);

	// ���݂̐���
	CGarbage::Load();

	// �^�C�g�����S�̐���
	m_pLogo = CLogo::Create();

	// PressEnter�̐���
	m_pPressEnter = CPressEnter::Create();

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	if (m_pFileLoad != NULL)
	{
		// �t�@�C���ǂݍ��݂̏I������
		m_pFileLoad->Uninit();
		delete m_pFileLoad;
		m_pFileLoad = NULL;
	}

	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	if (m_pLogo->GetEndAnim() == true && (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true))
	{
		if (m_bFade == false)
		{// �t�F�[�h�o�O�h�~
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// �Q�[����ʂֈڍs
			m_bFade = true;

			// �_�Őݒ�
			m_pPressEnter->SetBrightnessFade(true);

			// �T�E���h�̍Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_ENTER);
		}
	}
}

//===============================================
// �`�揈��
//===============================================
void CTitle::Draw(void)
{
	
}
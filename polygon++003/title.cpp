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

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CBg *CTitle::m_pBg = NULL;						// �w�i�N���X�̃|�C���^

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
	// �w�i�̐���
	m_pBg = CBg::Create(CBg::TYPE_TITLE, 6);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CTitle::Uninit(void)
{
	// �S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();
}

//===============================================
// �X�V����
//===============================================
void CTitle::Update(void)
{
	if (CManager::GetKeyboardInput()->GetTrigger(DIK_RETURN) == true
		|| CManager::GetInputGamePad()->GetTrigger(CInputGamePad::BUTTON_A, 0) == true)
	{
		if (m_bFade == false)
		{// �t�F�[�h�o�O�h�~
			CRenderer::GetFade()->Set(CScene::MODE_TUTORIAL);	// �Q�[����ʂֈڍs
			m_bFade = true;

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
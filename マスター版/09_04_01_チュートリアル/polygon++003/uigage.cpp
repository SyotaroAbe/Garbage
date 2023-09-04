//=========================================================
//
// �S�~�Q�[�W���� [uigage.cpp]
// Author = �����đ�Y
//
//=========================================================
#include "uigage.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"
#include "object2D.h"
#include "input.h"

//===============================================
// �}�N����`
//===============================================
#define SIZE_X			(100.0f)			// ���T�C�Y
#define SIZE_Y			(100.0f)			// �c�T�C�Y
#define MAX_GARBAGE		(1.0f)				// �ő�S�~��

//===============================================
// �ÓI�����o�ϐ�
//===============================================
CObject2D *CUiGage::m_apObject2D[TEX_MAX];				// �I�u�W�F�N�g2D�N���X�̃|�C���^
const char *CUiGage::m_apTextureData[TEX_MAX] = {};		// �e�N�X�`���t�@�C����
int CUiGage::m_aIdxTexture[TEX_MAX] = {};				// �g�p����e�N�X�`���̔ԍ�

//===============================================
// �R���X�g���N�^
//===============================================
CUiGage::CUiGage()
{
	// �l�̃N���A
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_fGarbage = 0.0f;
}

//===============================================
// �R���X�g���N�^�i�I�[�o�[���[�h�j
//===============================================
CUiGage::CUiGage(int nPriority)
{
	// �l�̃N���A
	m_fTexU = 0.0f;
	m_fTexV = 0.0f;
	m_fGarbage = 0.0f;
}

//===============================================
// �f�X�g���N�^
//===============================================
CUiGage::~CUiGage()
{
	
}

//===============================================
// ��������
//===============================================
CUiGage *CUiGage::Create(int nIdx, int nPriority)
{
	CUiGage *pUi;

	// �w�i�̐���
	pUi = new CUiGage(nPriority);

	// ����������
	pUi->Init(D3DXVECTOR3(150.0f, 600.0f, 0.0f), nPriority);

	return pUi;
}

//===============================================
// ����������
//===============================================
HRESULT CUiGage::Init(D3DXVECTOR3 pos, int nPriority)
{
	// �e�N�X�`���t�@�C����
	const char *m_apTextureData[TEX_MAX] =
	{
		{ "data\\TEXTURE\\gage002.png" },	// �O��
		{ "data\\TEXTURE\\gage001.png" }	// ����
	};

	for (int nCntObj = 0; nCntObj < TEX_MAX; nCntObj++)
	{
		m_apObject2D[nCntObj] = new CObject2D(nPriority);

		m_apObject2D[nCntObj]->SetSize(SIZE_X, SIZE_Y);

		// �I�u�W�F�N�g2D�̏���������
		m_apObject2D[nCntObj]->Init(pos);

		// �e�N�X�`���̐ݒ�
		m_aIdxTexture[nCntObj] = CManager::GetTexture()->Regist(m_apTextureData[nCntObj]);

		// �e�N�X�`���̊��蓖��
		m_apObject2D[nCntObj]->BindTexture(m_aIdxTexture[nCntObj]);
	}

	// �e�N�X�`�����W�̍X�V����
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f);

	return S_OK;
}

//===============================================
// �I������
//===============================================
void CUiGage::Uninit(void)
{
	
}

//===============================================
// �X�V����
//===============================================
void CUiGage::Update(void)
{
#if _DEBUG
	if (CManager::GetKeyboardInput()->GetPress(DIK_1) == true)
	{// 1�L�[
		// �ݒ菈��
		Set(AMOUNT_OF_RISE);
	}
	else if (CManager::GetKeyboardInput()->GetPress(DIK_2) == true)
	{// 2�L�[
		// �ݒ菈��
		Set(-MAX_GARBAGE);
	}
#endif
}

//===============================================
// �`�揈��
//===============================================
void CUiGage::Draw(void)
{
	if (m_fGarbage == MAX_GARBAGE)
	{// �S�~�̗ʂ��ő�
		// �F�̍X�V�����i�ԁj
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
	else
	{
		// �F�̍X�V�����i���j
		m_apObject2D[TEX_INSIDE]->SetCol(D3DXCOLOR(m_fGarbage, 1.0f - m_fGarbage * 0.5f, 1.0f - m_fGarbage, 1.0f));
	}
}

//===============================================
// �ݒ菈��
//===============================================
void CUiGage::Set(float fGarbage)
{
	m_fGarbage += fGarbage;

	if (m_fGarbage > MAX_GARBAGE)
	{// �ő�ʂ𒴂���
		m_fGarbage = MAX_GARBAGE;
	}
	else if (m_fGarbage < 0.0f)
	{// �ŏ��ʂ𒴂���
		m_fGarbage = 0.0f;
	}

	// �ʒu�̍X�V����
	m_apObject2D[TEX_INSIDE]->UpdatePos(D3DXVECTOR3(150.0f, 700.0f - m_fGarbage * SIZE_Y, 0.0f), SIZE_X, m_fGarbage * SIZE_Y);

	// �e�N�X�`�����W�̍X�V����
	m_apObject2D[TEX_INSIDE]->UpdateTex(0.0f, 0.0f, 1.0f, 1.0f, m_fGarbage, 0.0f);
}

//===============================================
// �Q�[�W���ő�ł��邩�擾����
//===============================================
bool CUiGage::GetMax(void)
{
	if (m_fGarbage >= MAX_GARBAGE)
	{// �ő�ʂ𒴂���
		return true;
	}

	return false;
}
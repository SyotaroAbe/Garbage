//=========================================================
//
// �S�~�Q�[�W���� [uigage.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _UIGAGE_H_     // ���̃}�N����`������ĂȂ�������
#define _UIGAGE_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "main.h"
#include "object.h"

//===============================================
// �O���錾
//===============================================
class CObject2D;

//===============================================
// �}�N����`
//===============================================
#define AMOUNT_OF_RISE	(0.05f)				// �Q�[�W�㏸��
#define MAX_GARBAGE		(1.0f)				// �ő�S�~��

//===============================================
// �S�~�Q�[�W�N���X
//===============================================
class CUiGage
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CUiGage();						// �f�t�H���g�R���X�g���N�^
	CUiGage(int nPriority = 5);		// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CUiGage();						// �f�X�g���N�^

	enum TEX
	{
		TEX_OUTSIDE = 0,	// �O��
		TEX_INSIDE,			// ����
		TEX_MAX
	};

	static CUiGage *Create(int nIdx, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos, int nPriority);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Set(float fGarbage);
	float Get(void) { return m_fGarbage; }
	bool GetMax(void);

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static CObject2D *m_apObject2D[TEX_MAX];		// �I�u�W�F�N�g2D�N���X�̃|�C���^
	static const char *m_apTextureData[TEX_MAX];	// �e�N�X�`���t�@�C����
	static int m_aIdxTexture[TEX_MAX];				// �g�p����e�N�X�`���̔ԍ�

	float m_fTexU;									// �e�N�X�`�����W�̊J�n�ʒu�iU�l�j
	float m_fTexV;									// �e�N�X�`�����W�̊J�n�ʒu�iV�l�j
	float m_fGarbage;								// �S�~�̗�
	float m_fMoveShake;								// �k���铮���̈ړ���
	bool m_bVMoveShake;								// �k���铮���̌���
};

#endif
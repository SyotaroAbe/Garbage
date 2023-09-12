//=========================================================
//
// �^�[�Q�b�g���� [target.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _TARGET_H_     // ���̃}�N����`������ĂȂ�������
#define _TARGET_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "main.h"
#include "object2D.h"
#include "objectBillboard.h"
#include "garbage.h"

//===============================================
// �}�N����`
//===============================================
#define MAX_TARGET		(256)			// �^�[�Q�b�g�̍ő吔
#define TARGET_SIZEX	(45.0f)			// ���i�����j
#define TARGET_SIZEY	(45.0f)			// �����i�����j

//===============================================
// �^�[�Q�b�g�N���X
//===============================================
class CTarget : public CObjectBillboard
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CTarget();						// �f�t�H���g�R���X�g���N�^
	CTarget(int nPriority = 2);		// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CTarget();						// �f�X�g���N�^

	// �^�[�Q�b�g�̏��
	typedef enum
	{
		STATE_NONE = 0,		// �Ȃ�
		STATE_ROCKON,		// ���b�N�I��
		STATE_MAX
	}STATE;

	static CTarget *Create(D3DXVECTOR3 pos, CGarbage::SEPARATION state, int nID, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Set(const D3DXVECTOR3 pos, const D3DXVECTOR3 move);

	void SetState(CGarbage::SEPARATION state);
	static CGarbage::SEPARATION GetState(void) { return m_state; }
	bool GetWithinRange(void) { return m_bWithinRange; }
	bool WithinRangeGarbage(void);

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static int m_nIdxTexture;					// �g�p����e�N�X�`���̔ԍ�
	static int m_nCntObjTarget[MAX_TARGET];		// �^�[�Q�b�g���Ă���I�u�W�F�N�g�̔ԍ��ۑ�
	static CGarbage::SEPARATION m_state;		// �^�[�Q�b�g�̏��

	D3DXVECTOR3 m_LocalPos;				// �����ʒu���猩�Ă̋���
	bool m_bWithinRange;				// �S�~���^�[�Q�b�g�͈͓̔�
	float m_fMaltiRivision;				// �ʒu�␳�l
};

#endif
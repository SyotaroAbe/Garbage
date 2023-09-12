//=========================================================
//
// �S�~�X�e�[�V�������� [dumpster.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _DUMPSTER_H_     // ���̃}�N����`������ĂȂ�������
#define _DUMPSTER_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "objectX.h"

//===============================================
// �}�N����`
//===============================================
#define MAX_DUMPSTER			(3)			// �ő�S�~�X�e�[�V�����z�u��
#define DUMPSTER_LENTH			(2500.0f)	// �S�~������ł���͈�

//===============================================
// �S�~�X�e�[�V�����N���X
//===============================================
class CDumpster : public CObjectX
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CDumpster();					// �f�t�H���g�R���X�g���N�^
	CDumpster(int nPriority = 3);	// �I�[�o�[���[�h���ꂽ�R���X�g���N�^
	~CDumpster();					// �f�X�g���N�^

	static HRESULT Load(void);
	static void Unload(void);
	static CDumpster *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nPriority = 3);

	HRESULT Init(D3DXVECTOR3 pos);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static int m_nIdxXFile;					// �g�p����X�t�@�C���̔ԍ�
	bool m_bRockon;							// �^�[�Q�b�g�͈͓̔����ǂ���
};

#endif
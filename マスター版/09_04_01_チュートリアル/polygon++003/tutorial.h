//=========================================================
//
// �`���[�g���A����ʏ��� [tutorial.h]
// Author = �����đ�Y
//
//=========================================================
#ifndef _TUTORIAL_H_     // ���̃}�N����`������ĂȂ�������
#define _TUTORIAL_H_     // 2�d�C���N���[�h�h�~�̃}�N����`����

#include "manager.h"

//===============================================
// �O���錾
//===============================================
class CPlayer;
class CNumber;
class CScore;
class CMeshField;
class CTarget;
class CDumpster;
class CUiGage;
class CUiTarget;
class CFileLoad;

//===============================================
// �`���[�g���A����ʃN���X
//===============================================
class CTutorial : public CScene
{
public:		// �N�ł��A�N�Z�X�\ [�A�N�Z�X�w��q]
	CTutorial();						// �f�t�H���g�R���X�g���N�^
	~CTutorial();						// �f�X�g���N�^

	HRESULT Init(HWND hWnd);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static CPlayer *GetPlayer() { return m_pPlayer; }
	static CNumber *GetNumber() { return m_pNumber; }
	static CScore *GetScore() { return m_pScore; }
	static CGarbage *GetGarbage() { return m_pGarbage; }
	static CMeshField *GetMeshField() { return m_pMeshField; }
	static CFileLoad *GetLoad() { return m_pFileLoad; }
	static CTarget *GetTarget() { return m_pTarget; }
	static CDumpster *GetDumpster(int nIdx) { return m_pDumpster; }
	static CUiGage *GetUiGage() { return m_pUiGage; }
	static CUiTarget *GetUiTarget() { return m_pUiTarget; }

private:	// �����̂݃A�N�Z�X�\ [�A�N�Z�X�w��q]
	static CPlayer *m_pPlayer;						// �v���C���[�N���X�̃|�C���^
	static CNumber *m_pNumber;						// �i���o�[�N���X�̃|�C���^
	static CScore *m_pScore;						// �X�R�A�N���X�̃|�C���^
	static CGarbage *m_pGarbage;					// �S�~�N���X�̃|�C���^
	static CMeshField *m_pMeshField;				// ���b�V���t�B�[���h�N���X�̃|�C���^
	static CFileLoad *m_pFileLoad;					// ���[�h�N���X�̃|�C���^
	static CTarget *m_pTarget;						// �^�[�Q�b�g�N���X�̃|�C���^
	static CDumpster *m_pDumpster;					// �S�~�X�e�[�V�����N���X�̃|�C���^
	static CUiGage *m_pUiGage;						// �S�~�Q�[�W�N���X�̃|�C���^
	static CUiTarget *m_pUiTarget;					// �^�[�Q�b�gUI�N���X�̃|�C���^

	bool m_bFade;		// �t�F�[�h�ɓ�������
};

#endif
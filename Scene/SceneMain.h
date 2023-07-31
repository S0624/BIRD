#pragma once
#include "SceneBase.h"

// �N���X�̐錾
class Player;
class Map;
class BackGround;
class Camera;
class GameObject;

// �V�[���x�[�X�N���X���p�����ăV�[�����쐬����
class SceneMain :
	public SceneBase
{
public:
	// �R���X�g���N�^
	SceneMain();
	// �f�X�g���N�^
	virtual ~SceneMain();

	// ������
	virtual void Init();
	// �G���h����
	virtual void End();
	// �X�V����
	virtual SceneBase* Update() override;
	// �`�揈��
	virtual void Draw();

	bool Timer();
private:
	Player* m_pPlayer;	// �v���C���[�̃|�C���^
	Map* m_pMap;		// �}�b�v�̃|�C���^
	BackGround* m_pBack;// �w�i�̃|�C���^
	Camera* m_pCamera;	// �J�����̃|�C���^

	int m_gamefont;		// �J�E���g�_�E���ȂǂɎg�p����t�H���g
	int m_guidefont;	// ���̃K�C�h�Ɏg�p����t�H���g

	int m_teimer;		// �^�C�}�[(�n�܂�O�̃J�E���g�_�E���Ɏg�p)

	// TODO �V���h�E�}�b�v��t���悤�Ƃ��Ăł��Ȃ������̂ł��ƂŒǉ�����
	int	m_shadowMap;	// �V���h�E�}�b�v(�e)�̂��߂̕ϐ�
};


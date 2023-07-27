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

private:
	Player* m_pPlayer;	// �v���C���[�̃|�C���^
	Map* m_pMap;		// �}�b�v�̃|�C���^
	BackGround* m_pBack;// �w�i�̃|�C���^
	Camera* m_pCamera;	// �J�����̃|�C���^

	// HaCK
	int	m_shadowMap;	// �V���h�E�}�b�v(�e)�̂��߂̕ϐ�
};


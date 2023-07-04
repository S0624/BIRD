#include"../Common.h"
#include "SceneMain.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Map.h"
#include"../Object/BackGround.h"

SceneMain::SceneMain()
{
	m_pPlayer = new Player();
	m_pMap = new Map();
	m_pMap->Load();
	m_pBack = new BackGround();

	m_pCamera = new Camera();
}

SceneMain::~SceneMain()
{
	// ���낢��폜
	delete(m_pPlayer);
	delete(m_pMap);
	delete(m_pBack);
	delete(m_pCamera);
}

void SceneMain::Init()
{
	m_isFadeOut = IsFadingOut();
}

void SceneMain::End()
{
	
}

SceneBase* SceneMain::Update()
{	
	//m_pBack->Update();
	m_pCamera->Update(*m_pPlayer);// �J�����̏�����

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			//return (new SceneMain);
		}
	}

	//// �t�F�[�h�C���A�E�g���Ă��Ȃ�
	//if (!IsFading())
	//{
	//	// �t�F�[�h�A�E�g�J�n
	//	if (Pad::IsTrigger(PAD_INPUT_1))
	//	{
	//		StartFadeOut();
	//	}
	//}

	m_pPlayer->Update();// �v���C���[�̃A�b�v�f�[�g
	m_pMap->Update();// �}�b�v�̃A�b�v�f�[�g

	return this;
}

void SceneMain::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kWhite, true);

	m_pPlayer->Draw();// �v���C���[�̕\��
	m_pMap->Draw();// �X�e�[�W�̕\��
	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
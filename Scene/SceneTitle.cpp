#include"../Common.h"
#include "SceneTitle.h"
#include"SceneMain.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"

SceneTitle::SceneTitle()
{
	//m_pPlayer = new Player();
	//m_pCamera = new Camera();
}

SceneTitle::~SceneTitle()
{
	//delete(m_pPlayer);
}

void SceneTitle::Init()
{
	m_isFadeOut = IsFadingOut();
}

void SceneTitle::End()
{
	
}

SceneBase* SceneTitle::Update()
{
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain);
		}
	}

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (!IsFading())
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}
	}
	//m_pPlayer->Update();
	//m_pCamera->Update(*m_pPlayer);

	return this;
}

void SceneTitle::Draw()
{
	// ���w�i
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	//m_pPlayer->Draw();
	DrawString(200, 200, "�^�C�g��", Color::kWhite);

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
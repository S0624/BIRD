#include"../Common.h"
#include "SceneTitle.h"
#include"SceneMain.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"

SceneTitle::SceneTitle()
{

}

SceneTitle::~SceneTitle()
{
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

	return this;
}

void SceneTitle::Draw()
{
	DrawString(200, 200, "�^�C�g��", Color::kWhite);

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
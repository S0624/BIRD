#include "SceneResult.h"
#include"../Common.h"
#include "SceneTitle.h"

SceneResult::SceneResult()
{

}

SceneResult::~SceneResult()
{
}

void SceneResult::Init()
{
	m_isFadeOut = IsFadingOut();
}

void SceneResult::End()
{

}

SceneBase* SceneResult::Update()
{
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneTitle);
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

void SceneResult::Draw()
{
	DrawString(200, 200, "result", Color::kWhite);

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
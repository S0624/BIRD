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
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneTitle);
		}
	}

	// フェードインアウトしていなかったら
	if (!IsFading())
	{
		// フェードアウト開始
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

	// フェードの表示
	SceneBase::DrawFade();
}
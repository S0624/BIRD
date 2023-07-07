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
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain);
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

void SceneTitle::Draw()
{
	DrawString(200, 200, "タイトル", Color::kWhite);

	// フェードの表示
	SceneBase::DrawFade();
}
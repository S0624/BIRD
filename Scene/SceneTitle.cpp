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
	//m_pPlayer->Update();
	//m_pCamera->Update(*m_pPlayer);

	return this;
}

void SceneTitle::Draw()
{
	// 仮背景
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0xffffff, true);
	//m_pPlayer->Draw();
	DrawString(200, 200, "タイトル", Color::kWhite);

	// フェードの表示
	SceneBase::DrawFade();
}
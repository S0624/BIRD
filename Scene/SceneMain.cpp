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
	// いろいろ削除
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
	m_pCamera->Update(*m_pPlayer);// カメラの初期化

	// フェードインアウトしていなかったら
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			//return (new SceneMain);
		}
	}

	//// フェードインアウトしていない
	//if (!IsFading())
	//{
	//	// フェードアウト開始
	//	if (Pad::IsTrigger(PAD_INPUT_1))
	//	{
	//		StartFadeOut();
	//	}
	//}

	m_pPlayer->Update();// プレイヤーのアップデート
	m_pMap->Update();// マップのアップデート

	return this;
}

void SceneMain::Draw()
{
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kWhite, true);

	m_pPlayer->Draw();// プレイヤーの表示
	m_pMap->Draw();// ステージの表示
	// フェードの表示
	SceneBase::DrawFade();
}
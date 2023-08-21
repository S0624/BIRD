#include<cassert>
#include "SceneManager.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"../Common.h"
#include "../Util/SoundManager.h"

SceneManager::SceneManager() :
	m_pScene(nullptr)
{
}
// 初期化
bool SceneManager::Init()
{
	// windowモード設定
	ChangeWindowMode(Game::kWindowMode);

	// ウインドウ名設定
	SetMainWindowText(Game::kTitleText);

	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	SetWindowSizeChangeEnableFlag(true);//ウィンドウモードの拡大縮小（サイズ変更）
	SetAlwaysRunFlag(true);

	if (DxLib_Init() == -1)        // ＤＸライブラリ初期化処理
	{
		return -1;            // エラーが起きたら直ちに終了
	}

	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);
	// サウンドをロードする
	Sound::LoadSound();

#ifdef DEBUG
	{
		m_pScene = new SceneTitle;
	}
#else
	{
		// デバッグ用にタイトルをすっ飛ばす
		m_pScene = new SceneTitle;
		//m_pScene = new SceneMain;
	}
#endif
	m_pScene->Init();
}
// 終了
void SceneManager::End()
{
	assert(m_pScene);// 確認処理
	if (!m_pScene)	return;

	m_pScene->End();// 終了処理
	delete m_pScene;
}
// 毎フレームの処理
void SceneManager::Update()
{
	Pad::Update();// パッドの処理の初期化

	assert(m_pScene);// 確認処理
	if (!m_pScene)	return;

	SceneBase* pScene = m_pScene->Update();// SceneBaseのupdate処理呼び出し

	if (pScene != m_pScene)
	{
		m_pScene->End();// 終了処理
		delete m_pScene;

		m_pScene = pScene;
		m_pScene->Init();// 初期化
	}
}
// 描画
void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->Draw();// 描画
}
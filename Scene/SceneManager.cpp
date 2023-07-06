#include<cassert>
#include "SceneManager.h"
#include"SceneTitle.h"
#include"SceneMain.h"
#include"../Common.h"

SceneManager::SceneManager() :
	m_pScene(nullptr)
{
}
// 初期化
void SceneManager::Init()
{
#ifdef DEBUG
	{
		m_pScene = new SceneTitle;
	}
#else
	{
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
#include"../Common.h"
#include "SceneMain.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Map.h"
#include"../Object/BackGround.h"

SceneMain::SceneMain() :
	m_shadowMap(0)
{
	// 初期化関係
	m_pPlayer = new Player();
	m_pMap = new Map();
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
	m_isFadeOut = IsFadingOut();//フェードの初期化
	m_pMap->Load();// マップのロード

	//// シャドウマップの生成
	//m_shadowMap = MakeShadowMap(1024, 1024);
	//SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::End()
{
	// 今のところ処理なし
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
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kRed, true);

			// デバッグ描画
//#if _DEBUG
//		//(仮決め)グリッドの表示
//	VECTOR startY = VGet(0, 0.0f, -100.0f);		//線の始点
//	VECTOR endY = VGet(0, 0.0f, 100.0f);		//線の終点
//	DrawLine3D(startY, endY, 0x7fffd4);			//あお
//
//	VECTOR startX = VGet(-100.0f, 0.0f, 0.0f);		//線の始点
//	VECTOR endX = VGet(100.0f, 0.0f, -0.0f);			//線の終点
//	DrawLine3D(startX, endX, 0xdc143c);			//あか
//	float lineSize = 300.0f;
//	// マップチップライン(課題当初のStageData1ColNum個(16)のマップチップをどう配置するか)
//	// プレイヤーの地面をY=0としたいので、その周りを配置し、大体の基準でカメラを決める
//	for (int i = 0; i < 16 + 2; i++)
//	{
//		// X軸とかぶるところはとりあえず描画しない
//		if (i != 1)
//		{
//			float y = 10 * (i - 1); // 一個下のラインからチップが始まる
//			DrawLine3D(VGet(-lineSize, y, 0), VGet(lineSize, y, 0), GetColor(255, 255, 0));
//		}
//	}
//#endif // kWindowMode


	m_pPlayer->Draw();// プレイヤーの表示
	m_pMap->Draw();// ステージの表示
	// フェードの表示
	SceneBase::DrawFade();
}
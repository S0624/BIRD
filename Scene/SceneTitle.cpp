#include"../Common.h"
#include "SceneTitle.h"
#include"SceneSelect.h"
#include"../Object/BackGround.h"

SceneTitle::SceneTitle():
	m_titleHandle(0),
	m_guidefont(0),
	m_test(100)
{
	m_pBack = new BackGround();
	// BGM 再生
	Sound::StartBGM(Sound::TitleBGM, 255);
}

SceneTitle::~SceneTitle()
{
	// BGM 停止
	Sound::StopBGM(Sound::TitleBGM);
	delete(m_pBack);
	DeleteGraph(m_titleHandle);
	DeleteFontToHandle(m_guidefont);
}

void SceneTitle::Init()
{
	// フェード関係の初期化
	m_isFadeOut = IsFadingOut();

	m_titleHandle = LoadGraph("Data/Img/Title.png");

	// フォントの読み込み
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// 上の表示する文字に使用するフォン
}

void SceneTitle::End()
{
	
}

SceneBase* SceneTitle::Update()
{
	m_test--;
	if (m_test < 0)
	{
		m_test = 100;
	}
	m_pBack->Update(); // 背景の更新処理
	Sound::LoopBGM(Sound::TitleBGM);
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneSelect);
		}
	}

	// フェードインアウトしていなかったら
	if (!IsFading())
	{
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::Cursor);
			StartFadeOut();
		}
	}

	return this;
}

void SceneTitle::Draw()
{
	m_pBack->Draw();	// 背景の表示

	// タイトルの文字の表示 
	DrawRotaGraph(Game::kScreenWidth / 2, 300,	// 位置の指定
				  1.0f, 0.0f,					// 拡大率、回転率
				  m_titleHandle, true, false);	// ハンドル、透過、反転
	if ((m_test / 60) == 0)
	{
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("Aボタンをおしてください", 24, m_guidefont)) / 2,
			Game::kScreenHeight - 150, "Aボタンをおしてください", 0xff0000, m_guidefont);
	}

	// フェードの表示
	SceneBase::DrawFade();
}
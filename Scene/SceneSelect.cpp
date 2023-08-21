#include "SceneSelect.h"
#include"../Common.h"
#include "SceneSelect.h"
#include"SceneMain.h"
#include"../Object/BackGround.h"

SceneSelect::SceneSelect() :
	m_selectHandle(0),
	m_frameHandle(0),
	m_guidefont(0),
	m_cursorNum(0)
{
	m_pBack = new BackGround();
}

SceneSelect::~SceneSelect()
{
	// BGM 停止
	Sound::StopBGM(Sound::SelectBGM);
	delete(m_pBack);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_frameHandle);
	DeleteFontToHandle(m_guidefont);
}

void SceneSelect::Init()
{
	// フェード関係の初期化
	m_isFadeOut = IsFadingOut();

	m_selectHandle = LoadGraph("Data/Img/Select1.png");
	m_frameHandle = LoadGraph("Data/Img/SelectFrame1.png");

	// フォントの読み込み
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// 上の表示する文字に使用するフォン
}

void SceneSelect::End()
{

}

SceneBase* SceneSelect::Update()
{
	m_pBack->Update(); // 背景の更新処理
	Sound::LoopBGM(Sound::SelectBGM);
	// フェードインアウトしている
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// フェードアウト終了時
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain(m_cursorNum));
		}
	}

	// フェードインアウトしていなかったら
	if (!IsFading())
	{
		// フェードアウト開始
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::Cursor);
			// HACK 力業 of 力業なので後で治す
			if (m_cursorNum != 3)
			{
				StartFadeOut();
			}
		}
		if (Pad::IsTrigger(PAD_INPUT_LEFT))
		{
			Sound::PlaySE(Sound::PushButton);
			m_cursorNum--;
		}
		if (Pad::IsTrigger(PAD_INPUT_RIGHT))
		{
			Sound::PlaySE(Sound::PushButton);
			m_cursorNum++;
		}
		if (m_cursorNum > 3)
		{
			m_cursorNum = 0;
		}
		if (m_cursorNum < 0)
		{
			m_cursorNum = 3;
		}
	}

	return this;
}

void SceneSelect::Draw()
{
	m_pBack->Draw();	// 背景の表示

	// select画面の表示 
	DrawGraph(0, 0, m_selectHandle, true);

	// HACK テスト実装です
	DrawStringToHandle( 190,
		Game::kScreenHeight / 2 - 30, "Easy", 0xffffff, m_guidefont);
	DrawStringToHandle( 500,
		Game::kScreenHeight / 2 - 30, "Normal", 0xffffff, m_guidefont);
	DrawStringToHandle( 880,
		Game::kScreenHeight / 2 - 30, "Hard", 0xffffff, m_guidefont);
	DrawStringToHandle( 1180,
		Game::kScreenHeight / 2 - 30, "Endless", 0xffffff, m_guidefont);

	if (m_cursorNum == 3)
	{
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("じゅんびちゅうだよ", 24, m_guidefont)) / 2,
			100, "じゅんびちゅうだよ", 0xff0000, m_guidefont);
	}

	//DrawBox(50 + 200 * (1 + m_cursorNum), 200, 50 + 200 * (1 + m_cursorNum) + 300, 200 + 500,0xff0000,false);
	DrawGraph(116  + (345 * m_cursorNum), 177, m_frameHandle, true);

	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("難易度を選んでください", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 150, "難易度を選んでください", 0xff0000, m_guidefont);
	// フェードの表示
	SceneBase::DrawFade();
}
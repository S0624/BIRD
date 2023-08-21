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
	// BGM ��~
	Sound::StopBGM(Sound::SelectBGM);
	delete(m_pBack);
	DeleteGraph(m_selectHandle);
	DeleteGraph(m_frameHandle);
	DeleteFontToHandle(m_guidefont);
}

void SceneSelect::Init()
{
	// �t�F�[�h�֌W�̏�����
	m_isFadeOut = IsFadingOut();

	m_selectHandle = LoadGraph("Data/Img/Select1.png");
	m_frameHandle = LoadGraph("Data/Img/SelectFrame1.png");

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
}

void SceneSelect::End()
{

}

SceneBase* SceneSelect::Update()
{
	m_pBack->Update(); // �w�i�̍X�V����
	Sound::LoopBGM(Sound::SelectBGM);
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain(m_cursorNum));
		}
	}

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (!IsFading())
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			Sound::PlaySE(Sound::Cursor);
			// HACK �͋� of �͋ƂȂ̂Ō�Ŏ���
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
	m_pBack->Draw();	// �w�i�̕\��

	// select��ʂ̕\�� 
	DrawGraph(0, 0, m_selectHandle, true);

	// HACK �e�X�g�����ł�
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
			GetDrawStringWidthToHandle("�����т��イ����", 24, m_guidefont)) / 2,
			100, "�����т��イ����", 0xff0000, m_guidefont);
	}

	//DrawBox(50 + 200 * (1 + m_cursorNum), 200, 50 + 200 * (1 + m_cursorNum) + 300, 200 + 500,0xff0000,false);
	DrawGraph(116  + (345 * m_cursorNum), 177, m_frameHandle, true);

	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("��Փx��I��ł�������", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 150, "��Փx��I��ł�������", 0xff0000, m_guidefont);
	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
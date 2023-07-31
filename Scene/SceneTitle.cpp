#include"../Common.h"
#include "SceneTitle.h"
#include"SceneMain.h"
#include"../Object/BackGround.h"

SceneTitle::SceneTitle():
	m_guidefont(0)
{
	m_pBack = new BackGround();
}

SceneTitle::~SceneTitle()
{
	delete(m_pBack);
	DeleteGraph(m_titleHandle);
	DeleteFontToHandle(m_guidefont);
}

void SceneTitle::Init()
{
	// �t�F�[�h�֌W�̏�����
	m_isFadeOut = IsFadingOut();

	m_titleHandle = LoadGraph("Data/Img/Title.png");

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
}

void SceneTitle::End()
{
	
}

SceneBase* SceneTitle::Update()
{
	// �t�F�[�h�C���A�E�g���Ă���
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			return (new SceneMain);
		}
	}

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (!IsFading())
	{
		// �t�F�[�h�A�E�g�J�n
		if (Pad::IsTrigger(PAD_INPUT_1))
		{
			StartFadeOut();
		}
	}

	return this;
}

void SceneTitle::Draw()
{
	m_pBack->Draw();	// �w�i�̕\��

	// �^�C�g���̕����̕\�� 
	DrawRotaGraph(Game::kScreenWidth / 2, 300,	// �ʒu�̎w��
				  1.0f, 0.0f,					// �g�嗦�A��]��
				  m_titleHandle, true, false);	// �n���h���A���߁A���]

	DrawStringToHandle((Game::kScreenWidth -
		GetDrawStringWidthToHandle("A�{�^���������Ă�������", 24, m_guidefont)) / 2,
		Game::kScreenHeight - 150, "A�{�^���������Ă�������", 0xff0000, m_guidefont);

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
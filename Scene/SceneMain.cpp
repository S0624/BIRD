#include"../Common.h"
#include "SceneMain.h"
#include "SceneResult.h"
#include "SceneTitle.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Map.h"
#include"../Object/BackGround.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SceneMain::SceneMain() :
	m_teimer(60 * 2),
	m_gamefont(0),
	m_guidefont(0),
	m_shadowMap(0)
{
	// �������֌W
	m_pPlayer = new Player();
	m_pMap = new Map();
	m_pBack = new BackGround();

	m_pCamera = new Camera();
}
/// <summary>
/// �f�X�g���N�^
/// </summary>
SceneMain::~SceneMain()
{
	// �폜
	delete(m_pPlayer);
	delete(m_pMap);
	delete(m_pBack);
	delete(m_pCamera);

	DeleteFontToHandle(m_gamefont);
	DeleteFontToHandle(m_guidefont);

	//// �V���h�E�}�b�v�̍폜
	//DeleteShadowMap(m_shadowMap);
}
/// <summary>
/// ����������
/// </summary>
void SceneMain::Init()
{
	m_isFadeOut = IsFadingOut();//�t�F�[�h�̏�����
	m_pMap->Load();// �}�b�v�̃��[�h

	// �t�H���g�̓ǂݍ���
	font::MyFontPath("Data/Font/yosugaraver1_2.ttf");
	m_gamefont = CreateFontToHandle("yosugara ver12", 100, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��
	m_guidefont = CreateFontToHandle("yosugara ver12", 75, -1, -1);// ��̕\�����镶���Ɏg�p����t�H��

	//// �V���h�E�}�b�v�̐���
	//m_shadowMap = MakeShadowMap(1024, 1024);
	//SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}
/// <summary>
/// �G���h����
/// </summary>
void SceneMain::End()
{
	// ���̂Ƃ��돈���Ȃ�
}
/// <summary>
/// �X�V����
/// </summary>
SceneBase* SceneMain::Update()
{	
	m_pCamera->Update(*m_pPlayer);// �J�����̏�����

	m_pPlayer->Update(); // �v���C���[�̍X�V����
	// OPTIMIZE �Q�[���̏�Ԃ��󂯎���Ă���
	m_pPlayer->GameClearFlag(m_pMap->GameClearFlag());	// �Q�[���̏�Ԃ��󂯎��
		// �v���C���[������ł��Ȃ��������ɍX�V�������s��
	if (!m_pPlayer->IsExistPlayer())
	{
		m_pBack->Update(); // �w�i�̍X�V����
		// �^�C�}�[�̕\�����I�������
		if (Timer())
		{
			m_pMap->Update(); // �}�b�v�̍X�V����
			m_pMap->CollisionDetection(m_pPlayer); // �����蔻��̏���
		}
	}

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			// resultScene�ɔ��
			//return (new SceneResult);
			return (new SceneTitle);
		}
	}

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�
	if (!IsFading())
	{
		m_teimer--;
		// �t�F�[�h�A�E�g�J�n
		if (m_pPlayer->IsExistPlayer() || m_pMap->GameClearFlag())
		{
			if (Pad::IsTrigger(PAD_INPUT_1))
			{
				// �t�F�[�h���J�n����
				StartFadeOut();
			}
		}
	}
	return this;
}
/// <summary>
/// �`�揈��
/// </summary>
void SceneMain::Draw()
{
	// �f�o�b�O�`��
#if false
		//(������)�O���b�h�̕\��
		VECTOR startY = VGet(0, 0.0f, -100.0f);		//���̎n�_
		VECTOR endY = VGet(0, 0.0f, 100.0f);		//���̏I�_
		DrawLine3D(startY, endY, 0x7fffd4);			//����
	
		VECTOR startX = VGet(-100.0f, 0.0f, 0.0f);		//���̎n�_
		VECTOR endX = VGet(100.0f, 0.0f, -0.0f);			//���̏I�_
		DrawLine3D(startX, endX, 0xdc143c);			//����
		float lineSize = 300.0f;
		// �}�b�v�`�b�v���C��(�ۑ蓖����StageData1ColNum��(16)�̃}�b�v�`�b�v���ǂ��z�u���邩)
		// �v���C���[�̒n�ʂ�Y=0�Ƃ������̂ŁA���̎����z�u���A��̂̊�ŃJ���������߂�
		for (int i = 0; i < 16 + 2; i++)
		{
			// X���Ƃ��Ԃ�Ƃ���͂Ƃ肠�����`�悵�Ȃ�
			if (i != 1)
			{
				float y = 10 * (i - 1); // ����̃��C������`�b�v���n�܂�
				DrawLine3D(VGet(-lineSize, y, 0), VGet(lineSize, y, 0), GetColor(255, 255, 0));
			}
		}
#endif // kWindowMode

	//// �V���h�E�}�b�v�ւ̏�������
	//ShadowMap_DrawSetup(m_shadowMap);

	//m_pBack->Draw();
	//m_pMap->Draw();// �X�e�[�W�̕\��
	//m_pPlayer->Draw();// �v���C���[�̕\��
	//// �V���h�E�}�b�v���g�p���ă��f���̕`����s��
	//ShadowMap_DrawEnd();
	//SetUseShadowMap(0, m_shadowMap);

	m_pBack->Draw();	// �w�i�̕\��
	m_pMap->Draw();		// �X�e�[�W�̕\��
	m_pPlayer->Draw();	// �v���C���[�̕\��

	// �N���A�ƃQ�[���I�[�o�[���o��
	if (m_pPlayer->IsExistPlayer() || m_pMap->GameClearFlag())
	{
		if (m_pMap->GameClearFlag())
		{
			// TODO ���Ƃŉ摜������
			DrawStringToHandle((Game::kScreenWidth -
				GetDrawStringWidthToHandle("Game Clear", 16, m_gamefont)) / 2,
				Game::kScreenHeight / 2, "Game Clear", 0xffdd0d, m_gamefont);
		}
		// TODO ���Ƃŉ摜������
		else
		{
			DrawStringToHandle((Game::kScreenWidth -
				GetDrawStringWidthToHandle("Game Over", 16, m_gamefont)) / 2,
				Game::kScreenHeight / 2, "Game Over", 0xff0f0f, m_gamefont);
		}
		DrawStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("A�{�^���������Ă�������", 24, m_guidefont)) / 2,
			Game::kScreenHeight - 150, "A�{�^���������Ă�������", 0xff0000, m_guidefont);
	}
	// �^�C�}�[
	if (!Timer())
	{
		// TODO ���Ƃŉ摜������
		DrawFormatStringToHandle((Game::kScreenWidth -
			GetDrawStringWidthToHandle("%d", 16, m_gamefont)) / 2,
			Game::kScreenHeight / 2, 0xff0000, m_gamefont, "%d", m_teimer / 60 + 1);
	}

	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}

bool SceneMain::Timer()
{
	// �c�莞�Ԃɂ��t���O��Ԃ�
	bool timeFlag = false;
	if (m_teimer <= 0)
	{
		m_teimer = 0;
		timeFlag = true;
	}

	return timeFlag;
}

#include"../Common.h"
#include "SceneMain.h"
#include"../Object/Player.h"
#include"../Camera/Camera.h"
#include"../Stage/Map.h"
#include"../Object/BackGround.h"

SceneMain::SceneMain() :
	m_shadowMap(0)
{
	// �������֌W
	m_pPlayer = new Player();
	m_pMap = new Map();
	m_pBack = new BackGround();

	m_pCamera = new Camera();
}

SceneMain::~SceneMain()
{
	// ���낢��폜
	delete(m_pPlayer);
	delete(m_pMap);
	delete(m_pBack);
	delete(m_pCamera);
}

void SceneMain::Init()
{
	m_isFadeOut = IsFadingOut();//�t�F�[�h�̏�����
	m_pMap->Load();// �}�b�v�̃��[�h

	//// �V���h�E�}�b�v�̐���
	//m_shadowMap = MakeShadowMap(1024, 1024);
	//SetShadowMapLightDirection(m_shadowMap, GetLightDirection());
}

void SceneMain::End()
{
	// ���̂Ƃ��돈���Ȃ�
}

SceneBase* SceneMain::Update()
{	
	//m_pBack->Update();
	m_pCamera->Update(*m_pPlayer);// �J�����̏�����

	// �t�F�[�h�C���A�E�g���Ă��Ȃ�������
	if (IsFading())
	{
		m_isFadeOut = IsFadingOut();
		SceneBase::UpdateFade();
		// �t�F�[�h�A�E�g�I����
		if (!IsFading() && m_isFadeOut && !m_isBackScene)
		{
			//return (new SceneMain);
		}
	}

	//// �t�F�[�h�C���A�E�g���Ă��Ȃ�
	//if (!IsFading())
	//{
	//	// �t�F�[�h�A�E�g�J�n
	//	if (Pad::IsTrigger(PAD_INPUT_1))
	//	{
	//		StartFadeOut();
	//	}
	//}

	m_pPlayer->Update();// �v���C���[�̃A�b�v�f�[�g
	m_pMap->Update();// �}�b�v�̃A�b�v�f�[�g

	return this;
}

void SceneMain::Draw()
{
	//DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, Color::kRed, true);

			// �f�o�b�O�`��
//#if _DEBUG
//		//(������)�O���b�h�̕\��
//	VECTOR startY = VGet(0, 0.0f, -100.0f);		//���̎n�_
//	VECTOR endY = VGet(0, 0.0f, 100.0f);		//���̏I�_
//	DrawLine3D(startY, endY, 0x7fffd4);			//����
//
//	VECTOR startX = VGet(-100.0f, 0.0f, 0.0f);		//���̎n�_
//	VECTOR endX = VGet(100.0f, 0.0f, -0.0f);			//���̏I�_
//	DrawLine3D(startX, endX, 0xdc143c);			//����
//	float lineSize = 300.0f;
//	// �}�b�v�`�b�v���C��(�ۑ蓖����StageData1ColNum��(16)�̃}�b�v�`�b�v���ǂ��z�u���邩)
//	// �v���C���[�̒n�ʂ�Y=0�Ƃ������̂ŁA���̎����z�u���A��̂̊�ŃJ���������߂�
//	for (int i = 0; i < 16 + 2; i++)
//	{
//		// X���Ƃ��Ԃ�Ƃ���͂Ƃ肠�����`�悵�Ȃ�
//		if (i != 1)
//		{
//			float y = 10 * (i - 1); // ����̃��C������`�b�v���n�܂�
//			DrawLine3D(VGet(-lineSize, y, 0), VGet(lineSize, y, 0), GetColor(255, 255, 0));
//		}
//	}
//#endif // kWindowMode


	m_pPlayer->Draw();// �v���C���[�̕\��
	m_pMap->Draw();// �X�e�[�W�̕\��
	// �t�F�[�h�̕\��
	SceneBase::DrawFade();
}
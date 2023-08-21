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
// ������
bool SceneManager::Init()
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);

	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);

	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	SetWindowSizeChangeEnableFlag(true);//�E�B���h�E���[�h�̊g��k���i�T�C�Y�ύX�j
	SetAlwaysRunFlag(true);

	if (DxLib_Init() == -1)        // �c�w���C�u��������������
	{
		return -1;            // �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);
	// �T�E���h�����[�h����
	Sound::LoadSound();

#ifdef DEBUG
	{
		m_pScene = new SceneTitle;
	}
#else
	{
		// �f�o�b�O�p�Ƀ^�C�g����������΂�
		m_pScene = new SceneTitle;
		//m_pScene = new SceneMain;
	}
#endif
	m_pScene->Init();
}
// �I��
void SceneManager::End()
{
	assert(m_pScene);// �m�F����
	if (!m_pScene)	return;

	m_pScene->End();// �I������
	delete m_pScene;
}
// ���t���[���̏���
void SceneManager::Update()
{
	Pad::Update();// �p�b�h�̏����̏�����

	assert(m_pScene);// �m�F����
	if (!m_pScene)	return;

	SceneBase* pScene = m_pScene->Update();// SceneBase��update�����Ăяo��

	if (pScene != m_pScene)
	{
		m_pScene->End();// �I������
		delete m_pScene;

		m_pScene = pScene;
		m_pScene->Init();// ������
	}
}
// �`��
void SceneManager::Draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;
	m_pScene->Draw();// �`��
}
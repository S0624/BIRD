#pragma once
#include "SceneBase.h"

class BackGround;
class SceneSelect :
	public SceneBase
{
public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	BackGround* m_pBack;// �w�i�̃|�C���^
	int m_selectHandle; // select��ʂ̉摜�̓ǂݍ���
	int m_frameHandle;	// select��ʂ̃t���[���̉摜�̓ǂݍ���
	int m_guidefont;	// ���̃K�C�h�Ɏg�p����t�H���g

	int m_cursorNum;	// �J�[�\���̂����Ă���ԍ�
	int m_max;

	int m_test = 200;
};


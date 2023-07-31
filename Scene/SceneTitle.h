#pragma once
#include "SceneBase.h"

class BackGround;

class SceneTitle :
    public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	BackGround* m_pBack;// 背景のポインタ
	int m_titleHandle;
	int m_guidefont;	// 下のガイドに使用するフォント
};


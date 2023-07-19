#pragma once
#include "SceneBase.h"
class SceneResult :
	public SceneBase
{
public:
	SceneResult();
	virtual ~SceneResult();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:


};

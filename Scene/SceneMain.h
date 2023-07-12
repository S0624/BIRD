#pragma once
#include "SceneBase.h"

class Player;
class Map;
class BackGround;
class Camera;

class Block;

class SceneMain :
	public SceneBase
{
public:
	SceneMain();
	virtual ~SceneMain();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	Player* m_pPlayer;
	Map* m_pMap;
	BackGround* m_pBack;
	Camera* m_pCamera;

	Block* m_pBlock;

	int	m_shadowMap;
};


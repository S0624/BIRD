#pragma once
#include "SceneBase.h"

// クラスの宣言
class Player;
class Map;
class BackGround;
class Camera;
class GameObject;

// シーンベースクラスを継承してシーンを作成する
class SceneMain :
	public SceneBase
{
public:
	// コンストラクタ
	SceneMain();
	// デストラクタ
	virtual ~SceneMain();

	// 初期化
	virtual void Init();
	// エンド処理
	virtual void End();
	// 更新処理
	virtual SceneBase* Update() override;
	// 描画処理
	virtual void Draw();

	bool Timer();
private:
	Player* m_pPlayer;	// プレイヤーのポインタ
	Map* m_pMap;		// マップのポインタ
	BackGround* m_pBack;// 背景のポインタ
	Camera* m_pCamera;	// カメラのポインタ

	int m_gamefont;		// カウントダウンなどに使用するフォント
	int m_guidefont;	// 下のガイドに使用するフォント

	int m_teimer;		// タイマー(始まる前のカウントダウンに使用)

	// TODO シャドウマップを付けようとしてできなかったのであとで追加する
	int	m_shadowMap;	// シャドウマップ(影)のための変数
};


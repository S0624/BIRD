#pragma once

#include "../Common.h"
#include<memory>

class Model;
class Block;
/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();				// コンストラクタ
	~Player();				// デストラクタ

	void Init() {};			// 初期化処理
	void Update();			// 更新
	void Draw();			// 描画

	// モデルハンドルの取得
	//int GetModelHandle() const { return m_modelHandle; }
	// プレイヤーの位置の取得
	const VECTOR& GetPlayerPos() const { return m_pos; }
	const float GetCollisionRadius()const { return m_colradius; }


	bool IsExistPlayer() { return m_isExist; }
	bool IsExistPlayer(bool isexist) { return m_isExist = isexist; }
	int TestBox(int testbox) { return m_boxPos = testbox; }

private:
	// プレイヤーモデル
	std::shared_ptr<Model> m_pModel;

	int		m_modelHandle;	// モデルハンドル
	VECTOR	m_pos;			// ポジション
	VECTOR	m_velocity;		// 移動力
	VECTOR	m_dir;			// 回転方向
	float   m_colradius;	// 当たり判定に使用する半径の大きさ
	bool	m_isExist;		// プレイヤーが死亡したかどうか
	int     m_boxPos;		// 箱の位置によって落ちる場所を変える	

	 const float m_speed;
	 const float m_scale;
	 float m_jumpAcc;
	 
	 int	m_attachIndex;	// 総時間取得するアニメーションのアタッチ番号
	 int	m_totalTime;	// アニメーションの総再生時間
	 float	m_animTime;		// 現在のアニメーションの再生時間
	 int	m_attachAnimNum;// 再生したいアニメーションの番号
};

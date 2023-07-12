#pragma once
#include "../Common.h"
#include<vector>

class Player;
/// <summary>
/// ブロック表示クラス
/// </summary>

class Block
{
public:
	Block();				// コンストラクタ
	~Block();				// デストラクタ

	void Update();			// 更新
	void Draw();			// 描画

	//ToDo テスト用の関数
	void BlockPos(int blockX, int blockY);
	// 画面内にブロックがあるかどうか
	bool IsExist(int blockNum);

	// モデルハンドルの取得
	int GetModelHandle() const { return m_modelHandle; }

	void ColDetection(const Player& player);
private:
	int		m_modelHandle;	// モデルハンドル
	std::vector<VECTOR>m_pos;
	//VECTOR	m_pos;			// ポジション
	VECTOR	m_velocity;		// 移動力
	VECTOR	m_dir;			// 回転方向

	const float m_speed;
	const float m_scale;

	int m_blockX;			// ブロックの位置をもらってくる
	int m_blockY;			// ブロックの位置をもらってくる

	bool m_isExist;			//	画面内に存在しているかどうか

	// Test
	int m_testColor = 0;
};


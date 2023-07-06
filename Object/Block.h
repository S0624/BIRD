#pragma once
#include "../Common.h"

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
	void Test(int blockX, int blockY) { m_blockX = blockX; m_blockY = blockY;}

	// モデルハンドルの取得.
	int GetModelHandle() const { return m_modelHandle; }

	const VECTOR& GetPos() const { return m_pos; }

private:
	int		m_modelHandle;	// モデルハンドル
	VECTOR	m_pos;			// ポジション
	VECTOR	m_velocity;		// 移動力
	VECTOR	m_dir;			// 回転方向

	const float m_speed;
	const float m_scale;

	int m_blockX;			// ブロックの位置をもらってくる
	int m_blockY;			// ブロックの位置をもらってくる

};


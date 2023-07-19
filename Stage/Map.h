#pragma once
#include <vector>
#include<memory>
#include "../Common.h"

class Block;
class Stage;
class Player;

/// <summary>
/// マップを表示する
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();

	void CollisionDetection(Player* player);
	bool GameClearFlag() { return m_gameClearFlag; }

	// モデルハンドルの取得
	int GetModelHandle() const { return m_modelHandle; }
	int GetColFrameIndex() const { return m_collisionFrameIndex; }

private:
	int	m_modelHandle;		// モデルハンドル
	int m_collisionFrameIndex;	// 使用するフレーム
	std::vector<std::vector<int>> m_currentData; // 読み込んだデータを一時的に保存する
	int m_dataColNum = 0;	// 横の最大数
	int m_dataRowNum = 0;	// 縦の最大数
	Stage* m_pStage;		// ステージクラスの宣言

	bool m_gameClearFlag;	// ゲームがクリアしたかの宣言
	float   m_collisionradius;	// 当たり判定に使用する半径の大きさ
	std::vector<std::shared_ptr<Block>> m_pBlock;
};


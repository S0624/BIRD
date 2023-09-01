#pragma once
#include <vector>
#include<memory>
#include "../Common.h"

// クラスの宣言
class GameObject;
class Stage;
class Player;

/// <summary>
/// マップを表示する
/// </summary>
class Map
{
public:
	// コンストラクタ
	Map(int selectNum);
	// デストラクタ
	~Map();

	// マップのロード
	void Load();
	// マップの更新処理
	void Update();
	// マップの描画
	void Draw();

	// エンドレスを選択したときに行う処理
	void SelectEndless();
	// プレイヤーたちの当たり判定
	void CollisionDetection(Player* player);
	// ゲームをクリアしたかのフラグ
	bool GameClearFlag() { return m_gameClearFlag; }

private:
	int m_selectNum;		// 選んでいる番号
	std::vector<std::vector<int>> m_currentData;		// 読み込んだデータを一時的に保存する
	Stage* m_pStage;									// ステージクラスの宣言
	std::vector<std::shared_ptr<GameObject>> m_pObject;	// オブジェクトクラスの宣言

	int m_dataColNum;		// 横の最大数
	int m_dataRowNum;		// 縦の最大数
	int m_max;				// カーソルの選択数の最大数
	int m_maxRand;			// ランダムな数を生成するときの最大数
	bool m_gameClearFlag;	// ゲームがクリアしたかの宣言
	float   m_collisionradius;	// 当たり判定に使5用する半径の大きさ
};


#pragma once

#include "../Common.h"
#include<memory>
#include<vector>

// クラスの宣言
class Model;
class Player;

/// <summary>
/// ブロック表示クラス
/// </summary>
enum Object
{
	Empty,		// 空
	Field,		// 床
	Flag,		// 旗(ゴール)
};

class GameObject
{
public:
	// コンストラクタ
	// モデルのハンドル、使用する当たり判定のフレーム、描画する位置のXとY座標
	GameObject(const char* modelhnadle, int objNum, int blockX, int blockY);

	// デストラクタ
	~GameObject();				

	// 初期化処理
	void Init(){};			
	// 更新
	void Update();			
	// 描画
	void Draw();		

	// 画面内にブロックがあるかどうか
	bool IsExist();

	// モデルハンドルの取得
	int GetModelHandle() const;
	//	当たり判定の取得
	int GetCollisionFrameIndex() const;

private:
	std::shared_ptr<Model> m_pModel;// モデルの表示
	int		m_modelHandle;	// モデルハンドル
	VECTOR	m_pos;			// ポジション

	const float m_speed;	// スクロールのスピード
	const float m_scale;	// モデルの大きさ

	int m_blockX;			// ブロックの位置をもらってくる
	int m_blockY;			// ブロックの位置をもらってくる

	bool m_isExist;			//	画面内に存在しているかどうか
	int m_objectNum;		//  オブジェクトの使用している番号
};


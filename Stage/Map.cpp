#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/GameObject.h"
#include "../Object/Player.h"

namespace
{
	// モデルのハンドル
	const char* const kFieldHandle = "Data/Model/Block.mv1";	// フィールド用のモデル
	const char* const kFlagHandle = "Data/Model/Flag.mv1";		// 旗用のモデル
	// 当たり判定として使用するフレームの名前
	const char* const kCollisionFrameNamu = "BoxCol";
	// プレイヤーの位置を受け取る
	VECTOR kPlayerPos = { 0,0,0 };
	// プレイヤーの当たり判定の大きさを受け取る
	float kPlayerRad = 0;
}

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map() :
	m_dataColNum(0),
	m_dataRowNum(0),
	m_collisionradius(0),
	m_flagPos(0),
	m_gameClearFlag(false)
{	
	m_currentData.clear();
	// マップのロード
	m_pStage = new Stage;
	m_pStage->Load("Data/Map3.fmf");
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	delete(m_pStage);
	m_pObject.clear();
	
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	// currentDataに外部ファイルを代入
	m_currentData.clear();
	std::vector<int> newColData;

	m_pStage->GetMapSize(m_dataRowNum, m_dataColNum);
	const auto mapData = m_pStage->GetMapData();
	for (int i = m_dataColNum - 1; i >= 0; i--)
	{
		newColData.clear();
		for (int j = 0; j < m_dataRowNum; j++)
		{
			newColData.push_back(m_pStage->GetChipId(0, j, i));
		}
		m_currentData.push_back(newColData);
	}
	for (int i = 0; i < m_dataColNum; i++)
	{
		for (int j = 0; j < m_dataRowNum; j++)
		{
			if (m_currentData[i][j] == Field)
			{
				// ブロックの初期化処理
				m_pObject.push_back(std::make_shared<GameObject>(kFieldHandle, Field, j, i));
				m_pObject.back()->Init();
			}
			if (m_currentData[i][j] == Flag)
			{
				// ３Ｄモデルの読み込み
				// フラグの初期化処理
				m_pObject.push_back(std::make_shared<GameObject>(kFlagHandle, Flag, j, i));
				m_flagPos = static_cast<int>(m_pObject.size() - 1);
				m_pObject.back()->Init();
			}
		}
	}
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 更新処理
	for (const auto& obj : m_pObject)
	{
		obj->Update();
		// 当たり判定の情報
		MV1SetupCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex(), 8, 8, 8);
		MV1RefreshCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex());
	}

	// 不必要なオブジェクトの削除処理
	for (int i = 0; i < m_pObject.size() - 1; i++)
	{
		if (!m_pObject[i]->IsExist())
		{
			// 存在していなかったら要素を削除
			m_pObject.erase(m_pObject.begin() + i);
			m_flagPos -= 1;
		}
	}

	// 旗が画面外に言ったらゲームクリア判定にする
	if (m_flagPos <= 0)
	{
		m_flagPos = 0;
		m_gameClearFlag = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	// 描画処理
	for (const auto& obj : m_pObject)
	{
		obj->Draw();
	}
}

void Map::CollisionDetection(Player* player)
{
	// プレイヤーの位置、当たり判定の範囲を渡す
	player->GetPlayerPos();
	player->GetCollisionRadius();

	// DxLibの関数を利用して当たり判定をとる
	MV1_COLL_RESULT_POLY_DIM result;// 当たりデータ

	for (const auto& obj : m_pObject)
	{
		result = MV1CollCheck_Capsule(obj->GetModelHandle(), obj->GetCollisionFrameIndex(),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 3, player->GetPlayerPos().z),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 7, player->GetPlayerPos().z),
			player->GetCollisionRadius());
		if (obj->GameObjectNum() == Field)
		{
			if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
			{
				player->IsExistPlayer(true);
				player->PlayerDropPoint(static_cast<int>(result.Dim[1].Position[1].y));
			}
		}
		else if (obj->GameObjectNum() == Flag)
		{
			if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
			{
				m_gameClearFlag = true;
			}
		}
		// 当たり判定情報の後始末
		MV1CollResultPolyDimTerminate(result);
	}
}
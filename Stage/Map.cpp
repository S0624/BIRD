#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/Block.h"
#include "../Object/Player.h"

namespace
{
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
	m_collisionFrameIndex(0),
	m_collisionradius(0),
	m_gameClearFlag(false)
{	
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("Data/Model/Block.mv1");

	m_currentData.clear();
	// マップのロード
	m_pStage = new Stage;
	m_pStage->Load("Data/Map.fmf");

	MV1SetupCollInfo(m_modelHandle, m_collisionFrameIndex, 8, 8, 8);
	
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	delete(m_pStage);
	m_pBlock.clear();
	
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
			if (m_currentData[i][j] == 1)
			{
				// ブロッククラスの初期化処理
				m_pBlock.push_back(std::make_shared<Block>(m_modelHandle, m_collisionFrameIndex, j, i));
				m_pBlock.back()->Init();
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
	for (const auto& block : m_pBlock)
	{
		block->Update();
		// 当たり判定の情報
		MV1SetupCollInfo(block->GetModelHandle(), block->GetCollisionFrameIndex(), 8, 8, 8);
		MV1RefreshCollInfo(block->GetModelHandle(), block->GetCollisionFrameIndex());
	}
	if (!m_pBlock[m_pBlock.size() - 1]->IsExist())
	{
		printfDx("ごーる（仮）\n");
		m_gameClearFlag = true;
	}
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	// 描画処理
	for (const auto& block : m_pBlock)
	{
		block->Draw();
	}
}

void Map::CollisionDetection(Player* player)
{
	// プレイヤーの位置、当たり判定の範囲を渡す
	player->GetPlayerPos();
	player->GetCollisionRadius();

	// HACK テスト実装きれいにする
	// DxLibの関数を利用して当たり判定をとる
	MV1_COLL_RESULT_POLY_DIM result;// 当たりデータ

	for (const auto& block : m_pBlock)
	{
		result = MV1CollCheck_Capsule(block->GetModelHandle(), block->GetCollisionFrameIndex(),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 3, player->GetPlayerPos().z),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 7, player->GetPlayerPos().z),
			player->GetCollisionRadius());
		if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
		{
			player->IsExistPlayer(true);
			//player->TestBox(block->GetPos().y);
			//player->TestBox(block->GetPos().y);
			player->TestBox(result.Dim[1].Position[1].y);
		}
		// 当たり判定情報の後始末
		MV1CollResultPolyDimTerminate(result);
	}
}
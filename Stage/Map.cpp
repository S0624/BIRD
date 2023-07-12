#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/Block.h"
#include "../Object/Player.h"

namespace
{
	VECTOR testPlayerPos = { 0,0,0 };
	float testPlayerRad = 0;
}

/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
{
	m_currentData.clear();
	m_pStage = new Stage;
	for (const auto& block : m_pBlock)
	{
		//block -> new Block();
	}
	auto block = new Block();
	m_pBlock.push_back(block);

	//m_pBlock = new Block();
	m_pStage->Load("Data/Map.fmf");
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	delete(m_pStage);
	for (const auto& block : m_pBlock)
	{
		delete(block);
	}
	/*m_pBlock.clear();
	for (const auto& block : m_pBlock)
	{
		if (block != nullptr)
		{
			delete(block);
		}
	}*/
}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	//////////////////////////////////////////////////////
	// currentDataに外部ファイルを代入
	//////////////////////////////////////////////////////
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
				for (const auto& block : m_pBlock)
				{
					block->BlockPos(j, i);
				}
				//m_pBlock->BlockPos(j, i);
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
	//m_pBlock->Update();
	for (const auto& block : m_pBlock)
	{
		block->Update();
	}
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{
	// 描画処理

	//for (int i = 0; i < m_dataColNum; i++)
	//{
	//	for (int j = 0; j < m_dataRowNum; j++)
	//	{
	//		if (m_currentData[i][j] == 1)
	//		{
	for (const auto& block : m_pBlock)
	{
		block->Draw();
	}
	//m_pBlock->Draw();
	
	//m_pBlock.push_back(block);
	/*		}
		}
	}*/
}


void Map::ColDetection(const Player& player)
{
	testPlayerRad = player.SetColRadius();
	testPlayerPos = player.SetPlayerPos();


	// HACK テスト実装きれいにする
	// DxLibの関数を利用して当たり判定をとる
	MV1_COLL_RESULT_POLY_DIM result;// 当たりデータ
	for (const auto& block : m_pBlock)
	{
		MV1SetupCollInfo(block->GetModelHandle(), 0, 8, 8, 8);
		MV1RefreshCollInfo(block->GetModelHandle(), 0);

		//for (auto& block : m_pBlock)
		{
			result = MV1CollCheck_Capsule(block->GetModelHandle(), 0,
				VGet(testPlayerPos.x, testPlayerPos.y + 3, testPlayerPos.z),
				VGet(testPlayerPos.x, testPlayerPos.y + 7, testPlayerPos.z), testPlayerRad);

			//if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
			{
				printfDx("Hit %d\n", result.HitNum);

			}
		}
	}

	// 当たったポリゴンの数だけ繰り返し
	for (int i = 0; i < result.HitNum; i++)
	{
		// 当たったポリゴンを描画
		DrawTriangle3D(
			result.Dim[i].Position[0],
			result.Dim[i].Position[1],
			result.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
	}


	DrawCapsule3D(VGet(testPlayerPos.x, testPlayerPos.y + 3, testPlayerPos.z),
		VGet(testPlayerPos.x, testPlayerPos.y + 7, testPlayerPos.z),
		testPlayerRad, 3, Color::kWhite, Color::kWhite, true);

	//player.test(true);
}
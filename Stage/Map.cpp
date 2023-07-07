#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/Block.h"


/// <summary>
/// コンストラクタ
/// </summary>
Map::Map()
{
	m_currentData.clear();
	m_pStage = new Stage;
	m_pBlock = new Block();
	m_pStage->Load("Data/Map.fmf");
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{
	delete(m_pStage);
	delete(m_pBlock);
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
				m_pBlock->BlockPos(j, i);
			}
		}
	}
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 処理なし
	m_pBlock->Update();
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
				m_pBlock->Draw();
				//m_pBlock.push_back(block);
	/*		}
		}
	}*/
}



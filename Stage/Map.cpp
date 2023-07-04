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
	m_pBlock = new Block;
	m_pStage->Load("Data/Map.fmf");
}

/// <summary>
/// デストラクタ
/// </summary>
Map::~Map()
{

}

/// <summary>
/// ロード
/// </summary>
void Map::Load()
{
	//////////////////////////////////////////////////////
	// 外部からのint値入力で、Stage1Dataを使うかStage2Dataを使うか切り替える
	// 言い換えると、可変データであるcurrentDataに
	// Stage1DataかStage2Dataの内容を【読み取って代入している】
	// ここを外部ファイル「外部ファイルの内容を読み取って代入する」形にすれば
	// 外部データ化は完了
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
	//for (int i = 0; i < dataColNum; i++)
	//{
	//	for (int j = 0; j < dataRowNum; j++)
	//	{
	//		if (currentData[i][j] == 1)
	//		{
	//			m_pBlock->test(i, j);
	//			m_pBlock->Update();
	//			m_pBlock->Draw();
	//		}
	//	}
	//}

	//////////////////////////////////////////////////////



	//// WorldSprite実体設定と位置初期化
	//VECTOR chipLeftTopPos = VGet(0, dataColNum * ChipSize, 0);			// マップの描画開始位置（左上）
	//for (int i = 0; i < dataColNum; i++)
	//{
	//	for (int j = 0; j < dataRowNum; j++)
	//	{
	//		auto sprite = new WorldSprite();
	//		sprite->Initialize(chipGraph, ChipPixelSize, currentData[i][j]);
	//		VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);					// マップチップの半分サイズ左下にずらすオフセット
	//		VECTOR chipPos = VAdd(VGet(j * Map::ChipSize,  (-i - 1) * Map::ChipSize, 0), chipHalfOffset);	// 真ん中ピボットなのでマップチップ半分サイズずらす+地面なので一つ下に
	//		chipPos = VAdd(chipPos, chipLeftTopPos);
	//		//sprite->SetTransform(chipPos, Map::ChipSize);
	//		sprite->SetTransform(VGet(0,0,0), Map::ChipSize);
	//		sprites.push_back(sprite);
	//	}
	//}
}

/// <summary>
/// 更新
/// </summary>
void Map::Update()
{
	// 処理なし
}

/// <summary>
/// 描画
/// </summary>
void Map::Draw()
{

	// 仮で表示
	//for (const auto& sprite : sprites)
	//{
	//	sprite->Draw();
	//}
	for (int i = 0; i < m_dataColNum; i++)
	//for (int i = 0; i < dataColNum; i++)
	{
		for (int j = 0; j < m_dataRowNum; j++)
		//for (int j = 0; j < dataRowNum; j++)
		{
			if (m_currentData[i][j] == 1)
			{
				m_pBlock->test(j, i);
				m_pBlock->Update();
				m_pBlock->Draw();
			}
		}
	}

}



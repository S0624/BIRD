#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/Block.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	m_currentData.clear();
	m_pStage = new Stage;
	m_pBlock = new Block;
	m_pStage->Load("Data/Map.fmf");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{

}

/// <summary>
/// ���[�h
/// </summary>
void Map::Load()
{
	//////////////////////////////////////////////////////
	// currentData�ɊO���t�@�C������
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
}

/// <summary>
/// �X�V
/// </summary>
void Map::Update()
{
	// �����Ȃ�
}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	//Todo�H �Ȃ񂩓��������ǂ����Ă�H�H�H�H�����Ă͂Ȃ��Ƃ�����
	
	// ���ŕ\��
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

				m_pBlock->Test(j, i);
				m_pBlock->Update();
				m_pBlock->Draw();
			}
		}
	}

}


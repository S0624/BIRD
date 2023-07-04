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
	// �O�������int�l���͂ŁAStage1Data���g����Stage2Data���g�����؂�ւ���
	// ����������ƁA�σf�[�^�ł���currentData��
	// Stage1Data��Stage2Data�̓��e���y�ǂݎ���đ�����Ă���z
	// �������O���t�@�C���u�O���t�@�C���̓��e��ǂݎ���đ������v�`�ɂ����
	// �O���f�[�^���͊���
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



	//// WorldSprite���̐ݒ�ƈʒu������
	//VECTOR chipLeftTopPos = VGet(0, dataColNum * ChipSize, 0);			// �}�b�v�̕`��J�n�ʒu�i����j
	//for (int i = 0; i < dataColNum; i++)
	//{
	//	for (int j = 0; j < dataRowNum; j++)
	//	{
	//		auto sprite = new WorldSprite();
	//		sprite->Initialize(chipGraph, ChipPixelSize, currentData[i][j]);
	//		VECTOR chipHalfOffset = VGet(-Map::ChipSize * 0.5f, -Map::ChipSize * 0.5f, 0);					// �}�b�v�`�b�v�̔����T�C�Y�����ɂ��炷�I�t�Z�b�g
	//		VECTOR chipPos = VAdd(VGet(j * Map::ChipSize,  (-i - 1) * Map::ChipSize, 0), chipHalfOffset);	// �^�񒆃s�{�b�g�Ȃ̂Ń}�b�v�`�b�v�����T�C�Y���炷+�n�ʂȂ̂ň����
	//		chipPos = VAdd(chipPos, chipLeftTopPos);
	//		//sprite->SetTransform(chipPos, Map::ChipSize);
	//		sprite->SetTransform(VGet(0,0,0), Map::ChipSize);
	//		sprites.push_back(sprite);
	//	}
	//}
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
				m_pBlock->test(j, i);
				m_pBlock->Update();
				m_pBlock->Draw();
			}
		}
	}

}



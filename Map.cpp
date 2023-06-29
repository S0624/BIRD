#include<vector>
#include "Map.h"
#include "DxLib.h"
#include "Stage.h"
#include "Block.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map()
{
	currentData.clear();
	pStage = new Stage;
	m_pBlock = new Block;
	pStage->Load("Data/Map.fmf");
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
	currentData.clear();
	std::vector<int> newColData;

	pStage->GetMapSize(dataRowNum, dataColNum);
	const auto mapData = pStage->GetMapData();
	for (int i = 0; i < dataColNum; i++)
	{
		newColData.clear();
		for (int j = 0; j < dataRowNum; j++)
		{
			newColData.push_back(pStage->GetChipId(0, j, i));
		}
		currentData.push_back(newColData);
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
	for (int i = 0; i < dataColNum; i++)
	//for (int i = 0; i < dataColNum; i++)
	{
		for (int j = 0; j < dataRowNum; j++)
		//for (int j = 0; j < dataRowNum; j++)
		{
			if (currentData[i][j] == 1)
			{
				m_pBlock->test(j, i);
				m_pBlock->Update();
				m_pBlock->Draw();
			}
		}
	}

}



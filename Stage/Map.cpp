#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/Block.h"
#include "../Object/Player.h"

namespace
{
	// �����蔻��Ƃ��Ďg�p����t���[���̖��O
	const char* const kCollisionFrameNamu = "BoxCol";
	// �v���C���[�̈ʒu���󂯎��
	VECTOR kPlayerPos = { 0,0,0 };
	// �v���C���[�̓����蔻��̑傫�����󂯎��
	float kPlayerRad = 0;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Map::Map() :
	m_collisionFrameIndex(0),
	m_collisionradius(0),
	m_gameClearFlag(false)
{	
	// �R�c���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("Data/Model/Block.mv1");

	m_currentData.clear();
	// �}�b�v�̃��[�h
	m_pStage = new Stage;
	m_pStage->Load("Data/Map.fmf");

	MV1SetupCollInfo(m_modelHandle, m_collisionFrameIndex, 8, 8, 8);
	
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	delete(m_pStage);
	m_pBlock.clear();
	
}

/// <summary>
/// ���[�h
/// </summary>
void Map::Load()
{
	// currentData�ɊO���t�@�C������
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
				// �u���b�N�N���X�̏���������
				m_pBlock.push_back(std::make_shared<Block>(m_modelHandle, m_collisionFrameIndex, j, i));
				m_pBlock.back()->Init();
			}
		}
	}
}

/// <summary>
/// �X�V
/// </summary>
void Map::Update()
{
	// �X�V����
	for (const auto& block : m_pBlock)
	{
		block->Update();
		// �����蔻��̏��
		MV1SetupCollInfo(block->GetModelHandle(), block->GetCollisionFrameIndex(), 8, 8, 8);
		MV1RefreshCollInfo(block->GetModelHandle(), block->GetCollisionFrameIndex());
	}
	if (!m_pBlock[m_pBlock.size() - 1]->IsExist())
	{
		printfDx("���[��i���j\n");
		m_gameClearFlag = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	// �`�揈��
	for (const auto& block : m_pBlock)
	{
		block->Draw();
	}
}

void Map::CollisionDetection(Player* player)
{
	// �v���C���[�̈ʒu�A�����蔻��͈̔͂�n��
	player->GetPlayerPos();
	player->GetCollisionRadius();

	// HACK �e�X�g�������ꂢ�ɂ���
	// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
	MV1_COLL_RESULT_POLY_DIM result;// ������f�[�^

	for (const auto& block : m_pBlock)
	{
		result = MV1CollCheck_Capsule(block->GetModelHandle(), block->GetCollisionFrameIndex(),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 3, player->GetPlayerPos().z),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 7, player->GetPlayerPos().z),
			player->GetCollisionRadius());
		if (result.HitNum > 0)// 1���ȏ�̃|���S���Ɠ������Ă����烂�f���Ɠ������Ă��锻��
		{
			player->IsExistPlayer(true);
			//player->TestBox(block->GetPos().y);
			//player->TestBox(block->GetPos().y);
			player->TestBox(result.Dim[1].Position[1].y);
		}
		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
}
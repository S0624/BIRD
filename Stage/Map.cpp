#include<vector>
#include "Map.h"
#include "Stage.h"
#include "../Object/GameObject.h"
#include "../Object/Player.h"

namespace
{
	// ���f���̃n���h��
	const char* const kFieldHandle = "Data/Model/Block.mv1";	// �t�B�[���h�p�̃��f��
	const char* const kFlagHandle = "Data/Model/Flag.mv1";		// ���p�̃��f��
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
	m_dataColNum(0),
	m_dataRowNum(0),
	m_collisionradius(0),
	m_flagPos(0),
	m_gameClearFlag(false)
{	
	m_currentData.clear();
	// �}�b�v�̃��[�h
	m_pStage = new Stage;
	m_pStage->Load("Data/Map3.fmf");
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Map::~Map()
{
	delete(m_pStage);
	m_pObject.clear();
	
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
			if (m_currentData[i][j] == Field)
			{
				// �u���b�N�̏���������
				m_pObject.push_back(std::make_shared<GameObject>(kFieldHandle, Field, j, i));
				m_pObject.back()->Init();
			}
			if (m_currentData[i][j] == Flag)
			{
				// �R�c���f���̓ǂݍ���
				// �t���O�̏���������
				m_pObject.push_back(std::make_shared<GameObject>(kFlagHandle, Flag, j, i));
				m_flagPos = static_cast<int>(m_pObject.size() - 1);
				m_pObject.back()->Init();
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
	for (const auto& obj : m_pObject)
	{
		obj->Update();
		// �����蔻��̏��
		MV1SetupCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex(), 8, 8, 8);
		MV1RefreshCollInfo(obj->GetModelHandle(), obj->GetCollisionFrameIndex());
	}

	// �s�K�v�ȃI�u�W�F�N�g�̍폜����
	for (int i = 0; i < m_pObject.size() - 1; i++)
	{
		if (!m_pObject[i]->IsExist())
		{
			// ���݂��Ă��Ȃ�������v�f���폜
			m_pObject.erase(m_pObject.begin() + i);
			m_flagPos -= 1;
		}
	}

	// ������ʊO�Ɍ�������Q�[���N���A����ɂ���
	if (m_flagPos <= 0)
	{
		m_flagPos = 0;
		m_gameClearFlag = true;
	}
}

/// <summary>
/// �`��
/// </summary>
void Map::Draw()
{
	// �`�揈��
	for (const auto& obj : m_pObject)
	{
		obj->Draw();
	}
}

void Map::CollisionDetection(Player* player)
{
	// �v���C���[�̈ʒu�A�����蔻��͈̔͂�n��
	player->GetPlayerPos();
	player->GetCollisionRadius();

	// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
	MV1_COLL_RESULT_POLY_DIM result;// ������f�[�^

	for (const auto& obj : m_pObject)
	{
		result = MV1CollCheck_Capsule(obj->GetModelHandle(), obj->GetCollisionFrameIndex(),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 3, player->GetPlayerPos().z),
			VGet(player->GetPlayerPos().x, player->GetPlayerPos().y + 7, player->GetPlayerPos().z),
			player->GetCollisionRadius());
		if (obj->GameObjectNum() == Field)
		{
			if (result.HitNum > 0)// 1���ȏ�̃|���S���Ɠ������Ă����烂�f���Ɠ������Ă��锻��
			{
				player->IsExistPlayer(true);
				player->PlayerDropPoint(static_cast<int>(result.Dim[1].Position[1].y));
			}
		}
		else if (obj->GameObjectNum() == Flag)
		{
			if (result.HitNum > 0)// 1���ȏ�̃|���S���Ɠ������Ă����烂�f���Ɠ������Ă��锻��
			{
				m_gameClearFlag = true;
			}
		}
		// �����蔻����̌�n��
		MV1CollResultPolyDimTerminate(result);
	}
}
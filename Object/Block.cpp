#include "Block.h"
#include <cassert>

namespace
{
	constexpr float kMoveScroll = -0.5f;
	float kAddScroll = 0.0f;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
Block::Block()
	: m_modelHandle(-1),
	m_speed(3.0f),
	m_scale(0.05f),	// �X�P�[��
	m_blockX(0),
	m_blockY(0),
	m_isExist(false)
{
	// �R�c���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("Data/Model/Block.mv1");
	//m_modelHandle = MV1LoadModel("Data/Model/Robot.mv1");
	m_modelHandle = MV1DuplicateModel(m_modelHandle);
	
	assert(m_modelHandle >= 0);
	
	m_pos.push_back(VGet(50, -10, 0));
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Block::~Block()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// �X�V
/// </summary>
void Block::Update()
{

	// 3D���f���̃X�P�[������
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// �X�N���[������
	for (int i = 0; i < m_pos.size(); i++)
	{
		m_pos[i].x += kMoveScroll;

	}

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));

}

/// <summary>
/// �`��
/// </summary>
void Block::Draw()
{
	for (int i = 0; i < m_pos.size(); i++)
	{
		if (IsExist(i))
		{
			// �RD���f���̃|�W�V�����ݒ�
			MV1DrawModel(m_modelHandle);
			MV1SetPosition(m_modelHandle, m_pos[i]);
			// �R�c���f���̕`��
			DrawCapsule3D(m_pos[i], m_pos[i],
				6.0f, 3, Color::kWhite, Color::kGreen, true);
		}
	}
}

void Block::BlockPos(int blockX, int blockY)
{
	m_blockX = blockX;
	m_blockY = blockY;

	m_pos.push_back(VAdd(VGet(50, -10, 0), VGet((m_blockX * 9), (m_blockY * 9), 0)));
	//m_pos = VAdd(VGet(50, -10, 0), VGet((m_blockX * 9), (m_blockY * 9), 0));
}

bool Block::IsExist(int blockNum)
{
	//m_isExist.clear();
	//for (auto& pos : m_pos)
	//{
	//	if (pos.x > 0)
	//	{
			m_isExist.push_back(true);
	//	}
	//	else
	//	{
	//		m_isExist.push_back(false);
	//	}
	//}
	return m_isExist[blockNum];
}

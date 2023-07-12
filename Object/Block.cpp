#include "Block.h"
#include"Player.h"
#include <cassert>

namespace
{
	constexpr float kMoveScroll = -0.5f;
	//float kAddScroll = 0.0f;
	constexpr float kColRadius = 6.0f;

	VECTOR testPlayerPos = {0,0,0};
	float testPlayerRad = 0;
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
			//// �R�c���f���̕`��
			//DrawCapsule3D(m_pos[i], m_pos[i],
			//	kColRadius, 3, Color::kWhite, Color::kGreen, true);
		}
	}
}

void Block::BlockPos(int blockX, int blockY)
{
	m_blockX = blockX;
	m_blockY = blockY;

	m_pos.push_back(VAdd(VGet(50, -10, 0), VGet((m_blockX * 9), (m_blockY * 9), 0)));
}

bool Block::IsExist(int blockNum)
{
	if (m_pos[blockNum].x > 0 && m_pos[blockNum].x < 230)
	{
		m_isExist = true;
	}
	else
	{
		m_isExist = false;
	}
	return m_isExist;
}

void Block::ColDetection(const Player& player)
{
	//testPlayerRad = player.SetColRadius();
	//testPlayerPos = player.SetPlayerPos();


	//// HACK �e�X�g�������ꂢ�ɂ���
	//// DxLib�̊֐��𗘗p���ē����蔻����Ƃ�
	//MV1SetupCollInfo(m_modelHandle, 0, 8, 8, 8);
	//MV1RefreshCollInfo(m_modelHandle, 0);
	//MV1_COLL_RESULT_POLY_DIM result;// ������f�[�^

	//for (const auto& pos : m_pos)
	//{
	//	result = MV1CollCheck_Capsule(m_modelHandle, 0,
	//		VGet(testPlayerPos.x, testPlayerPos.y + 3, testPlayerPos.z), 
	//		VGet(testPlayerPos.x, testPlayerPos.y + 7, testPlayerPos.z), testPlayerRad);

	//	if (result.HitNum > 0)// 1���ȏ�̃|���S���Ɠ������Ă����烂�f���Ɠ������Ă��锻��
	//	{
	//		printfDx("Hit %d\n", result.HitNum);

	//	}
	//}

	//// ���������|���S���̐������J��Ԃ�
	//for (int i = 0; i < result.HitNum; i++)
	//{
	//	// ���������|���S����`��
	//	DrawTriangle3D(
	//		result.Dim[i].Position[0],
	//		result.Dim[i].Position[1],
	//		result.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
	//}


	//DrawCapsule3D(VGet(testPlayerPos.x, testPlayerPos.y + 3, testPlayerPos.z), 
	//	VGet(testPlayerPos.x, testPlayerPos.y + 7, testPlayerPos.z),
	//	testPlayerRad, 3, Color::kWhite, Color::kWhite, true);

	////player.test(true);
}
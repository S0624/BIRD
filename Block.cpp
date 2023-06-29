#include "Block.h"
#include"Pad.h"
#include <cassert>
#include"game.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
Block::Block()
	: m_modelHandle(-1),
	m_speed(3.0f),
	m_scale(0.08f)	// �X�P�[��

{
	// �R�c���f���̓ǂݍ���
	m_modelHandle = MV1LoadModel("Data/Model/Block.mv1");
	assert(m_modelHandle >= 0);
	
	m_pos = VGet(50, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Block::~Block()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// �X�V
/// </summary>
void Block::Update()
{
	//	Pad::update();
		// ����̓e�X�g
		// �̂��Ƀv���`�i���������ŊO���t�@�C����ǂݍ���őΏۂ̏ꏊ�Ńu���b�N��\��������
		//int test[5][5] = { {0, 1, 0, 0, 0},
		//					{1, 0, 0, 1, 0}, 
		//					{0, 0, 1, 0, 0}, 
		//					{0, 1, 0, 1, 0}, 
		//					{0, 0, 0, 0, 0}, };
		//for (int j = 0; j < 5; j++)
		//{
		//	for (int i = 0; i < 5; i++)
		//	{
		//		if (test[j][i] == 0)
		//		{
					//m_pos = VGet(50 + (testX * 15), Game::kScreenHeight - (testY * 15), 0);
	m_pos = VGet(50 + (testX * 15), 0 + (testY * 15), 0);
	//m_pos = VGet(50 + (15 * i), 0 + (15 * j), 0);
	// 3D���f���̃X�P�[������
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// �RD���f���̃|�W�V�����ݒ�
	MV1SetPosition(m_modelHandle, m_pos);

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);
	//		}
	//	}
	//}
	//// �RD���f���̃|�W�V�����ݒ�
	//MV1SetPosition(m_modelHandle, m_pos);
	//m_pos.x -= 1.0;
}

/// <summary>
/// �`��
/// </summary>
void Block::Draw()
{	
	// �R�c���f���̕`��
	MV1DrawModel(m_modelHandle);

	printfDx("%f\n", m_pos.y);
}

#pragma once
#include "../Common.h"
#include<vector>

class Player;
/// <summary>
/// �u���b�N�\���N���X
/// </summary>

class Block
{
public:
	Block();				// �R���X�g���N�^
	~Block();				// �f�X�g���N�^

	void Update();			// �X�V
	void Draw();			// �`��

	//ToDo �e�X�g�p�̊֐�
	void BlockPos(int blockX, int blockY);
	// ��ʓ��Ƀu���b�N�����邩�ǂ���
	bool IsExist(int blockNum);

	// ���f���n���h���̎擾
	int GetModelHandle() const { return m_modelHandle; }

	void ColDetection(const Player& player);
private:
	int		m_modelHandle;	// ���f���n���h��
	std::vector<VECTOR>m_pos;
	//VECTOR	m_pos;			// �|�W�V����
	VECTOR	m_velocity;		// �ړ���
	VECTOR	m_dir;			// ��]����

	const float m_speed;
	const float m_scale;

	int m_blockX;			// �u���b�N�̈ʒu��������Ă���
	int m_blockY;			// �u���b�N�̈ʒu��������Ă���

	bool m_isExist;			//	��ʓ��ɑ��݂��Ă��邩�ǂ���

	// Test
	int m_testColor = 0;
};


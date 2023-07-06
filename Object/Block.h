#pragma once
#include "../Common.h"

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
	void Test(int blockX, int blockY) { m_blockX = blockX; m_blockY = blockY;}

	// ���f���n���h���̎擾.
	int GetModelHandle() const { return m_modelHandle; }

	const VECTOR& GetPos() const { return m_pos; }

private:
	int		m_modelHandle;	// ���f���n���h��
	VECTOR	m_pos;			// �|�W�V����
	VECTOR	m_velocity;		// �ړ���
	VECTOR	m_dir;			// ��]����

	const float m_speed;
	const float m_scale;

	int m_blockX;			// �u���b�N�̈ʒu��������Ă���
	int m_blockY;			// �u���b�N�̈ʒu��������Ă���

};


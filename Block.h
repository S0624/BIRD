#pragma once
#include "DxLib.h"

class Block
{
public:
	Block();				// �R���X�g���N�^
	~Block();				// �f�X�g���N�^

	void Update();			// �X�V
	void Draw();			// �`��

	void test(int blockX, int blockY) { testX = blockX; testY = blockY;}

	// ���f���n���h���̎擾.
	int GetModelHandle() const { return m_modelHandle; }

	const VECTOR& GetPos() const { return m_pos; }
	const VECTOR& GetDir() const { return m_dir; }

private:
	int		m_modelHandle;	// ���f���n���h��
	VECTOR	m_pos;			// �|�W�V����
	VECTOR	m_velocity;		// �ړ���
	VECTOR	m_dir;			// ��]����

	const float m_speed;
	const float m_scale;

	int testX;
	int testY;

};


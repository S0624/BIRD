#pragma once

#include "../Common.h"
#include<memory>
#include<vector>

class Model;
class Player;
/// <summary>
/// �u���b�N�\���N���X
/// </summary>

class Block
{
public:
	// �R���X�g���N�^
	Block(int modelhnadle, int colindex, int blockX, int blockY);		// ���f���̃n���h���A�g�p���铖���蔻��̃t���[���A�`�悷��ʒu��X��Y���W

	~Block();				// �f�X�g���N�^

	void Init(){};			// ����������
	void Update();			// �X�V
	void Draw();			// �`��

	// ��ʓ��Ƀu���b�N�����邩�ǂ���
	bool IsExist();

	//// ���f���n���h���̎擾
	int GetModelHandle() const;
	int GetCollisionFrameIndex() const;
	VECTOR GetPos() { return m_pos; }

	//std::vector<VECTOR> GetPos()const { return m_pos; }
private:
	// �v���C���[���f��
	std::shared_ptr<Model> m_pModel;
	int		m_modelHandle;	// ���f���n���h��
	VECTOR	m_pos;			// �|�W�V����
	VECTOR	m_velocity;		// �ړ���
	VECTOR	m_dir;			// ��]����

	const float m_speed;
	const float m_scale;

	int m_blockX;			// �u���b�N�̈ʒu��������Ă���
	int m_blockY;			// �u���b�N�̈ʒu��������Ă���

	bool m_isExist;			//	��ʓ��ɑ��݂��Ă��邩�ǂ���

	int m_colFrameIndex;	// �g�p����t���[��
};


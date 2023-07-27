#pragma once

#include "../Common.h"
#include<memory>
#include<vector>


class Model;
class Player;

/// <summary>
/// �u���b�N�\���N���X
/// </summary>
enum Object
{
	Empty,		// ��
	Field,		// ��
	Flag,		// ��(�S�[��)
};

class GameObject
{
public:
	// �R���X�g���N�^
	// ���f���̃n���h���A�g�p���铖���蔻��̃t���[���A�`�悷��ʒu��X��Y���W
	GameObject(const char* modelhnadle, int objNum, int blockX, int blockY);

	// �f�X�g���N�^
	~GameObject();				

	// ����������
	void Init(){};			
	// �X�V
	void Update();			
	// �`��
	void Draw();		

	// ��ʓ��Ƀu���b�N�����邩�ǂ���
	bool IsExist();

	//// ���f���n���h���̎擾
	int GetModelHandle() const;
	int GetCollisionFrameIndex() const;
	VECTOR GetPos() { return m_pos; }

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

	int m_objectNum;	// �g�p����t���[��
};


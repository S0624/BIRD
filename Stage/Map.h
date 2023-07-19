#pragma once
#include <vector>
#include<memory>
#include "../Common.h"

class Block;
class Stage;
class Player;

/// <summary>
/// �}�b�v��\������
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();

	void CollisionDetection(Player* player);
	bool GameClearFlag() { return m_gameClearFlag; }

	// ���f���n���h���̎擾
	int GetModelHandle() const { return m_modelHandle; }
	int GetColFrameIndex() const { return m_collisionFrameIndex; }

private:
	int	m_modelHandle;		// ���f���n���h��
	int m_collisionFrameIndex;	// �g�p����t���[��
	std::vector<std::vector<int>> m_currentData; // �ǂݍ��񂾃f�[�^���ꎞ�I�ɕۑ�����
	int m_dataColNum = 0;	// ���̍ő吔
	int m_dataRowNum = 0;	// �c�̍ő吔
	Stage* m_pStage;		// �X�e�[�W�N���X�̐錾

	bool m_gameClearFlag;	// �Q�[�����N���A�������̐錾
	float   m_collisionradius;	// �����蔻��Ɏg�p���锼�a�̑傫��
	std::vector<std::shared_ptr<Block>> m_pBlock;
};


#pragma once
#include <vector>
#include<memory>
#include "../Common.h"

class GameObject;
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
	// �Q�[�����N���A�������̃t���O
	bool GameClearFlag() { return m_gameClearFlag; }

private:
	std::vector<std::vector<int>> m_currentData; // �ǂݍ��񂾃f�[�^���ꎞ�I�ɕۑ�����
	int m_dataColNum;		// ���̍ő吔
	int m_dataRowNum;		// �c�̍ő吔
	Stage* m_pStage;		// �X�e�[�W�N���X�̐錾

	int m_flagPos;			// ���̈ʒu��ۑ�����ϐ�
	bool m_gameClearFlag;	// �Q�[�����N���A�������̐錾
	float   m_collisionradius;	// �����蔻��Ɏg5�p���锼�a�̑傫��
	std::vector<std::shared_ptr<GameObject>> m_pObject;
};


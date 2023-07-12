#pragma once
#include <vector>
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

	void ColDetection(const Player& player);

	// �}�b�v�`�b�v�̃T�C�Y
	//static const float	ChipSize;
	//static const int	ChipPixelSize;

private:
	
	std::vector<std::vector<int>> m_currentData;
	int m_dataColNum = 0;
	int m_dataRowNum = 0;
	Stage* m_pStage;
	//Block* m_pBlock;

	float   m_colradius;	// �����蔻��Ɏg�p���锼�a�̑傫��
	std::vector<Block*> m_pBlock;
};


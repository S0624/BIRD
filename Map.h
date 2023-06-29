#pragma once
#include <vector>
#include "DxLib.h"

class Block;
class Stage;

/// <summary>
/// 2D�̔w�i�}�b�v
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();

	// �}�b�v�`�b�v�̃T�C�Y
	static const float	ChipSize;
	static const int	ChipPixelSize;

private:
	
	std::vector<std::vector<int>> currentData;
	int dataColNum = 0;
	int dataRowNum = 0;
	Stage* pStage;
	Block* m_pBlock;
};


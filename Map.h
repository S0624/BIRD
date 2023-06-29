#pragma once
#include <vector>
#include "DxLib.h"

class Block;
class Stage;

/// <summary>
/// 2Dの背景マップ
/// </summary>
class Map
{
public:
	Map();
	~Map();

	void Load();
	void Update();
	void Draw();

	// マップチップのサイズ
	static const float	ChipSize;
	static const int	ChipPixelSize;

private:
	
	std::vector<std::vector<int>> currentData;
	int dataColNum = 0;
	int dataRowNum = 0;
	Stage* pStage;
	Block* m_pBlock;
};


#pragma once
#include <vector>
#include "../Common.h"

class Block;
class Stage;

/// <summary>
/// マップを表示する
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
	//static const float	ChipSize;
	//static const int	ChipPixelSize;

private:
	
	std::vector<std::vector<int>> m_currentData;
	int m_dataColNum = 0;
	int m_dataRowNum = 0;
	Stage* m_pStage;
	Block* m_pBlock;
};


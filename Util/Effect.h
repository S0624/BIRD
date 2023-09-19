#pragma once
#include"../Common.h"

class Effect
{
public:
	Effect();
	~Effect();

	void Init();
	void Update();
	void Draw();
private:
	int m_effectHandle;
	int m_currentPlayEffect;
	VECTOR m_pos;
};


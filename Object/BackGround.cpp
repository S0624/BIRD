#include "BackGround.h"
#include"../Common.h"

BackGround::BackGround()
{
 	m_handle1 = LoadGraph("Data/Img/Background_1.png");
 	m_handle2 = LoadGraph("Data/Img/Background_2.png");
	
}

BackGround::~BackGround()
{
}

void BackGround::Update()
{
    m_scroll1--;
    m_scroll2--;
}

void BackGround::Draw()
{
    // ÅiâºÅj
    DrawGraph(0, 0, m_handle2, false);
    DrawGraph(0, 0, m_handle1, true);
}

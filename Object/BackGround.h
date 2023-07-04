#pragma once
class BackGround
{
public:
	BackGround();
	~BackGround();

	void Update();
	void Draw();
private:
	int m_handle1;
	int m_handle2;
	int m_scroll1;
	int m_scroll2;
};


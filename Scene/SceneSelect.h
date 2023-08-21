#pragma once
#include "SceneBase.h"

class BackGround;
class SceneSelect :
	public SceneBase
{
public:
	SceneSelect();
	virtual ~SceneSelect();

	virtual void Init();
	virtual void End();

	virtual SceneBase* Update() override;
	virtual void Draw();

private:
	BackGround* m_pBack;// 背景のポインタ
	int m_selectHandle; // select画面の画像の読み込み
	int m_frameHandle;	// select画面のフレームの画像の読み込み
	int m_guidefont;	// 下のガイドに使用するフォント

	int m_cursorNum;	// カーソルのさしている番号
	int m_max;

	int m_test = 200;
};


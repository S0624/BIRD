#include "Block.h"
#include"Pad.h"
#include <cassert>
#include"game.h"


/// <summary>
/// コンストラクタ
/// </summary>
Block::Block()
	: m_modelHandle(-1),
	m_speed(3.0f),
	m_scale(0.08f)	// スケール

{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("Data/Model/Block.mv1");
	assert(m_modelHandle >= 0);
	
	m_pos = VGet(50, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);

}

/// <summary>
/// デストラクタ
/// </summary>
Block::~Block()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void Block::Update()
{
	//	Pad::update();
		// これはテスト
		// のちにプラチナムか何かで外部ファイルを読み込んで対象の場所でブロックを表示させる
		//int test[5][5] = { {0, 1, 0, 0, 0},
		//					{1, 0, 0, 1, 0}, 
		//					{0, 0, 1, 0, 0}, 
		//					{0, 1, 0, 1, 0}, 
		//					{0, 0, 0, 0, 0}, };
		//for (int j = 0; j < 5; j++)
		//{
		//	for (int i = 0; i < 5; i++)
		//	{
		//		if (test[j][i] == 0)
		//		{
					//m_pos = VGet(50 + (testX * 15), Game::kScreenHeight - (testY * 15), 0);
	m_pos = VGet(50 + (testX * 15), 0 + (testY * 15), 0);
	//m_pos = VGet(50 + (15 * i), 0 + (15 * j), 0);
	// 3Dモデルのスケール決定
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);
	//		}
	//	}
	//}
	//// ３Dモデルのポジション設定
	//MV1SetPosition(m_modelHandle, m_pos);
	//m_pos.x -= 1.0;
}

/// <summary>
/// 描画
/// </summary>
void Block::Draw()
{	
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

	printfDx("%f\n", m_pos.y);
}

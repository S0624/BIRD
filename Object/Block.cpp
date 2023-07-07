#include "Block.h"
#include <cassert>

namespace
{
	constexpr float kMoveScroll = -0.005f;
	float kAddScroll = 0.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
Block::Block()
	: m_modelHandle(-1),
	m_speed(3.0f),
	m_scale(0.05f),	// スケール
	m_blockX(0),
	m_blockY(0),
	m_isExist(false)
{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("Data/Model/Block.mv1");
	//m_modelHandle = MV1LoadModel("Data/Model/Robot.mv1");
	m_modelHandle = MV1DuplicateModel(m_modelHandle);
	
	assert(m_modelHandle >= 0);
	
	m_pos = VGet(50, -10, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);

}

/// <summary>
/// デストラクタ
/// </summary>
Block::~Block()
{
	// モデルのアンロード
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void Block::Update()
{
	//if (IsExist())
	{
		// 3Dモデルのスケール決定
		MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

		// スクロール処理
		kAddScroll += kMoveScroll;
		m_pos.x += kAddScroll;

		// ３Dモデルのポジション設定
		MV1SetPosition(m_modelHandle, m_pos);

		// 回転
		MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	}
}

/// <summary>
/// 描画
/// </summary>
void Block::Draw()
{
	if (IsExist())
	{
		// ３Ｄモデルの描画
		MV1DrawModel(m_modelHandle);
		DrawCapsule3D(VGet(m_pos.x, m_pos.y, m_pos.z), VGet(m_pos.x, m_pos.y, m_pos.z),
			6.0f, 3, Color::kWhite, Color::kGreen, true);
	}
}

void Block::Test(int blockX, int blockY)
{
	m_blockX = blockX;
	m_blockY = blockY;
	//m_pBlockX.push_back(m_blockX);
	//m_pBlockY.push_back(m_blockY);

	m_pos = VAdd(VGet(50, -10, 0), VGet((m_blockX * 9), (m_blockY * 9), 0));
}

bool Block::IsExist()
{
	m_isExist = true;
	if (m_pos.x > 0&& m_pos.x < 250)
	{
		//m_isExist = true;
	}
	else
	{
		//m_isExist = false;
	}
	return m_isExist;
}

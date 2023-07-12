#include "Block.h"
#include"Player.h"
#include <cassert>

namespace
{
	constexpr float kMoveScroll = -0.5f;
	//float kAddScroll = 0.0f;
	constexpr float kColRadius = 6.0f;

	VECTOR testPlayerPos = {0,0,0};
	float testPlayerRad = 0;
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
	m_modelHandle = MV1DuplicateModel(m_modelHandle);
	
	assert(m_modelHandle >= 0);
	
	m_pos.push_back(VGet(50, -10, 0));
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

	// 3Dモデルのスケール決定
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// スクロール処理
	for (int i = 0; i < m_pos.size(); i++)
	{
		m_pos[i].x += kMoveScroll;

	}

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));

}

/// <summary>
/// 描画
/// </summary>
void Block::Draw()
{
	for (int i = 0; i < m_pos.size(); i++)
	{
		if (IsExist(i))
		{
			// ３Dモデルのポジション設定
			MV1DrawModel(m_modelHandle);
			MV1SetPosition(m_modelHandle, m_pos[i]);
			//// ３Ｄモデルの描画
			//DrawCapsule3D(m_pos[i], m_pos[i],
			//	kColRadius, 3, Color::kWhite, Color::kGreen, true);
		}
	}
}

void Block::BlockPos(int blockX, int blockY)
{
	m_blockX = blockX;
	m_blockY = blockY;

	m_pos.push_back(VAdd(VGet(50, -10, 0), VGet((m_blockX * 9), (m_blockY * 9), 0)));
}

bool Block::IsExist(int blockNum)
{
	if (m_pos[blockNum].x > 0 && m_pos[blockNum].x < 230)
	{
		m_isExist = true;
	}
	else
	{
		m_isExist = false;
	}
	return m_isExist;
}

void Block::ColDetection(const Player& player)
{
	//testPlayerRad = player.SetColRadius();
	//testPlayerPos = player.SetPlayerPos();


	//// HACK テスト実装きれいにする
	//// DxLibの関数を利用して当たり判定をとる
	//MV1SetupCollInfo(m_modelHandle, 0, 8, 8, 8);
	//MV1RefreshCollInfo(m_modelHandle, 0);
	//MV1_COLL_RESULT_POLY_DIM result;// 当たりデータ

	//for (const auto& pos : m_pos)
	//{
	//	result = MV1CollCheck_Capsule(m_modelHandle, 0,
	//		VGet(testPlayerPos.x, testPlayerPos.y + 3, testPlayerPos.z), 
	//		VGet(testPlayerPos.x, testPlayerPos.y + 7, testPlayerPos.z), testPlayerRad);

	//	if (result.HitNum > 0)// 1枚以上のポリゴンと当たっていたらモデルと当たっている判定
	//	{
	//		printfDx("Hit %d\n", result.HitNum);

	//	}
	//}

	//// 当たったポリゴンの数だけ繰り返し
	//for (int i = 0; i < result.HitNum; i++)
	//{
	//	// 当たったポリゴンを描画
	//	DrawTriangle3D(
	//		result.Dim[i].Position[0],
	//		result.Dim[i].Position[1],
	//		result.Dim[i].Position[2], GetColor(0, 255, 255), TRUE);
	//}


	//DrawCapsule3D(VGet(testPlayerPos.x, testPlayerPos.y + 3, testPlayerPos.z), 
	//	VGet(testPlayerPos.x, testPlayerPos.y + 7, testPlayerPos.z),
	//	testPlayerRad, 3, Color::kWhite, Color::kWhite, true);

	////player.test(true);
}
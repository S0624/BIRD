#include "Player.h"
#include"../Util/Model.h"
#include <cassert>
namespace
{
	// モデルのファイル名
	const char* const kFileName = "Data/Model/Bee.mv1";
	// 重力
	constexpr float kGravity = -0.15f;
	// ジャンプ力
	constexpr float kJumpPower = 2.5f;
}

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player(): 
	m_modelHandle(-1),
	m_colradius(5.0f),
	m_boxPos(-10.0f),
	m_speed(3.0f),
	m_scale(0.07f),	// スケール
	m_jumpAcc(0),
	m_attachIndex(0),
	m_totalTime(0),
	m_animTime(0),
	m_attachAnimNum(2)

{
	// 3Dモデルの生成
	m_pModel = std::make_shared<Model>(kFileName);
	m_pModel->SetAnimation(m_attachAnimNum, true, true);

	m_pos = VGet(60, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 0);

}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	m_pModel->Update();
	//PlayAnimation();

	// ジャンプ処理
	bool isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y < -10.0f || m_pos.y < m_boxPos)
	{
		m_pos.y = m_boxPos;
		m_jumpAcc = 0.0f;
		isJumping = false;
	}
	if (m_pos.y > 110.0f)
	{
		m_pos.y = 110.0f;
		m_jumpAcc = 0.0f;
		isJumping = false;
	}
	// デバッグ描画
#if _DEBUG
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		m_jumpAcc = kJumpPower;
	}
	// デバック用で方向移動(後でいらないからけす)
	m_dir = VGet(0, 0, 0);
	if (Pad::IsPress(PAD_INPUT_UP))
	{
		m_dir = VAdd(m_dir, VGet(0, 1, 0));
	}
	else if (Pad::IsPress(PAD_INPUT_DOWN))
	{
		m_dir = VAdd(m_dir, VGet(0, -1, 0));
	}
	if (Pad::IsPress(PAD_INPUT_RIGHT))
	{
		m_dir = VAdd(m_dir, VGet(1, 0, 0));
	}
	else if (Pad::IsPress(PAD_INPUT_LEFT))
	{
		m_dir = VAdd(m_dir, VGet(-1, 0, 0));
	}

	// デバック用
	// HACK 死亡処理
	else if (Pad::IsTrigger(PAD_INPUT_2)|| IsExistPlayer())
	{
		m_attachAnimNum = 1;
		m_animTime = 0.0f;
		m_pModel->ChangeAnimation(m_attachAnimNum, false, true, 4);
	}

	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}
#endif // kWindowMode

	// ポジションを更新.
	m_velocity = VScale(m_dir, m_speed);
	m_pos = VAdd(m_pos, m_velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}


	// 3Dモデルのスケール決定
	m_pModel->SetPos(m_pos);
	// ３Dモデルのポジション設定
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// 回転（モデルを横に向かせる）
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	m_pModel->Draw();

	// デバッグ描画
#if _DEBUG
	//DrawFormatString(400,0,0x00ff00,"Z飛ぶ\nX死亡\nCカメラ--\nAカメラ++");
	//DrawFormatString(400, 100, 0xffffff, "PlayerPos%f,%f,%f", m_pos.x, m_pos.y, m_pos.z);

#endif // kWindowMode
}
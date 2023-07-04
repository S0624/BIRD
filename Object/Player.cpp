#include "Player.h"
#include <cassert>

namespace
{
	// 重力
	constexpr float kGravity = -0.15f;
	// ジャンプ力
	constexpr float kJumpPower = 2.5f;
}

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: m_modelHandle(-1),
	m_speed(3.0f),
	//m_scale(0.01f),	// スケール
	m_scale(0.07f),	// スケール
	m_jumpAcc(0),
	m_attachIndex(0),
	m_totalTime(0),
	m_animTime(0),
	m_attachAnimNum(2)

{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("Data/Model/Bee.mv1");
	assert(m_modelHandle >= 0);
	m_pos = VGet(0, -10, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);

	printfDx("%f,%f,%f\n", m_pos.x,m_pos.y, m_pos.z);
}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
	// モデルのアンロード.
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update()
{
	PlayAnimation();

	// ジャンプ処理
	bool isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y < -10.0f)
	{
		m_pos.y = -10.0f;
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
	else if (Pad::IsTrigger(PAD_INPUT_2))
	{
		m_attachAnimNum = 1;
		m_animTime = 0.0f;
		DetachAnimation();
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
	MV1SetScale(m_modelHandle, VGet(m_scale, m_scale, m_scale));

	// ３Dモデルのポジション設定
	MV1SetPosition(m_modelHandle, m_pos);

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, -89.5f, 0.0f));
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw()
{
	// ３Ｄモデルの描画
	MV1DrawModel(m_modelHandle);

	// デバッグ描画
#if _DEBUG
	DrawFormatString(0,0,0x00ff00,"Z飛ぶ\nX死亡");
	//printfDx("%f %f %f\n", pos.x, pos.y, pos.z);
	DrawFormatString(400, 100, 0xffffff, "%f,%f,%f", m_pos.x, m_pos.y, m_pos.z);
#endif // kWindowMode
}

void Player::PlayAnimation()
{
	m_animTime += 0.5f;
	if (m_animTime >= m_totalTime)
	{
		m_animTime = 0.0f;
		m_attachAnimNum = 2;
		DetachAnimation();
	}

	MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_animTime);
}

void Player::DetachAnimation()
{
	MV1DetachAnim(m_modelHandle, m_attachIndex);
	// ３Ｄモデルのアニメーションをアタッチする
	m_attachIndex = MV1AttachAnim(m_modelHandle, m_attachAnimNum, -1, false);
	// アタッチしたアニメーションの総再生時間を取得する
	m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);
}

#include "Player.h"
#include "DxLib.h"
#include"Pad.h"
#include <cassert>

namespace
{
	// 重力
	constexpr float kGravity = -0.3f;
	// ジャンプ力
	constexpr float kJumpPower = 5.0f;
}

/// <summary>
/// コンストラクタ
/// </summary>
Player::Player()
	: m_modelHandle(-1),
	m_speed(3.0f),
	m_scale(0.09f),	// スケール
	m_jumpAcc(0),
	m_attachIndex(),
	m_totalTime(),
	m_animTime(),
	m_attachAnimNum()

{
	// ３Ｄモデルの読み込み
	m_modelHandle = MV1LoadModel("Data/Model/Bee.mv1");
	//assert(modelHandle >= 0);
	m_pos = VGet(10, 0, 0);
	m_velocity = VGet(0, 0, 0);
	m_dir = VGet(0, 0, 1);
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
	Pad::update();
	// キー入力取得
	int Key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	// ジャンプ処理
	bool isJumping = true;
	m_jumpAcc += kGravity;
	m_pos.y += m_jumpAcc;
	if (m_pos.y < 0.0f)
	{
		m_pos.y = 0.0f;
		m_jumpAcc = 0.0f;
		isJumping = false;
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		m_jumpAcc = kJumpPower;
	}
	// 単純に方向転換
	m_dir = VGet(0, 0, 0);
	if (Key & PAD_INPUT_UP)
	{
		m_dir = VAdd(m_dir, VGet(0, 1, 0));
	}
	else if (Key & PAD_INPUT_DOWN)
	{
		m_dir = VAdd(m_dir, VGet(0, -1, 0));
	}
	if (Key & PAD_INPUT_RIGHT)
	{
		m_dir = VAdd(m_dir, VGet(1, 0, 0));
	}
	else if (Key & PAD_INPUT_LEFT)
	{
		m_dir = VAdd(m_dir, VGet(-1, 0, 0));
	}

	// ゼロ除算避け
	if (VSquareSize(m_dir) > 0)
	{
		// 正規化
		m_dir = VNorm(m_dir);
	}

	// ポジションを更新.
	m_velocity = VScale(m_dir, m_speed);
	m_pos = VAdd(m_pos, m_velocity);

	// 力をかけ終わったベロシティの方向にディレクションを調整.
	if (VSize(m_velocity) != 0)
	{
		m_dir = VNorm(m_velocity);
	}
	//printfDx("%f %f %f\n", pos.x, pos.y, pos.z);
	DrawFormatString(400, 100, 0xffffff, "%f,%f,%f", m_pos.x, m_pos.y, m_pos.z);

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
}

void Player::PlayAnimation()
{
	m_animTime += 0.5f;
	if (m_animTime >= m_totalTime)
	{
		m_animTime = 0.0f;
		m_attachAnimNum = 10;
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

#pragma once

#include "../Common.h"

/// <summary>
/// プレイヤークラス
/// </summary>
class Player
{
public:
	Player();				// コンストラクタ
	~Player();				// デストラクタ

	void Update();			// 更新
	void Draw();			// 描画

	void PlayAnimation();	// アニメーションの処理
	void DetachAnimation(); // アニメーションを切り替える

	// モデルハンドルの取得
	int GetModelHandle() const { return m_modelHandle; }

	const VECTOR& GetPos() const { return m_pos; }

private:
	int		m_modelHandle;	// モデルハンドル
	VECTOR	m_pos;			// ポジション
	VECTOR	m_velocity;		// 移動力
	VECTOR	m_dir;			// 回転方向

	 const float m_speed;
	 const float m_scale;
	 float m_jumpAcc;
	 
	 int	m_attachIndex;	// 総時間取得するアニメーションのアタッチ番号
	 int	m_totalTime;	// アニメーションの総再生時間
	 float	m_animTime;		// 現在のアニメーションの再生時間
	 int	m_attachAnimNum;// 再生したいアニメーションの番号

};

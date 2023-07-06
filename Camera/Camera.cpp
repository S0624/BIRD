﻿#include "../Object/Player.h"
#include "Camera.h"

/// <summary>
/// コンストラクタ
/// </summary>
Camera::Camera()
{
	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 1000.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(550, 10, 0), VGet(550.0f, 10.0f, 0.0f));

	m_pos = VGet(0, 0, 0);
	
	// Zバッファを使用する
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを行う
	SetWriteZBuffer3D(true);

	// ポリゴンの裏面を描画しない
	SetUseBackCulling(true);

}

/// <summary>
/// デストラクタ
/// </summary>
Camera::~Camera()
{
	// 処理なし
}

/// <summary>
/// 更新
/// </summary>
void Camera::Update(const Player& player)
{

	if (Pad::IsPress(PAD_INPUT_3))
	{
		test += 0.5;
	}
	if (Pad::IsPress(PAD_INPUT_4))
	{
		test -= 0.5;
	}

	printfDx("%f\n", test);
	VECTOR playerPos = player.GetPos();
	VECTOR cameraPos = VGet(playerPos.x + 60 ,  40.0f, playerPos.z  - 100.0f + test);// 縦に追いかけない
	//VECTOR cameraPos = VGet(playerPos.x + 60 ,  40.0f, playerPos.z  - 100.0f);// 縦に追いかけない

	// 注視する視点は、カメラと平行にまっすぐz=0地点
	VECTOR lookPos = VGet(cameraPos.x, cameraPos.y, 0.0f);

	m_pos = cameraPos;

	// カメラに位置を反映
	SetCameraPositionAndTarget_UpVecY(m_pos, lookPos);
	//printfDx("%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);

}
#include "GameObject.h"
#include"../Util/Model.h"
#include <cassert>

namespace
{
	// スクロール量
	//constexpr float kMoveScroll = -1.5f;
	constexpr float kMoveScroll = -1.0f;
	//float kAddScroll = 0.0f;
	
	// 当たり判定の大きさ（仮）
	constexpr float kColRadius = 6.0f;

	// プレイヤーの位置を受け取る
	VECTOR kPlayerPos = {0,0,0};
	// プレイヤーの当たり判定の大きさを受け取る
	float kPlayerRad = 0;
}

/// <summary>
/// コンストラクタ
/// </summary>
GameObject::GameObject(const char* modelhnadle, int objNum, int blockX, int blockY)
	: m_modelHandle(-1),
	m_objectNum(objNum),
	m_speed(3.0f),
	m_scale(0.05f),	// スケール
	m_blockX(blockX),
	m_blockY(blockY),
	m_isExist(false)
{
	m_modelHandle = MV1LoadModel(modelhnadle);
	// 3Dモデルの生成
	m_pModel = std::make_shared<Model>(m_modelHandle);
	//m_pModel->SetAnimation(m_animNo, true, true);
	m_pModel->setUseCollision(true, true);


	m_pos = VAdd(VGet(100.0f, -10.0f, 0.0f), VGet(static_cast<float>(m_blockX * 9), static_cast<float>(m_blockY * 9), 0));
	m_velocity = VGet(0.0f, 0.0f, 0.0f);
	m_dir = VGet(0.0f, 0.0f, 1.0f);

}

/// <summary>
/// デストラクタ
/// </summary>
GameObject::~GameObject()
{
	// モデルのアンロード
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// 更新
/// </summary>
void GameObject::Update()
{
	// スクロール処理
	m_pos.x += kMoveScroll;

	// 回転
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3Dモデルのスケール決定
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// 回転（モデルを横に向かせる）
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
	m_pModel->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameObject::Draw()
{

	// 存在していなかったら描画しない
	if (IsExist())
	{
		// ３Dモデルのポジション設定
		m_pModel->SetPos(m_pos);
		m_pModel->Draw();
	}

}

// 範囲外だったら存在を消す
bool GameObject::IsExist()
{
	if (m_pos.x > 0)
	{
		m_isExist = true;
	}
	else
	{
		m_isExist = false;
	}
	return m_isExist;
}

int GameObject::GetModelHandle() const
{
	return m_pModel->GetModelHandle();
}

int GameObject::GetCollisionFrameIndex() const
{
	return m_pModel->GetColFrameIndex();
}
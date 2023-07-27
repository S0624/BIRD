#include "GameObject.h"
#include"../Util/Model.h"
#include <cassert>

namespace
{
	// �X�N���[����
	//constexpr float kMoveScroll = -1.5f;
	constexpr float kMoveScroll = -1.0f;
	//float kAddScroll = 0.0f;
	
	// �����蔻��̑傫���i���j
	constexpr float kColRadius = 6.0f;

	// �v���C���[�̈ʒu���󂯎��
	VECTOR kPlayerPos = {0,0,0};
	// �v���C���[�̓����蔻��̑傫�����󂯎��
	float kPlayerRad = 0;
}

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameObject::GameObject(const char* modelhnadle, int objNum, int blockX, int blockY)
	: m_modelHandle(-1),
	m_objectNum(objNum),
	m_speed(3.0f),
	m_scale(0.05f),	// �X�P�[��
	m_blockX(blockX),
	m_blockY(blockY),
	m_isExist(false)
{
	m_modelHandle = MV1LoadModel(modelhnadle);
	// 3D���f���̐���
	m_pModel = std::make_shared<Model>(m_modelHandle);
	//m_pModel->SetAnimation(m_animNo, true, true);
	m_pModel->setUseCollision(true, true);


	m_pos = VAdd(VGet(100.0f, -10.0f, 0.0f), VGet(static_cast<float>(m_blockX * 9), static_cast<float>(m_blockY * 9), 0));
	m_velocity = VGet(0.0f, 0.0f, 0.0f);
	m_dir = VGet(0.0f, 0.0f, 1.0f);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameObject::~GameObject()
{
	// ���f���̃A�����[�h
	MV1DeleteModel(m_modelHandle);
}

/// <summary>
/// �X�V
/// </summary>
void GameObject::Update()
{
	// �X�N���[������
	m_pos.x += kMoveScroll;

	// ��]
	MV1SetRotationXYZ(m_modelHandle, VGet(0.0f, 0.0f, 0.0f));
	// 3D���f���̃X�P�[������
	m_pModel->SetScale(VGet(m_scale, m_scale, m_scale));
	// ��]�i���f�������Ɍ�������j
	m_pModel->SetRot(VGet(0.0f, DX_PI_F * -0.5, 0.0f));;
	m_pModel->Update();
}

/// <summary>
/// �`��
/// </summary>
void GameObject::Draw()
{

	// ���݂��Ă��Ȃ�������`�悵�Ȃ�
	if (IsExist())
	{
		// �RD���f���̃|�W�V�����ݒ�
		m_pModel->SetPos(m_pos);
		m_pModel->Draw();
	}

}

// �͈͊O�������瑶�݂�����
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
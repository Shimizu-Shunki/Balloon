// ============================================
// 
// �t�@�C����: FixedCamera.cpp
// �T�v: �Œ�J����
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Cameras/FixedCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
FixedCamera::FixedCamera(const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& rotation)
	:
	m_transform{},
	m_up{},
	m_view{}
{
	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// ���W��ݒ�
	m_transform->SetLocalPosition(position);
	// ��]��ݒ�
	m_transform->SetLocalRotation(rotation);
}

/// <summary>
/// ����������
/// </summary>
void FixedCamera::Initialize()
{
	// �^�[�Q�b�g�͐���
	DirectX::SimpleMath::Vector3 target =
		DirectX::SimpleMath::Vector3::Backward;
	// ��]��K��
	target = DirectX::SimpleMath::Vector3::Transform(target, m_transform->GetLocalRotation());

	// �^�[�Q�b�g���W��ݒ肷�� �X�P�[�����^�[�Q�b�g�Ƃ��Ă݂�
	m_transform->SetLocalScale(m_transform->GetLocalPosition() + target);
	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �r���[�s����쐬
	this->CalculateViewMatrix();
}

/// <summary>
/// �X�V����
/// </summary>
void FixedCamera::Update()
{
	// �Œ�J�����̂��ߍX�V�͂Ȃ�
}

/// <summary>
/// �r���[�s����쐬
/// </summary>
/// <returns>�r���[�s��</returns>
DirectX::SimpleMath::Matrix FixedCamera::CalculateViewMatrix()
{
	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	return m_view;
}
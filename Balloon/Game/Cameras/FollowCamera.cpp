#include "Framework/pch.h"
#include "Game/Cameras/FollowCamera.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="target">�Ǐ]�ΏۂƂȂ�I�u�W�F�N�g�� Transform �|�C���^</param>
/// <param name="distance">�^�[�Q�b�g�Ƃ̑��ΓI�Ȉʒu�i�I�t�Z�b�g�����j</param>
FollowCamera::FollowCamera(Transform* target, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(target),
	m_distance(distance),
	m_transform{},
	m_up{},
	m_view{}
{
}

/// <summary>
/// ����������
/// </summary>
void FollowCamera::Initialize()
{
	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// ������
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �r���[�s����쐬
	this->CalculateViewMatrix();
}

/// <summary>
/// �X�V����
/// </summary>
void FollowCamera::Update()
{
	// �r���[�s����X�V
	this->CalculateViewMatrix();
}

/// <summary>
/// �r���[�s����쐬
/// </summary>
/// <returns>�r���[�s��</returns>
DirectX::SimpleMath::Matrix FollowCamera::CalculateViewMatrix()
{
	// �v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 position = m_targetTransform->GetLocalPosition();

	// ���݂̊p�x�Ɋ�Â��ăJ�����̋�����ϊ����A�J�����̈ʒu���v�Z
	DirectX::SimpleMath::Vector3 CameraPosition =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_targetTransform->GetLocalRotation());

	// ���_ (�J�����̈ʒu)
	m_transform->SetLocalPosition(position + CameraPosition);

	// �����_ (�J����������ڕW�̈ʒu) - �v���C���[�̈ʒu
	m_transform->SetLocalScale(position);

	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	return m_view;
}
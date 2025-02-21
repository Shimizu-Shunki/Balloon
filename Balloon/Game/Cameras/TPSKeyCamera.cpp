#include "Framework/pch.h"
#include "Game/Cameras/TPSKeyCamera.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include <Mouse.h>



TPSKeyCamera::TPSKeyCamera(Transform* targetTransform, PhysicsBody* targetPhysicsBody, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(targetTransform),
	m_targetPhysicsBody(targetPhysicsBody),
	m_distance(distance),
	m_initialRotation{},
	m_up{},
	m_view{},
	m_sensitivity{}
{
}

void TPSKeyCamera::Initialize()
{
	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// ������
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// ���x��ݒ�
	m_sensitivity = 0.0009f;

	m_pitch = 0.0f;

	// ������]�p��ݒ�
	m_initialRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	// �}�E�X�𑊑΃��[�h�ɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSKeyCamera::Update()
{
	// ���x���擾
	DirectX::SimpleMath::Vector3 velocity = m_targetPhysicsBody->GetVelocity();

	DirectX::SimpleMath::Vector3 angle = m_targetTransform->GetLocalRotation().ToEuler();

	// �^�[�Q�b�g�̉�]���l������
	m_yaw  = angle.y + DirectX::XMConvertToRadians(180.0f);

	float targetPitch = BASE_PITCH - (-velocity.y * PITCH_OFFSET_FACTOR);
	// ������K�p
	targetPitch = std::clamp(targetPitch, MIN_PITCH, MAX_PITCH);
	// ��� (�X���[�Y�ȕω�) - LERP
	const float interpolationSpeed = 0.03f; // 0.0�`1.0�͈̔͂Œ����i�������قǂ�������ԁj
	m_pitch = (1.0f - interpolationSpeed) * m_pitch + interpolationSpeed * targetPitch;

	// ���[�p�ƃs�b�`�p�Ɋ�Â��ăN�H�[�^�j�I�����쐬���A���݂̊p�x���X�V
	DirectX::SimpleMath::Quaternion rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);

	// ��]���X�V
	m_transform->SetLocalRotation(m_initialRotation * rotation);
	

	// �r���[�s����쐬
	this->CalculateViewMatrix();
}

// �r���[�s����v�Z����
DirectX::SimpleMath::Matrix  TPSKeyCamera::CalculateViewMatrix()
{
	// �v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 position = m_targetTransform->GetLocalPosition();

	// ���݂̊p�x�Ɋ�Â��ăJ�����̋�����ϊ����A�J�����̈ʒu���v�Z
	DirectX::SimpleMath::Vector3 CameraPosition =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_transform->GetLocalRotation());

	// ���_ (�J�����̈ʒu)
	m_transform->SetLocalPosition(position + CameraPosition);
	// �����_ (�J����������ڕW�̈ʒu) - �v���C���[�̈ʒu
	m_transform->SetLocalScale(position);
	
	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(
		m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	// �r���[�s���ݒ�
	return m_view;
}
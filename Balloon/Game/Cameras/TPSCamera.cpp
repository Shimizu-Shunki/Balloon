#include "Framework/pch.h"
#include "Game/Cameras/TPSCamera.h"
#include <Mouse.h>

#include "Framework/InputManager.h"

TPSCamera::TPSCamera(Transform* targetTransform, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(targetTransform),
	m_distance(distance),
	m_initialRotation{},
	m_up{},
	m_view{},
	m_sensitivity{},
	m_pitch{},
	m_yaw{}
{
	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾����
	m_inputManager = InputManager::GetInstance();
}

void TPSCamera::Initialize()
{
	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// ������
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// ������
	m_yaw   = 0.0f;
	m_pitch = 0.0f;

	// ���x��ݒ�
	m_sensitivity = 0.0009f;

	// ������]�p��ݒ�
	m_initialRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	// �}�E�X�𑊑΃��[�h�ɂ���
	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSCamera::Update()
{
	// �}�E�X�X�e�[�g
	const DirectX::Mouse::State& mouseState = m_inputManager->GetMouse()->GetState();

	if (mouseState.positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		// �}�E�X�̉������̓����Ɋ�Â��ă��[�p���X�V
		m_yaw   -= m_inputManager->GetMouseTracker()->GetLastState().x * m_sensitivity;
		// �}�E�X�̏c�����̓����Ɋ�Â��ăs�b�`�p���X�V
		m_pitch -= m_inputManager->GetMouseTracker()->GetLastState().y * m_sensitivity;

		// �s�b�`�p�̐���: -90�x����90�x
		const float pitchLimit = DirectX::XM_PIDIV2 - 0.01f; // 90�x - �}�[�W��
		m_pitch = std::clamp(m_pitch, -pitchLimit, pitchLimit);

		// ���[�p�ƃs�b�`�p�Ɋ�Â��ăN�H�[�^�j�I�����쐬���A���݂̊p�x���X�V
		DirectX::SimpleMath::Quaternion rotation =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);

		// ��]���X�V
		m_transform->SetLocalRotation(m_initialRotation * rotation);
	}

	// �r���[�s����쐬
	this->CalculateViewMatrix();

#ifdef _DEBUG
	// �}�E�X���[�h���΃��[�h
	if (m_inputManager->OnKeyDown(InputManager::Keys::W))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
	}
	// �}�E�X���[�h�𑍑̃��[�h
	if (m_inputManager->OnKeyDown(InputManager::Keys::Z))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
	}
#endif
}

// �r���[�s����v�Z����
DirectX::SimpleMath::Matrix  TPSCamera::CalculateViewMatrix()
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
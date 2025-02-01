#include "pch.h"
#include "Game/Camera/TPSCamera.h"

#include "Framework/Graphics.h"
#include "Framework/InputManager.h"

TPSCamera::TPSCamera()
	:
	m_position{},
	m_initialRotation{},
	m_currentRotation{},
	m_targetPosition{},
	m_up{},
	m_distance{},
	m_targetObjectPosition{},
	m_view{},
	m_sensitivity{},
	m_pitch{},
	m_yaw{}
{
	// �O���t�B�b�N�X�̃C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾����
	m_inputManager = InputManager::GetInstance();
}


TPSCamera::~TPSCamera()
{

}


void TPSCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation)
{
	// �^�[�Q�b�g����̋���
	m_distance = { 0.0f,5.0f, 7.0f };

	// ������
	m_yaw = 0.0f;
	m_pitch = 0.0f;

	// ���x��ݒ�
	m_sensitivity = 0.0009f;

	// ������]�p��ݒ�
	m_initialRotation = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSCamera::Update(const float& deltaTime)
{
	m_targetObjectPosition = m_targetObject->GetPosition();

	if (m_inputManager->GetMouseState().positionMode == DirectX::Mouse::MODE_RELATIVE)
	{
		// �}�E�X�̉������̓����Ɋ�Â��ă��[�p���X�V
		m_yaw   -= m_inputManager->GetMouseTracker()->GetLastState().x * m_sensitivity;
		// �}�E�X�̏c�����̓����Ɋ�Â��ăs�b�`�p���X�V
		m_pitch -= m_inputManager->GetMouseTracker()->GetLastState().y * m_sensitivity;

		// ���[�p�ƃs�b�`�p�Ɋ�Â��ăN�H�[�^�j�I�����쐬���A���݂̊p�x���X�V
		DirectX::SimpleMath::Quaternion rotation =
			DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);
		m_currentRotation = m_initialRotation * rotation;
	}

	// �Œ�J�����̂��ߏ������̎��_�̂݃r���[�s����쐬����
	this->CalculateViewMatrix();

#ifdef _DEBUG
	// �}�E�X���[�h���΃��[�h
	if (m_inputManager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::X))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_ABSOLUTE);
	}
	// �}�E�X���[�h�𑍑̃��[�h
	if (m_inputManager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Z))
	{
		DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
	}
#endif
}

// �r���[�s����v�Z����
void TPSCamera::CalculateViewMatrix()
{
	// �v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 position = m_targetObjectPosition;

	// ���݂̊p�x�Ɋ�Â��ăJ�����̋�����ϊ����A�J�����̈ʒu���v�Z
	DirectX::SimpleMath::Vector3 camera_position =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_currentRotation);

	// ���_ (�J�����̈ʒu)
	m_position = position + camera_position;

	// �����_ (�J����������ڕW�̈ʒu) - �v���C���[�̈ʒu
	m_targetPosition = position;
	// �J�����̓�
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_targetPosition, m_up);
	// �r���[�s���ݒ�
	m_graphics->SetViewMatrix(m_view);
}
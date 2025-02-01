#include "pch.h"
#include "Game/Camera/TPSCamera2.h"
#include "Framework/Graphics.h"
#include "Framework/InputManager.h"

TPSCamera2::TPSCamera2()
{

}

TPSCamera2::~TPSCamera2()
{

}

void TPSCamera2::Initialize()
{
	// �^�[�Q�b�g����̋���
	m_distance = { 0.0f,3.0f,5.0f };

	// ������
	m_yaw = 0.0f;
	m_pitch = 0.0f;

	// ���x��ݒ�
	m_sensitivity = 0.0009f;

	// ������]�p��ݒ�
	m_initial_angle = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(0.78f));

	DirectX::Mouse::Get().SetMode(DirectX::Mouse::MODE_RELATIVE);
}

void TPSCamera2::Update(float elapsed_time, DirectX::SimpleMath::Vector3 const& position)
{
	// �^�[�Q�b�g�̍��W
	m_targetObjectPosition = position;

	// �}�E�X�̉������̓����Ɋ�Â��ă��[�p���X�V
	m_yaw   -= m_inputManager->GetMouseTracker()->GetLastState().x * m_sensitivity;
	// �}�E�X�̏c�����̓����Ɋ�Â��ăs�b�`�p���X�V
	m_pitch -= m_inputManager->GetMouseTracker()->GetLastState().y * m_sensitivity;

	// ���[�p�ƃs�b�`�p�Ɋ�Â��ăN�H�[�^�j�I�����쐬���A���݂̊p�x���X�V
	DirectX::SimpleMath::Quaternion rotation =
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(m_yaw, m_pitch, 0);
	m_current_angle = m_initial_angle * rotation;


	// ��
	if (MIN_VALUE >= position.y)
	{

	}
	// ����
	else if (MEDIAN_VALUE >= position.y)
	{

	}
	// ��
	else
	{

	}
}

void TPSCamera2::CalculateViewMatrix()
{
	// �v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 position = m_targetObjectPosition;

	// ���݂̊p�x�Ɋ�Â��ăJ�����̋�����ϊ����A�J�����̈ʒu���v�Z
	DirectX::SimpleMath::Vector3 camera_position =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_current_angle);

	// ���_ (�J�����̈ʒu)
	m_eye = position + camera_position;

	// �����_ (�J����������ڕW�̈ʒu) - �v���C���[�̈ʒu
	m_target = position;
	// �J�����̓�
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �J�����̃r���[�s����쐬
	m_graphics->SetViewMatrix(DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, m_up));
}
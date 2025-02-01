#include "pch.h"
#include "Game/Camera/FollowCamera.h"
#include "Game/Camera/FollowCamera.h"
#include "Framework/Graphics.h"

FollowCamera::FollowCamera(DirectX::SimpleMath::Vector3 distance)
	:
	m_distance(distance),
	m_position{},
	m_targetPosition{},
	m_rotation{},
	m_up{},
	m_view{}
{
	// �O���t�B�b�N�̃C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation)
{
	// ���W��ݒ肷��
	m_position = position;
	// �^�[�Q�b�g���W��ݒ肷��
	m_targetPosition = targetPosition;
	// ��]�p��ݒ肷��
	m_rotation = rotation;
	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �Œ�J�����̂��ߏ������̎��_�̂݃r���[�s����쐬����
	this->CalculateViewMatrix();
}

void FollowCamera::Update(const float& deltaTime)
{
	// �^�[�Q�b�g�̍��W��ݒ�
	m_targetObjectPosition = m_targetObject->GetPosition();
	// �^�[�Q�b�g�̉�]�p��ݒ�
	m_rotation = m_targetObject->GetAngle();
	// �Œ�J�����̂��ߏ������̎��_�̂݃r���[�s����쐬����
	this->CalculateViewMatrix();
}

void FollowCamera::CalculateViewMatrix()
{
	// �v���C���[�̍��W���擾
	DirectX::SimpleMath::Vector3 position = m_targetObjectPosition;

	// ���݂̊p�x�Ɋ�Â��ăJ�����̋�����ϊ����A�J�����̈ʒu���v�Z
	DirectX::SimpleMath::Vector3 camera_position =
		DirectX::SimpleMath::Vector3::Transform(m_distance, m_rotation);

	// ���_ (�J�����̈ʒu)
	//m_position = position + camera_position;

	// �����_ (�J����������ڕW�̈ʒu) - �v���C���[�̈ʒu
	m_targetPosition = position;
	// �J�����̓�
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_targetPosition, m_up);
	// �r���[�s���ݒ�
	m_graphics->SetViewMatrix(m_view);
}
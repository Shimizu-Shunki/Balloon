#include "Framework/pch.h"
#include "Game/Cameras/FixedCamera.h"


FixedCamera::FixedCamera()
	:
	m_transform{},
	m_up{},
	m_view{}
{
}

FixedCamera::~FixedCamera()
{

}

void FixedCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager)
{
	// �J�����}�l�[�W���[�̃C���X�^���X���擾����
	m_cameraManager = cameraManager;

	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// ���W��ݒ肷��
	m_transform->SetLocalPosition(position);

	// �^�[�Q�b�g���W
	// ��]��ݒ�
	m_transform->SetLocalRotation(rotation);
	// �^�[�Q�b�g�͐���
	DirectX::SimpleMath::Vector3 target =
		DirectX::SimpleMath::Vector3::Backward;
	// ��]��K��
	target = DirectX::SimpleMath::Vector3::Transform(target, rotation);

	// �^�[�Q�b�g���W��ݒ肷�� �X�P�[�����^�[�Q�b�g�Ƃ��Ă݂�
	m_transform->SetLocalScale(position + target);
	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �Œ�J�����̂��ߏ������̎��_�̂݃r���[�s����쐬����
	m_cameraManager->SetViewMatrix(this->CalculateViewMatrix());
}

void FixedCamera::Update()
{
	// �Œ�J�����̂��ߍX�V�͂Ȃ�
}

DirectX::SimpleMath::Matrix FixedCamera::CalculateViewMatrix()
{
	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_transform->GetLocalPosition(), m_transform->GetLocalScale(), m_up);

	return m_view;
}
#include "Framework/pch.h"
#include "Game/Cameras/FollowCamera.h"

FollowCamera::FollowCamera(Transform* target, DirectX::SimpleMath::Vector3 distance)
	:
	m_targetTransform(target),
	m_distance(distance),
	m_transform{},
	m_up{},
	m_view{}
{
}

FollowCamera::~FollowCamera()
{

}

void FollowCamera::Initialize(
	const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& targetPosition,
	const DirectX::SimpleMath::Quaternion& rotation, CameraManager* cameraManager)
{
	// �J�����}�l�[�W���[�̃C���X�^���X���擾����
	m_cameraManager = cameraManager;

	// Transform���쐬
	m_transform = std::make_unique<Transform>();

	// ������
	m_transform->SetLocalPosition(DirectX::SimpleMath::Vector3::Zero);
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::Zero);

	// ���̌�����ݒ肷��
	m_up = DirectX::SimpleMath::Vector3::Up;

	// �Œ�J�����̂��ߏ������̎��_�̂݃r���[�s����쐬����
	m_cameraManager->SetViewMatrix(this->CalculateViewMatrix());
}

void FollowCamera::Update()
{
	// �r���[�s����X�V
	m_cameraManager->SetViewMatrix(this->CalculateViewMatrix());
}

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
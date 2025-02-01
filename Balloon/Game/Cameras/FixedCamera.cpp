#include "pch.h"
#include "Game/Camera/FixedCamera.h"
#include "Framework/Graphics.h"

FixedCamera::FixedCamera()
	:
	m_position{},
	m_targetPosition{},
	m_rotation{},
	m_up{},
	m_view{}
{
	// �O���t�B�b�N�̃C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
}

FixedCamera::~FixedCamera()
{

}

void FixedCamera::Initialize(
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

void FixedCamera::Update(const float& deltaTime)
{
	// �Œ�J�����̂��ߍX�V�͂Ȃ�
}

void FixedCamera::CalculateViewMatrix()
{
	// �r���[�s����쐬
	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_position, m_targetPosition, m_up);
	// �r���[�s���ݒ�
	m_graphics->SetViewMatrix(m_view);
}
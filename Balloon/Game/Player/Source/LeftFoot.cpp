#include "pch.h"
#include "Game/Player/Header/LeftFoot.h"
#include "Game/Player/Character.h"
#include "Framework/CollisionManager.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/InputManager.h"
#include "Game/Player/Enemy.h"
#include "Game/Collider/Collider.h"
#include "Game/Player/Hand.h"
#include "Game/Player/Jump.h"
#include "Framework/Resources.h"


LeftFoot::LeftFoot(CollisionManager* collisionManger, IComponent* parent, const int balloonIndex, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
{
	m_collisionManager = collisionManger;
	m_inputManager = InputManager::GetInstance();
}

LeftFoot::~LeftFoot()
{

}


void LeftFoot::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;

	m_isKinematic = false;

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = ObjectID::PLAYER;

	// ���݂̍��W��������
	m_currentPosition = m_initialPosition;
	// ���݂̉�]��������
	m_rotationTurretAngle = m_initialAngle;
	// �傫����������
	m_scale = DirectX::SimpleMath::Vector3::One;

	// ���f�����擾����
	m_model = Resources::GetInstance()->GetPlayerLeftFootModel();
}

void LeftFoot::Update(const float elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{




	// �����蔻��̍X�V
	for (auto& collider : m_colliders)
	{
		collider->Update(m_currentPosition);
	}
	// �q�I�u�W�F�N�g���X�V����
	for (auto& child : m_child)
	{
		// ���D���X�V����
		child->Update(elapsedTime, m_currentPosition, m_currentAngle);
	}
}

// �`�揈��
void LeftFoot::Render()
{
	// �����蔻��̍X�V
	for (auto& collider : m_colliders)
	{
		collider->DebugRender();
	}
	// �q�I�u�W�F�N�g��`�悷��
	for (auto& childes : m_child)
	{
		// �q�I�u�W�F�N�g��`�悷��
		childes->Render();
	}
}

void LeftFoot::Attach(std::unique_ptr<IComponent> turretParts)
{
	// �C�����i��ǉ�����
	turretParts->Initialize(IComponent::ObjectID::BALLOON, true);
	// �q�I�u�W�F�N�g���A�^�b�`
	m_child.emplace_back(std::move(turretParts));
}

void LeftFoot::OnCollisionEnter(IComponent* component)
{
	m_gravity = 0.0f;
	m_velocity.y = 0.0f;
	m_isGravity = false;
}

void LeftFoot::OnCollisionStay(IComponent* component)
{

}

void LeftFoot::OnCollisionExit(IComponent* component)
{
	m_isGravity = true;
}



void LeftFoot::OnTriggerEnter(IComponent* component)
{
}
void LeftFoot::OnTriggerStay(IComponent* component)
{
}
void LeftFoot::OnTriggerExit(IComponent* component)
{
}



void LeftFoot::Detach(std::unique_ptr<IComponent> turretParts)
{

}

void LeftFoot::Finalize()
{

}



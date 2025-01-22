#include "pch.h"
#include "Game/Player/Player.h"
#include "Game/Player/Character.h"
#include "Framework/CollisionManager.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/InputManager.h"
#include "Game/Player/Enemy.h"
#include "Game/Collider/Collider.h"
#include "Game/Player/Hand.h"
#include "Game/Player/Jump.h"


Player::Player(ICamera* camera,IComponent* parent, const int balloonIndex, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle)
	:
	m_parent(parent),
	m_balloonIndex(balloonIndex),
	m_initialPosition(initialPosition),
	m_initialAngle(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::Up, initialAngle))
{
	
	m_inputManager = InputManager::GetInstance();
	m_camera = camera;
}

Player::~Player()
{

}


void Player::Initialize(ObjectID objectID, const bool& active)
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

	// �W�����v�����쐬
	m_jump = std::make_unique<Jump>();
	m_jump->Initialize();

	
	// �L�����N�^�[���A�^�b�`����
	this->Attach(std::make_unique<Character>());
	// ���D�̏������W
	DirectX::SimpleMath::Vector3 initPosition = { 0.0f,1.0f,0.0f };
	// ���D�̐��ɉ����Đ�������
	for (int i = 0; i < m_balloonIndex; i++)
	{
		// ���D���A�^�b�`����
		this->Attach(std::make_unique<Balloon>(this,initPosition,DirectX::XMConvertToRadians(20.0f * static_cast<float>(i) - 20.0f) ));
	}

	// ����A�^�b�`
	this->Attach(std::make_unique<Hand>());

	// �����蔻�萶��
	std::unique_ptr<Collider> collider = std::make_unique<Collider>();
	collider->Initialize<DirectX::BoundingBox>(DirectX::SimpleMath::Vector3::Up * 0.5f, DirectX::SimpleMath::Vector3::One / 2.0f);

	// �i�[
	m_colliders.push_back(std::move(collider));

	collider = std::make_unique<Collider>();
	collider->Initialize<DirectX::BoundingSphere>(DirectX::SimpleMath::Vector3::Up * 2.0f, DirectX::SimpleMath::Vector3::One / 2.0f , true);

	// �i�[
	m_colliders.push_back(std::move(collider));
}

void Player::Update(const float elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle)
{
	// ���͂Ɋ�Â������x�N�g�����擾
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(m_camera->GetRotation());

	if (movementDirection.LengthSquared() > 0.0f)
	{
		// ���͂�����ꍇ�F������K�p
		m_velocity += movementDirection * 20.0f * elapsedTime;

		// ���C����߂�
		m_velocity.x *= 0.95f; // ���͂�����Ƃ��̖��C
		m_velocity.z *= 0.95f; // ���͂�����Ƃ��̖��C
	}
	else
	{
		// ���͂��Ȃ��ꍇ�F���C�����߂�
		m_velocity.x *= 0.85f; // ���͂��Ȃ��Ƃ��̖��C
		m_velocity.z *= 0.85f; // ���͂��Ȃ��Ƃ��̖��C
	}

	// �d�͂��L���ŃL�l�}�e�B�b�N�o�Ȃ���
	if (m_isGravity && !m_isKinematic)
	{
		// �d�͐��l
		m_gravity = ( - 9.81f + 2.0f * m_balloonIndex) * elapsedTime;
		// �d�͂𑬓x�ɉ��Z
		m_velocity.y = m_velocity.y + m_gravity;
	}

	// �W�����v����
	if (m_inputManager->GetKeyboardTracker()->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_velocity.y += m_jump->TryJump(elapsedTime);
	}

	m_jump->Update(elapsedTime);
	// ���W�ɑ��x�����Z����
	m_currentPosition += m_velocity * elapsedTime;

	// �����蔻��̍X�V
	for (auto& collider : m_colliders)
	{
		collider->Update(m_currentPosition);
	}


	// ���D���X�V����
	for (auto& child : m_child)
	{
		// ���D���X�V����
		child->Update(elapsedTime, m_currentPosition, m_rotationTurretAngle);
	}
}

// �`�揈��
void Player::Render()
{

	// this->DebugImguiRender();
	m_jump->Render();
	m_jump->DebugRender();
	// �����蔻��f�o�b�O�`��
	// �����蔻��̍X�V
	for (auto& collider : m_colliders)
	{
		//collider->DebugRender();
	}

	// �q�I�u�W�F�N�g��`�悷��
	for (auto& childes : m_child)
	{
		// �q�I�u�W�F�N�g��`�悷��
		childes->Render();
	}
}

void Player::Attach(std::unique_ptr<IComponent> turretParts)
{
	// �C�����i��ǉ�����
	turretParts->Initialize(IComponent::ObjectID::BALLOON, true);
	//m_collisionManager->Attach(turretParts.get());
	m_child.emplace_back(std::move(turretParts));
}

void Player::OnCollisionEnter(IComponent* component)
{
	m_gravity = 0.0f;
	m_velocity.y = 0.0f;
	m_isGravity = false;
}



void Player::OnCollisionStay(IComponent* component)
{

}

void Player::OnCollisionExit(IComponent* component)
{
	m_isGravity = true;
}

void Player::OnTriggerEnter(IComponent* component)
{
	// �v���C���[������������
 	if (component->GetObjectID() == ObjectID::ENEMY)
	{
		this->BalloonDetach();
	}

	
}

//void Player::OnTriggerStay(IComponent* component)
//{
//
//}
//
//void Player::OnTriggerExit(IComponent* component)
//{
//
//}



void Player::RecoverJump()
{
	// �W�����v���s��ꂽ�Ƃ�
	if (m_jumpIndex != 10)
	{
		// �W�����v�񐔂̉�

	}
}




void Player::Detach(std::unique_ptr<IComponent> turretParts)
{

}

void Player::Finalize()
{

}

void Player::BalloonDetach()
{
	// �o���[�����\���ɂ���
	// bool true false ���G��Ԃ����
	// ���ׂĂ̕��D���Ȃ��ꍇ�@������x�̑��x�œ��ނƎ��ʁ@������
	if (m_balloonIndex != 0)
	{
		m_child[m_balloonIndex - 1]->SetIsActive(false);
		m_balloonIndex--;
	}
}

// �ړ��������擾����
DirectX::SimpleMath::Vector3 Player::GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle)
{
	// ����
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	// ��L�[
	if (m_inputManager->GetKeyboardState().W)
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// ���L�[
	if (m_inputManager->GetKeyboardState().S)
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// �E�L�[
	if (m_inputManager->GetKeyboardState().D)
	{
		direction += DirectX::SimpleMath::Vector3::Right;
	}
	// ���L�[
	if (m_inputManager->GetKeyboardState().A)
	{
		direction += DirectX::SimpleMath::Vector3::Left;
	}

	// �v���C���[�̉�]�p�i�N�H�[�^�j�I���j�Ɋ�Â��ĕ�������]������
	direction = DirectX::SimpleMath::Vector3::Transform(direction, angle);

	// Y�������[���ɂ��Đ����ʂɐ���
	direction.y = 0.0f;

	// ���K�����Ĉړ�������Ԃ�
	direction.Normalize();

	return direction;
}

void Player::DebugImguiRender()
{
	// �e�̏���\��
	ImGui::Begin("Hierarchy");

	if (ImGui::TreeNode("Player")) {
		RenderComponent(this);  // �v���C���[���g�̏���\��

		// �q�v�f���ċA�I�ɕ`��
		for (const auto& child : m_child) {
			if (ImGui::TreeNode(child.get(), "Child")) {
				RenderComponent(child.get());
				ImGui::TreePop();
			}
		}
		ImGui::TreePop();
	}

	ImGui::End();
	
}

void Player::RenderComponent(IComponent* component)
{
	// �e�̏���`��
	float position[3] = { component->GetPosition().x, component->GetPosition().y, component->GetPosition().z };
	float scale[3] = { component->GetScale().x, component->GetScale().y, component->GetScale().z };

	ImGui::Text("Position");
	ImGui::InputFloat3("##Position", position);
	ImGui::Text("Scale");
	ImGui::InputFloat3("##Scale", scale);

	// �l�𔽉f
	component->SetPosition({ position[0], position[1], position[2] });
	component->SetScale({ scale[0], scale[1], scale[2] });
}
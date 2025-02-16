#include "Framework/pch.h"
#include "Game/Player/Header/Player.h"
#include "Framework/CommonResources.h"

// �q�I�u�W�F�N�g
#include "Game/Player/Header/Body.h"
#include "Game/Balloon/Balloon.h"
// �����蔻��
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"
// ��������
#include "Game/PhysicsBody/PhysicsBody.h"

#include "Game/Jump/Jump.h"




Player::Player(ICamera* camera, IObject* parent)
	:
	m_parent(parent),
	m_camera(camera),
	m_transform{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
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
	// �v���C���[���f���͂Ȃ�
	m_model = nullptr;

	m_transform = std::make_unique<Transform>();

	// �ʒu��������
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// ��]�p��������
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	
	// �X�P�[����������
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	// �g�����X�t�H�[����e�ɐݒ�
	/*m_transform->SetParent(nullptr);*/
	// �e��Transform�Ɏ������g���q���ɐݒ�
	//m_parent->GetTransform()->SetChild(m_transform.get());
	

	// �{�f�B���A�^�b�`
	this->Attach(std::make_unique<Body>(this), ObjectID::PLAYER);
	
	// ���D���A�^�b�`
	for (int i = 0; i < 3; i++)
	{
		std::unique_ptr<IObject> balloon = std::make_unique<Balloon>(this,-20.0f + 20.0f * i);
		balloon->Initialize(ObjectID::BALLOON , true);

		m_childs.emplace_back(std::move(balloon));
	}

	

	// �����蔻���ݒ�
	m_boxCollider = std::make_unique<BoxCollider>(ICollider::ColliderType::BOX);
	m_boxCollider->SetIsActive(true);
	m_boxCollider->SetIsTrigger(false);
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,0.75 * 10.0f,0.0f });
	m_boxCollider->GetTransform()->SetLocalScale({ 1.0f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f });
	m_boxCollider->GetTransform()->SetParent(m_transform.get());
	m_transform->SetChild(m_boxCollider->GetTransform());

	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.1f);
	

	// �����蔻����}�l�[�W���[�ɓn��
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());

	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this);
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
	m_physicsBody->SetIsActive(true);
	m_physicsBody->SetMass(5.0f);
	m_physicsBody->SetUseGravity(true);
	m_physicsBody->SetIsKinematic(false);

	// �W�����v����
	m_jump = std::make_unique<Jump>(m_physicsBody.get());
	m_jump->Initialize();

	
	
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::Up, DirectX::XMConvertToRadians(180.0f)
	));
}

void Player::Update()
{
	// ���͂Ɋ�Â������x�N�g�����擾
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(DirectX::SimpleMath::Quaternion::Identity);

	m_physicsBody->SetFoce(m_physicsBody->GetFoce() + movementDirection * 100.0f);
	
	
	
	m_jump->Update();
	m_physicsBody->Update();

	// �q�����X�V����
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void Player::Finalize() {}


void Player::Attach(std::unique_ptr<IObject> turretParts , IObject::ObjectID objectId)
{
	// �p�[�c�̏�����
	turretParts->Initialize(objectId, true);
	// �q���ɓo�^
	m_childs.emplace_back(std::move(turretParts));
}


void Player::Detach(std::unique_ptr<IObject> turretParts)
{

}

void Player::OnCollisionEnter(IObject* object) { (void)object; }
void Player::OnCollisionStay(IObject* object)  { (void)object; }
void Player::OnCollisionExit(IObject* object)  { (void)object; }
void Player::OnTriggerEnter(IObject* object)   { (void)object; }
void Player::OnTriggerStay(IObject* object)    { (void)object; }
void Player::OnTriggerExit(IObject* object)    { (void)object; }
											   

// �ړ��������擾����
DirectX::SimpleMath::Vector3 Player::GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle)
{
	// �L�[�{�[�h�X�e�[�g
	InputManager* input = m_commonResources->GetInputManager();

	// ����
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	// ��L�[
	if (input->OnKey(InputManager::Keys::W))
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// ���L�[
	if (input->OnKey(InputManager::Keys::S))
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// �E�L�[
	if (input->OnKey(InputManager::Keys::D))
	{
		direction += DirectX::SimpleMath::Vector3::Right;
	}
	// ���L�[
	if (input->OnKey(InputManager::Keys::A))
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
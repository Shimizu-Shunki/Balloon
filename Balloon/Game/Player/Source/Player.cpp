#include "Framework/pch.h"
#include "Game/Player/Header/Player.h"
#include "Framework/CommonResources.h"
#include "Game/Cameras/TPSKeyCamera.h"
#include "Interface/ICamera.h"
#include "Game/Player/Header/Body.h"
#include "Game/Balloon/Balloon.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Game/Jump/Jump.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="parent">�e�I�u�W�F�N�g</param>
Player::Player(IObject* parent)
	:
	m_parent(parent),
	m_childs{},
	m_objectId{},
	m_isActive{},
	m_transform{},
	m_physicsBody{},
	m_boxCollider{},
	m_sphereCollider{},
	m_balloonIndex{},
	m_jump{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);
}

/// <summary>
/// ����������
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="active">�A�N�e�B�u�ݒ�</param>
void Player::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;


	// �q�I�u�W�F�N�g�𐶐�
	this->CreateChildObjects();
	// �����蔻��𐶐�
	this->CreateCollider();
	// ���������𐶐�
	this->CreatePhysicsBody();

	
	// �W�����v����
	m_jump = std::make_unique<Jump>(m_physicsBody.get());
	m_jump->Initialize();

	// TPS�J�����𐶐�
	//std::unique_ptr<ICamera> camera = std::make_unique<TPSKeyCamera>(
	//	m_transform.get(), m_physicsBody.get(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 10.0f));
	//// �J������������
	//camera->Initialize();
	// �J�������}�l�[�W���[�ɐݒ�
	//m_commonResources->GetCameraManager()->Attach(std::move(camera));


	// Tween �A�j���[�V�������J�n
	//m_transform->GetTween()->DOMove(DirectX::SimpleMath::Vector3::One, 2.0f)  // (1,1,1) �̍��W�� 2.0�b�����Ĉړ�
	//	.SetDelay(3.0f)                                                       // 3.0�b�̒x����ݒ�i�J�n�O�̑ҋ@���ԁj
	//	.SetEase(Tween::EasingType::EaseOutSine)                              // �C�[�W���O�֐���ݒ�
	//	.SetLoops(3, Tween::LoopType::Yoyo)                                   // 3��J��Ԃ� (Yoyo = �s�����藈����)
	//	.OnComplete([this] {                                                  // �A�j���[�V�����������̃R�[���o�b�N�֐�
	//	// �����ɃA�j���[�V�����I����̏���������
	//	});


}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Player::InitialTransform(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// �ʒu��������
	m_transform->SetLocalPosition(position);
	// ��]�p��������
	m_transform->SetLocalRotation(rotation);
	// �X�P�[����������
	m_transform->SetLocalScale(scale);
}

/// <summary>
/// �X�V����
/// </summary>
void Player::Update()
{
	// ���͂Ɋ�Â������x�N�g�����擾
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(DirectX::SimpleMath::Quaternion::Identity);

	m_physicsBody->SetFoce(m_physicsBody->GetFoce() + movementDirection * 100.0f);
	
	m_jump->Update();
	m_physicsBody->Update();

	// �q���I�u�W�F�N�g�𐶐�
	for (const auto& object : m_childs)
	{
		object->Update();
	}
}

/// <summary>
/// �I������
/// </summary>
void Player::Finalize() 
{

}


/// <summary>
/// �A�^�b�`
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Player::Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// �I�u�W�F�N�g�̏�����
	object->Initialize(objectId, true);
	// �I�u�W�F�N�g��Transform��������
	object->InitialTransform(position, rotation, scale);

	// �q���ɓo�^
	m_childs.emplace_back(std::move(object));
}

/// <summary>
/// �f�^�b�`
/// </summary>
/// <param name="turretParts">�I�u�W�F�N�g</param>
void Player::Detach(std::unique_ptr<IObject> turretParts)
{

}

void Player::OnCollisionEnter(IObject* object) { (void)object; }
void Player::OnCollisionStay(IObject* object)  { (void)object; }
void Player::OnCollisionExit(IObject* object)  { (void)object; }
void Player::OnTriggerEnter(IObject* object)   { (void)object; }
void Player::OnTriggerStay(IObject* object)    { (void)object; }
void Player::OnTriggerExit(IObject* object)    { (void)object; }

/// <summary>
/// �q�I�u�W�F�N�g�𐶐�
/// </summary>
void Player::CreateChildObjects()
{
	// �̃I�u�W�F�N�g�𐶐�
	this->Attach(std::make_unique<Body>(this), ObjectID::PLAYER_BODY);

	// ���D�̐���ݒ�
	m_balloonIndex = 3;

	// ���D�𐶐�
	for (int i = 0; i < m_balloonIndex; i++)
	{
		this->Attach(std::make_unique<Balloon>(this), ObjectID::BALLOON,
			DirectX::SimpleMath::Vector3( 0.0f,3.0f,-0.2f ),
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::Forward,DirectX::XMConvertToRadians(-20.0f + 20.0f * i)) *
			DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
				DirectX::SimpleMath::Vector3::UnitX, DirectX::XMConvertToRadians(-20.0f)
			),
			DirectX::SimpleMath::Vector3::One * 0.03f
			);
	}
}

/// <summary>
/// �����蔻����쐬
/// </summary>
void Player::CreateCollider()
{
	// BoxCollider
	// �̗p�̓����蔻��
	m_boxCollider = std::make_unique<BoxCollider>();                                           // �����蔻��𐶐�
	m_boxCollider->SetIsActive(true);                                                          // �A�N�e�B�u�ݒ�
	m_boxCollider->SetIsTrigger(false);                                                        // �g���K�[�ݒ�
	m_boxCollider->GetTransform()->SetLocalPosition({ 0.0f,0.75 * 10.0f,0.0f });               // ���W�ݒ�
	m_boxCollider->GetTransform()->SetLocalScale({ 1.0f * 10.0f,1.5f * 10.0f ,1.0f * 10.0f }); // �X�P�[���ݒ�
	m_boxCollider->GetTransform()->SetParent(m_transform.get());                               // �e��Transform��ݒ�
	// SphereCollider
	// ���D�p�̓����蔻���ݒ�
	m_sphereCollider = std::make_unique<SphereCollider>();                                     // �����蔻��𐶐�
	m_sphereCollider->SetIsActive(true);                                                       // �A�N�e�B�u�ݒ�
	m_sphereCollider->SetIsTrigger(true);                                                      // �g���K�[�ݒ�
	m_sphereCollider->GetTransform()->SetLocalPosition({ 0.0f,2.0f * 10.0f,-0.6f * 10.0f });   // ���W��ݒ�
	m_sphereCollider->GetTransform()->SetLocalScale({ 0.4f * 10.0f,0.0f ,0.0f });              // �X�P�[���ݒ�
	m_sphereCollider->GetTransform()->SetParent(m_transform.get());                            // �e��Transform��ݒ�

	// �����蔻����}�l�[�W���[�ɓn��
	m_commonResources->GetCollisionManager()->Attach(this, m_boxCollider.get());
	m_commonResources->GetCollisionManager()->Attach(this, m_sphereCollider.get());
}

/// <summary>
/// �����������쐬
/// </summary>
void Player::CreatePhysicsBody()
{
	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this); // ���������𐶐�
	m_physicsBody->SetIsActive(true);                    // �A�N�e�B�u�ݒ�
	m_physicsBody->SetMass(5.0f);                        // ���ʂ�ݒ�
	m_physicsBody->SetUseGravity(true);                  // �d�͐ݒ�
	m_physicsBody->SetIsKinematic(false);                // �L�l�}�e�B�b�N�ݒ�

	// �����蔻��ɕ������������n��
	m_commonResources->GetCollisionManager()->PhysicsAttach(this, m_physicsBody.get());
}
											   

// �ړ��������擾����
DirectX::SimpleMath::Vector3 Player::GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle)
{
	// �L�[�{�[�h�X�e�[�g
	InputManager* input = m_commonResources->GetInputManager();

	// ����
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity;

	// ��L�[
	if (input->OnKey(InputManager::Keys::Up))
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// ���L�[
	if (input->OnKey(InputManager::Keys::Down))
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// �E�L�[
	if (input->OnKey(InputManager::Keys::Right))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(-2.0f));
	}
	// ���L�[
	if (input->OnKey(InputManager::Keys::Left))
	{
		rotation *= DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(2.0f));
	}

	m_transform->SetLocalRotation(m_transform->GetLocalRotation() * rotation);

	// �v���C���[�̉�]�p�i�N�H�[�^�j�I���j�Ɋ�Â��ĕ�������]������
	direction = DirectX::SimpleMath::Vector3::Transform(direction, m_transform->GetLocalRotation());

	// Y�������[���ɂ��Đ����ʂɐ���
	direction.y = 0.0f;

	// ���K�����Ĉړ�������Ԃ�
	direction.Normalize();

	return direction;
}
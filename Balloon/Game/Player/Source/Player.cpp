// ============================================
// 
// �t�@�C����: Player.cpp
// �T�v: �v���C���[�I�u�W�F�N�g
// 
// ����� : �����x��
// 
// ============================================
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

#include "Game/States/Player/PlayerIdleState.h"
#include "Game/States/Player/PlayerRunState.h"
#include "Game/States/Player/PlayerAttackState.h"


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
	m_balloonIndex{}
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
	// �X�e�[�g���쐬
	this->CreateStates();

	// TPS�J�����𐶐�
	//std::unique_ptr<ICamera> camera = std::make_unique<TPSKeyCamera>(
	//	m_transform.get(), m_physicsBody.get(), DirectX::SimpleMath::Vector3(0.0f, 0.0f, 10.0f));
	//// �J������������
	//camera->Initialize();
	//// �J�������}�l�[�W���[�ɐݒ�
	//m_commonResources->GetCameraManager()->Attach(std::move(camera));

	// �����蔻��}�l�[�W���[�o�^
	std::vector<ICollider*> colliders;
	colliders.push_back(m_boxCollider.get());
	colliders.push_back(m_sphereCollider.get());
	m_commonResources->GetCollisionManager()->Attach(this, colliders, m_physicsBody.get());

	m_balloonAirAmount = 0.0f;
	m_isFlating = false;
	m_isMoveing = false;
	m_isStage = false;
	m_moveingTime = 0.0f;
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
	// �L�[�{�[�h�X�e�[�g
	InputManager* input = m_commonResources->GetInputManager();
	float deltaTime = (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_currentState->Update(deltaTime);

	// �㏸�̏��������s
	if (input->OnKey(InputManager::Keys::Space))
	{
   		m_isFlating = true;
	}
	// �㏸�̏���������
	if (input->OnKeyUp(InputManager::Keys::Space))
	{
		m_isFlating = false;
	}

	// �Ə�
	if (input->OnKey(InputManager::Keys::X))
	{
		// �Ə��J�������N��
	}

	if (input->OnKeyUp(InputManager::Keys::X))
	{
		// �Ə�����
	}

	// �X�L���̔���
	if (input->OnKeyDown(InputManager::Keys::Z) && input->OnKey(InputManager::Keys::X))
	{
		// �X�L������

		// �����㐔�b��ɉ���
	}

	if (m_isFlating)
	{
		// ���D��傫������
		m_balloonAirAmount += deltaTime;

		// ���D�̑傫���𐧌�
		if (m_balloonAirAmount >= 5.0f)
		{
			m_balloonAirAmount = 5.0f;
		}

		// ���D�̑傫���ɉ����ď㏸�X�s�[�h��ݒ�
		float force = m_balloonAirAmount * 0.3f;
		// �d�͂�ݒ肷��
		if(!m_isStage)
		m_physicsBody->SetGravity(force);

		// �͂�^����
		// m_physicsBody->SetFoce(m_physicsBody->GetFoce() + force);
	}
	else
	{
		// ���D������������
		m_balloonAirAmount -= deltaTime;

		// ���D�̑傫������ԏ������Ȃ�����
		if (m_balloonAirAmount <= 0.0f)
		{
			// �͂�^���Ȃ�
			m_balloonAirAmount = -0.3f;

			// �d�͂�ݒ肷��
			//m_physicsBody->SetGravity(m_balloonAirAmount);
		}

		// ���D�̑傫���ɉ����ď㏸�X�s�[�h��ݒ�
		float force = m_balloonAirAmount * 0.3f;

		// �d�͂�ݒ肷��
		if (!m_isStage)
		m_physicsBody->SetGravity(force);
	}

	// �X�e�[�W�Ȃ��ɂ��邩�ǂ����̔���
	m_isStage = this->IsOutsideBounds(m_transform->GetLocalPosition());
	// �X�e�[�W�O�ɂ���Ƃ�
	if (m_isStage)
	{
		// �v���C���[�̃X�e�[�W����
		DirectX::SimpleMath::Vector3 correction = this->GetCorrectionVector(m_transform->GetLocalPosition());
		// �X�e�[�W�O�ɂ���ꍇ�͉����߂�
		m_physicsBody->AddForce(correction);

		m_physicsBody->SetGravity(m_physicsBody->GetGravity() * 0.2f);
	}

	// ���������̍X�V����
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

/// <summary>
/// �X�e�[�g��؂�ւ���
/// </summary>
/// <param name="newState">���̃X�e�[�g</param>
void Player::ChangeState(IState* newState)
{
	// ���㏈��
	m_currentState->PostUpdate();
	// ���݂̃X�e�[�g��؂�ւ���
	m_currentState = newState;
	// ���O����
	m_currentState->PreUpdate();
}

/// <summary>
/// ���b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
void Player::OnObjectMessegeAccepted(Message::ObjectMessageID messageID)
{
	switch (messageID)
	{
		case Message::PLAYER_IDLE:
			this->ChangeState(m_idleState.get());
			break;
		case Message::PLAYER_RUN:
			this->ChangeState(m_runState.get());
			break;
		case Message::PLAYER_ATTACK:
			this->ChangeState(m_attackState.get());
			break;
		default:
			break;
	}
}

/// <summary>
/// �����蔻��̃��b�Z�[�W���󂯎��
/// </summary>
/// <param name="messageID">���b�Z�[�WID</param>
/// <param name="sender">������������̃I�u�W�F�N�g</param>
void Player::OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender)
{
	switch (messageID)
	{
	case Message::ON_COLLISION_ENTER:
		break;
	case Message::ON_COLLISION_STAY:
		break;
	case Message::ON_COLLISION_EXIT:
		break;
	case Message::ON_TRIGGER_ENTER:
		break;
	case Message::ON_TRIGGER_STAY:
		break;
	case Message::ON_TRIGGER_EXIT:
		break;
	default:
		break;
	}
	(void)sender;
}

DirectX::SimpleMath::Vector3 Player::GetCorrectionVector(const DirectX::SimpleMath::Vector3& position)
{
	DirectX::SimpleMath::Vector3 correction = DirectX::SimpleMath::Vector3::Zero;

	float correctionStrength = 2.0f; // �␳�͌W��
	DirectX::SimpleMath::Vector3 minBounds = { -5.0f , -5.0f ,-5.0f }; // �ŏ��X�e�[�W�͈�
	DirectX::SimpleMath::Vector3 maxBounds = {  5.0f ,  5.0f , 5.0f }; // �ő�X�e�[�W�͈�

	if (position.x < minBounds.x)
		correction.x = minBounds.x - position.x;
	else if (position.x > maxBounds.x)
		correction.x = maxBounds.x - position.x;

	if (position.y < minBounds.y)
		correction.y = minBounds.y - position.y;
	else if (position.y > maxBounds.y)
		correction.y = maxBounds.y - position.y;

	if (position.z < minBounds.z)
		correction.z = minBounds.z - position.z;
	else if (position.z > maxBounds.z)
		correction.z = maxBounds.z - position.z;

	return correction * correctionStrength;
}

bool Player::IsOutsideBounds(const DirectX::SimpleMath::Vector3& position)
{
	DirectX::SimpleMath::Vector3 minBounds = { -5.0f , -5.0f ,-5.0f }; // �ŏ��X�e�[�W�͈�
	DirectX::SimpleMath::Vector3 maxBounds = { 5.0f ,  5.0f , 5.0f }; // �ő�X�e�[�W�͈�

	return (
		position.x < minBounds.x || position.x > maxBounds.x ||
		position.y < minBounds.y || position.y > maxBounds.y ||
		position.z < minBounds.z || position.z > maxBounds.z
		);
}

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
			DirectX::SimpleMath::Vector3( 0.0f,0.0f,-0.0f ),
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
}

/// <summary>
/// �����������쐬
/// </summary>
void Player::CreatePhysicsBody()
{
	// �����������쐬�Ɛݒ�
	m_physicsBody = std::make_unique<PhysicsBody>(this); // ���������𐶐�
	m_physicsBody->SetIsActive(true);                    // �A�N�e�B�u�ݒ�
	m_physicsBody->SetMass(10.0f);                        // ���ʂ�ݒ�
	m_physicsBody->SetUseGravity(true);                  // �d�͐ݒ�
	m_physicsBody->SetGravity(-2.0f);
	m_physicsBody->SetIsKinematic(false);                // �L�l�}�e�B�b�N�ݒ�
}

/// <summary>
/// �X�e�[�g���쐬
/// </summary>
void Player::CreateStates()
{
	m_idleState = std::make_unique<PlayerIdleState>();
	m_runState = std::make_unique<PlayerRunState>(m_transform.get(),m_physicsBody.get());
	m_attackState = std::make_unique<PlayerAttackState>(this);

	m_currentState = m_idleState.get();
}
											   
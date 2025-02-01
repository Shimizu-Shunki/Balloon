#include "Framework/pch.h"
#include "Game/Player/Header/Player.h"
#include "Framework/CommonResources.h"

// �q�I�u�W�F�N�g
#include "Game/Player/Header/Body.h"



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
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
		DirectX::SimpleMath::Vector3::Up,DirectX::XMConvertToRadians(180.0f)
	));
	// �X�P�[����������
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One * 0.1f);

	// �g�����X�t�H�[����e�ɐݒ�
	m_transform->SetParent(nullptr);
	// �e��Transform�Ɏ������g���q���ɐݒ�
	//m_parent->GetTransform()->SetChild(m_transform.get());

	// �{�f�B���A�^�b�`
	this->Attach(std::make_unique<Body>(this), ObjectID::PLAYER);
	// ���D���A�^�b�`�@
	
}

void Player::Update()
{
	// ���͂Ɋ�Â������x�N�g�����擾
	DirectX::SimpleMath::Vector3 movementDirection = this->GetMovementDirection(DirectX::SimpleMath::Quaternion::Identity);

	movementDirection *= (float)m_commonResources->GetStepTimer()->GetElapsedSeconds();

	m_transform->SetLocalPosition(m_transform->GetLocalPosition() += movementDirection);

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
	DirectX::Keyboard::State key = m_commonResources->GetInputManager()->GetKeyboardState();

	// ����
	DirectX::SimpleMath::Vector3 direction = DirectX::SimpleMath::Vector3::Zero;

	// ��L�[
	if (key.W)
	{
		direction += DirectX::SimpleMath::Vector3::Forward;
	}
	// ���L�[
	if (key.S)
	{
		direction += DirectX::SimpleMath::Vector3::Backward;
	}
	// �E�L�[
	if (key.D)
	{
		direction += DirectX::SimpleMath::Vector3::Right;
	}
	// ���L�[
	if (key.A)
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
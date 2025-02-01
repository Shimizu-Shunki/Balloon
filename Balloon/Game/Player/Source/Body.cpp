#include "Framework/pch.h"
#include "Game/Player/Header/Body.h"
#include "Framework/CommonResources.h"

// ���i
#include "Game/Player/Header/Head.h"
#include "Game/Player/Header/LeftArm.h"
#include "Game/Player/Header/RightArm.h"
#include "Game/Player/Header/LeftFoot.h"
#include "Game/Player/Header/RightFoot.h"



Body::Body(IObject* parent)
	:
	m_parent(parent),
	m_transform{},
	m_childs{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}

Body::~Body()
{

}


void Body::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// ���f�����擾
	m_model = m_commonResources->GetResources()->GetPlayerBodyModel();

	m_transform = std::make_unique<Transform>();

	// �ʒu��������
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// ��]�p��������
	m_transform->SetLocalRotation(DirectX::SimpleMath::Quaternion::Identity);
	// �X�P�[����������
	m_transform->SetLocalScale(DirectX::SimpleMath::Vector3::One);

	// �g�����X�t�H�[����e�ɐݒ�
	m_transform->SetParent(m_parent->GetTransform());
	// �e��Transform�Ɏ������g���q���ɐݒ�
	m_parent->GetTransform()->SetChild(m_transform.get());

	// �`��Ǘ��N���X��Transform�ƃ��f����ݒ�
	m_commonResources->GetRenderManager()->AddModel({
		m_transform.get(),
		m_model
	});

	// �A�^�b�`
	// ��
	this->Attach(std::make_unique<Head>(this), ObjectID::PLAYER);
	// ���r
	this->Attach(std::make_unique<LeftArm>(this), ObjectID::PLAYER);
	// �E�r
	this->Attach(std::make_unique<RightArm>(this), ObjectID::PLAYER);
	// ����
	this->Attach(std::make_unique<LeftFoot>(this), ObjectID::PLAYER);
	// �E��
	this->Attach(std::make_unique<RightFoot>(this), ObjectID::PLAYER);
}

void Body::Update()
{

	// �q�����X�V����
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void Body::Finalize() {}


void Body::Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId)
{
	// �p�[�c�̏�����
	turretParts->Initialize(objectId, true);
	// �q���ɓo�^
	m_childs.emplace_back(std::move(turretParts));
}


void Body::Detach(std::unique_ptr<IObject> turretParts)
{

}

void Body::OnCollisionEnter(IObject* object) { (void)object; }
void Body::OnCollisionStay(IObject* object) { (void)object; }
void Body::OnCollisionExit(IObject* object) { (void)object; }
void Body::OnTriggerEnter(IObject* object) { (void)object; }
void Body::OnTriggerStay(IObject* object) { (void)object; }
void Body::OnTriggerExit(IObject* object) { (void)object; }

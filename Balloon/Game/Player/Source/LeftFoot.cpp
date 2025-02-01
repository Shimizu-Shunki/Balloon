#include "Framework/pch.h"
#include "Game/Player/Header/LeftFoot.h"
#include "Framework/CommonResources.h"



LeftFoot::LeftFoot(IObject* parent)
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

LeftFoot::~LeftFoot()
{

}


void LeftFoot::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// ���f�����擾
	m_model = m_commonResources->GetResources()->GetPlayerLeftFootModel();

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

}

void LeftFoot::Update()
{

	// �q�����X�V����
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

void LeftFoot::Finalize() {}


void LeftFoot::Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId)
{
	// �p�[�c�̏�����
	turretParts->Initialize(objectId, true);
	// �q���ɓo�^
	m_childs.emplace_back(std::move(turretParts));
}


void LeftFoot::Detach(std::unique_ptr<IObject> turretParts)
{

}

void LeftFoot::OnCollisionEnter(IObject* object) { (void)object; }
void LeftFoot::OnCollisionStay(IObject* object) { (void)object; }
void LeftFoot::OnCollisionExit(IObject* object) { (void)object; }
void LeftFoot::OnTriggerEnter(IObject* object) { (void)object; }
void LeftFoot::OnTriggerStay(IObject* object) { (void)object; }
void LeftFoot::OnTriggerExit(IObject* object) { (void)object; }

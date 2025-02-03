#include "Framework/pch.h"
#include "Game/Balloon/Balloon.h"
#include "Framework/CommonResources.h"


Balloon::Balloon(IObject* parent, float angle)
	:
	m_parent(parent),
	m_angle(angle),
	m_transform{},
	m_objectId{},
	m_isActive{},
	m_model{}
{
	// �C���X�^���X���擾����
	m_commonResources = CommonResources::GetInstance();
}

Balloon::~Balloon()
{

}


void Balloon::Initialize(ObjectID objectID, const bool& active)
{
	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;
	// ���f�����擾
	m_model = m_commonResources->GetResources()->GetBalloonModel();

	m_transform = std::make_unique<Transform>();

	// �ʒu��������
	m_transform->SetLocalPosition({ 0.0f,0.0f,0.0f });
	// ��]�p��������
	m_transform->SetLocalRotation(
		DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
			DirectX::SimpleMath::Vector3::Forward,DirectX::XMConvertToRadians(m_angle)
		)
	);
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

void Balloon::Update()
{


}

void Balloon::Finalize() {}

void Balloon::OnCollisionEnter(IObject* object) { (void)object; }
void Balloon::OnCollisionStay(IObject* object) { (void)object; }
void Balloon::OnCollisionExit(IObject* object) { (void)object; }
void Balloon::OnTriggerEnter(IObject* object) { (void)object; }
void Balloon::OnTriggerStay(IObject* object) { (void)object; }
void Balloon::OnTriggerExit(IObject* object) { (void)object; }

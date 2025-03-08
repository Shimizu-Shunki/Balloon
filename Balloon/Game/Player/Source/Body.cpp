#include "Framework/pch.h"
#include "Game/Player/Header/Body.h"
#include "Framework/CommonResources.h"
#include "Game/Model3D/Model3D.h"
#include "Framework/Resources/ModelResources.h"
#include "Framework/Resources/MaterialResources.h"

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
	// Transform�𐶐�
	m_transform = std::make_unique<Transform>();
}

void Body::Initialize(ObjectID objectID, const bool& active)
{
	// ���L���\�[�X
	CommonResources* commonResources = CommonResources::GetInstance();

	// �I�u�W�F�N�gID��ݒ�
	m_objectId = objectID;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ�
	m_isActive = active;

	// 3D���f������������
	m_model = std::make_unique<Model3D>();
	m_model->Initialize(commonResources->GetResources()->GetModelResources()->GetPlayerBodyModel(),
		commonResources->GetResources()->GetMaterialResources()->GetDefaultPBRLit(), this
	);

	// �`��}�l�[�W���[�ɓn��
	commonResources->GetRenderManager()->AddModel(m_model.get());

	// �v���C���[
	if (m_objectId == ObjectID::PLAYER_BODY)
	{
		// �A�^�b�`
		// ��
		this->Attach(std::make_unique<Head>(this)           , ObjectID::PLAYER_HEAD);
		// ���r
		this->Attach(std::make_unique<LeftArm>(this)    , ObjectID::PLAYER_LEFT_ARM);
		// �E�r
		this->Attach(std::make_unique<RightArm>(this)  , ObjectID::PLAYER_RIGHT_ARM);
		// ����
		this->Attach(std::make_unique<LeftFoot>(this)  , ObjectID::PLAYER_LEFT_FOOT);
		// �E��
		this->Attach(std::make_unique<RightFoot>(this), ObjectID::PLAYER_RIGHT_FOOT);
	}
	// �G
	else
	{
		// �A�^�b�`
		// ��
		this->Attach(std::make_unique<Head>(this)           , ObjectID::ENEMY_HEAD);
		// ���r
		this->Attach(std::make_unique<LeftArm>(this)    , ObjectID::ENEMY_LEFT_ARM);
		// �E�r
		this->Attach(std::make_unique<RightArm>(this)  , ObjectID::ENEMY_RIGHT_ARM);
		// ����
		this->Attach(std::make_unique<LeftFoot>(this)  , ObjectID::ENEMY_LEFT_FOOT);
		// �E��
		this->Attach(std::make_unique<RightFoot>(this), ObjectID::ENEMY_RIGHT_FOOT);
	}
	
}

/// <summary>
/// Transform��������
/// </summary>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Body::InitialTransform(
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

	// �g�����X�t�H�[����e�ɐݒ�
	m_transform->SetParent(m_parent->GetTransform());
}

/// <summary>
/// �X�V����
/// </summary>
void Body::Update()
{
	// �q�����X�V����
	for (const auto& childObject : m_childs)
	{
		childObject->Update();
	}
}

/// <summary>
/// �I������
/// </summary>
void Body::Finalize() {}

/// <summary>
/// �A�^�b�`
/// </summary>
/// <param name="object">�I�u�W�F�N�g</param>
/// <param name="objectId">�I�u�W�F�N�gID</param>
/// <param name="position">�������W</param>
/// <param name="rotation">������]</param>
/// <param name="scale">�����X�P�[��</param>
void Body::Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// �p�[�c�̏�����
	object->Initialize(objectId, true);
	// Transform�̏�����
	object->InitialTransform(position, rotation, scale);

	// �q���ɓo�^
	m_childs.emplace_back(std::move(object));
}

/// <summary>
/// �f�^�b�`
/// </summary>
/// <param name="turretParts">�I�u�W�F�N�g</param>
void Body::Detach(std::unique_ptr<IObject> turretParts)
{

}
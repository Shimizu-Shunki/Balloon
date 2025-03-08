#pragma once
#include "Interface/IComposite.h"
#include "Interface/IObject.h"

#include <Interface/ICamera.h>

class CommonResources;
class PhysicsBody;
class IComposite;
class ICollider;
class Jump;



class Player : public IComposite
{
public:
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ������擾����
	bool GetIsActive() const override { return m_isActive; }
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ�����ݒ肷��
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectId; }
	// Transform�̎擾
	Transform* GetTransform() const override { return m_transform.get(); }
	// �����������擾
	PhysicsBody* GetPhysicsBody() const { return m_physicsBody.get(); }

public:
	// �R���X�g���N�^
	Player(IObject* parent);
	// �f�X�g���N�^
	~Player() override = default;

public:
	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transform��������
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// �X�V����
	void Update() override;
	// �I������
	void Finalize() override;

	// �Փ˂���������
	void OnCollisionEnter(IObject* object) override;
	// �Փ˂��Ă��鎞
	void OnCollisionStay(IObject* object) override;
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	void OnCollisionExit(IObject* object) override;

	// �Փ˂����������i�g���K�[�j
	void OnTriggerEnter(IObject* object) override;
	// �Փ˂��Ă��鎞�i�g���K�[�j
	void OnTriggerStay(IObject* object) override;
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	void OnTriggerExit(IObject* object) override;

	// ���i��ǉ�����
	void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) override;
	// ���i���폜����
	void Detach(std::unique_ptr<IObject> turretPart) override;

private:
	// �q�I�u�W�F�N�g�𐶐�
	void CreateChildObjects();
	// �����蔻��𐶐�
	void CreateCollider();
	// ���������𐶐�
	void CreatePhysicsBody();

	// �ړ�����
	DirectX::SimpleMath::Vector3 GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle);

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �e�̃I�u�W�F�N�g
	IObject* m_parent;
	// �q���̃I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_childs;

	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectId;
	// �I�u�W�F�N�g�A�N�e�B�u
	bool m_isActive;

	// Transform �S�ẴI�u�W�F�N�g������
	std::unique_ptr<Transform> m_transform;
	// �����I���l
	std::unique_ptr<PhysicsBody> m_physicsBody;
	// �����蔻��
	std::unique_ptr<ICollider> m_boxCollider;
	std::unique_ptr<ICollider> m_sphereCollider;

	// ���D�̐�
	int m_balloonIndex;

	// �W�����v����
	std::unique_ptr<Jump> m_jump;
};

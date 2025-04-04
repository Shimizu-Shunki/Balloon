#pragma once
#include "Interface/ILeaf.h"
#include "Interface/IObject.h"

class ICollider;
class Model3D;
class PhysicsBody;

class Cloud : public ILeaf
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
	
public:
	// �R���X�g���N�^
	// �J�����̏��A�e�̃I�u�W�F�N�g
	Cloud(IObject* parent);
	// �f�X�g���N�^
	~Cloud() override = default;

public:
	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transform�̏�����
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// �X�V����
	void Update() override;
	// �I������
	void Finalize() override;

	// �I�u�W�F�N�g���b�Z�[�W���󂯎��
	void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) override;
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender) override;

private:
	// �e�̃I�u�W�F�N�g
	IObject* m_parent;

	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectId;
	// �I�u�W�F�N�g�A�N�e�B�u
	bool m_isActive;

	// Transform �S�ẴI�u�W�F�N�g������
	std::unique_ptr<Transform> m_transform;
	// �����蔻��
	std::unique_ptr<ICollider> m_boxCollider;
	// ��������
	std::unique_ptr<PhysicsBody> m_physicsBody;

	// 3D���f��
	std::unique_ptr<Model3D> m_model;
	// ���D�̐�
	int m_balloonIndex;
};

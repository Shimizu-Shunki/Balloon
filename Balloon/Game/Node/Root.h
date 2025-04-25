#pragma once
#include "Interface/IObject.h"
#include "Game/Node/NodeBase.h"
#include "Interface/IComposite.h"

class Transform;

class Root : public NodeBase, public IComposite
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const override { return m_isActive; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

public:

	// �R���X�g���N�^
	Root(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale
	);
	// �f�X�g���N�^
	~Root();

public:

	// ����������
	void Initialize() override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

	// �I�u�W�F�N�g���A�^�b�`����
	void Attach(std::unique_ptr<IObject> node) override;
	// �I�u�W�F�N�g���폜����
	void Detach(std::unique_ptr<IObject> node) override;

	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID) override;
	// �L�[����������ꂽ��ʒm����
	void OnKeyPressed(KeyType type , const DirectX::Keyboard::Keys& key) override;

private:

	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// ���
	bool m_isActive;
	// Transform
	std::unique_ptr<Transform> m_transform;
};
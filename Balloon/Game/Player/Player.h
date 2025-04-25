#pragma once
#include "Interface/IComposite.h"
#include "Game/Object/Object.h"

class Transform;
class PlayerRenderableObject;
class PlayerIdleState;
class PlayerRunState;
class PlayerAttackState;

class Player : public Object , IComposite
{
public:
	// �I�u�W�F�N�g�̃A�N�e�B�u�ݒ�
	void SetIsActive(const bool& isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
	bool GetIsActive() const { return m_isActive; }

	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transform���擾����
	Transform* GetTransform() const override { return m_transform.get(); }

	// ���x���擾����
	DirectX::SimpleMath::Vector3& GetVelocity() override { return m_velocity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }
	// �����x���擾����
	DirectX::SimpleMath::Vector3& GetAcceralation() override { return m_acceralation; }
	// �����x��ݒ肷��
	void SetAcceralation(const DirectX::SimpleMath::Vector3& accelaration) override { m_acceralation = accelaration; }

	// �R���X�g���N�^
	Player(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale,
		Message::MessageID messageID);
	// �f�X�g���N�^
	~Player() override;

	// ����������
	void Initialize();
	// ���b�Z�[�W���擾����
	void OnMessegeAccepted(Message::MessageID messageID) override;
	// �L�[����������ꂽ��ʒm����
	void OnKeyPressed(KeyType type, const DirectX::Keyboard::Keys& key) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	// �㏈�����s��
	void Finalize() override;

	// �I�u�W�F�N�g���A�^�b�`����
	void Attach(std::unique_ptr<IObject> object) override;

	// �I�u�W�F�N�g���폜����
	void Detach(std::unique_ptr<IObject> object) override;

private:
	
	// �v���C���[�̉�]�p��ݒ肷��
	void SetRotation();


private:

	// �A�N�e�B�u���
	bool m_isActive;
	// �I�u�W�F�N�g�ԍ�
	int m_objectNumber;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectID;
	// �e�I�u�W�F�N�g
	IObject* m_parent;

	// �q�I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_childs;

	// ���b�Z�[�WID
	Message::MessageID m_messageID;
	// Transform
	std::unique_ptr<Transform> m_transform;
	// �����蔻��
	DirectX::BoundingSphere m_boundingSphere;

	// �X�e�[�g
	// �A�C�h���X�e�[�g
	std::unique_ptr<PlayerIdleState> m_playerIdleState;
	// �����X�e�[�g
	std::unique_ptr<PlayerRunState> m_playerRunState;
	// �A�^�b�N�X�e�[�g
	std::unique_ptr<PlayerAttackState> m_playerAttackState;

	// �v���C���[�̑��x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ����
	DirectX::SimpleMath::Vector3 m_heading;
	// ����
	DirectX::SimpleMath::Vector3 m_side;
	// �v���C���[�̉����x
	DirectX::SimpleMath::Vector3 m_acceralation;
};
// ============================================
// 
// �t�@�C����: Player.h
// �T�v: Player.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IComposite.h"
#include "Interface/IObject.h"

#include <Interface/ICamera.h>

class CommonResources;
class PhysicsBody;
class IComposite;
class ICollider;
class IState;
class Jump;



class Player : public IComposite
{
public:
	static const DirectX::SimpleMath::Vector3 MIN_LIMIT;
	static const DirectX::SimpleMath::Vector3 MAX_LIMIT;

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
	// �A�^�b�N�����ǂ����擾����
	bool GetIsAttack() { return m_isAttack; }

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

	// �I�u�W�F�N�g���b�Z�[�W���󂯎��
	void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) override;
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender) override;

	// ���i��ǉ�����
	void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) override;
	// ���i���폜����
	void Detach(std::unique_ptr<IObject> turretPart) override;
	// �X�e�[�g��؂�ւ���
	void ChangeState(IState* newState);

	DirectX::SimpleMath::Vector3 ClampPlayerPosition(DirectX::SimpleMath::Vector3 position);

private:
	// �q�I�u�W�F�N�g�𐶐�
	void CreateChildObjects();
	// �����蔻��𐶐�
	void CreateCollider();
	// ���������𐶐�
	void CreatePhysicsBody();
	// �X�e�[�g�쐬
	void CreateStates();



	// �X�e�[�W�Ȃ��ɂ��邩�ǂ���
	bool IsOutsideBounds(const DirectX::SimpleMath::Vector3& position);
	// �͂�^����
	DirectX::SimpleMath::Vector3 GetCorrectionVector(const DirectX::SimpleMath::Vector3& position);

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

	// �X�e�[�g
	std::unique_ptr<IState> m_idleState;
	std::unique_ptr<IState> m_runState;
	std::unique_ptr<IState> m_attackState;
	// ���݂̃X�e�[�g
	IState* m_currentState;


	// �c��܂������̃t���O
	bool m_isFlating;
	// �X�e�[�W���ɂ��邩�ǂ����̃t���O
	bool m_isStage;

	// ���D�̐�
	int m_balloonIndex;
	// ���D�̖c��܂����
	float m_balloonAirAmount;
	// �n�C�X�s�[�h�ړ�
	bool m_isMoveing;
	float m_moveingTime;

	// ���݂̑傫��
	float m_currentScale;
	// �c���ł�����
	bool m_isBalloon;
	// �c��܂��鑬�x
	float m_speed;

	// �A�^�b�N�����ǂ���
	bool m_isAttack;
};

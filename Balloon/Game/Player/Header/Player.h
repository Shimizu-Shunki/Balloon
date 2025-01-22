#pragma once

#include "Interface/IComponent.h"
#include "Interface/IComposite.h"
#include "Framework/Graphics.h"
#include "Framework/CollisionManager.h"
#include "Game/Collider/Collider.h"
#include <Interface/ICamera.h>


class InputManager;
class Collider;
class Jump;


class Player : public IComposite
{
public:
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ������擾����
	bool GetIsActive() const override { return m_isActive; }
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ�����ݒ肷��
	void SetIsActive(bool isActive) { m_isActive = isActive; }

	// ��{�I�̎擾�ݒ�
	// �Q�b�^�[
	// ���݂̈ʒu���擾����
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_currentPosition; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const override { return m_currentAngle; }
	// ���݂̑傫�����擾����
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// �Z�b�^�[
	// ���W��ݒ肷��
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_currentPosition = position; }
	// ��]��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& angle) override { m_currentAngle = angle; }
	// �傫����ݒ肷��
	void SetScale(const DirectX::SimpleMath::Vector3& scale) override { m_scale = scale; }

	// �����I���l
	// �Q�b�^�[
	// �d�͗L������
	bool GetIsGravity() const override { return m_isGravity; }
	// �L�l�}�e�B�b�N
	bool GetIsKinematic() const override { return m_isKinematic; }
	// ����
	float GetMass() const override { return m_mass; }
	// ���x
	DirectX::SimpleMath::Vector3 GetVelocity() const override { return m_velocity; }
	// �Z�b�^�[
	// �d�͗L������
	void SetIsGravity(const bool& isGravity) override { m_isGravity = isGravity; }
	// �L�l�}�e�B�b�N
	void SetIsKinematic(const bool& isKinematic) override { m_isKinematic = isKinematic; }
	// ����
	void SetMass(const float& mass) override { m_mass = mass; }
	// ���x
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }

	// �I�u�W�F�N�gID���擾����
	IComponent::ObjectID GetObjectID() const override { return m_objectId; }

	// ���f�����擾����
	DirectX::Model* GetModel() const override { return m_model.get(); }
public:
	// �R���X�g���N�^
	Player(ICamera* camera, IComponent* parent,const int balloonIndex, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// �f�X�g���N�^
	~Player();

public:
	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
	// �X�V����
	void Update(const float elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;

	// �Փ˂���������
	void OnCollisionEnter(IComponent* object);
	// �Փ˂��Ă��鎞
	void OnCollisionStay(IComponent* object);
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	void OnCollisionExit(IComponent* object);

	// �Փ˂����������i�g���K�[�j
	void OnTriggerEnter(IComponent* object);
	// �Փ˂��Ă��鎞�i�g���K�[�j
	//void OnTriggerStay(IComponent* object);
	//// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	//void OnTriggerExit(IComponent* object);

	// �C�����i��ǉ�����
	void Attach(std::unique_ptr<IComponent> turretParts) override;
	// �C�����i���폜����
	void Detach(std::unique_ptr<IComponent> turretPart) override;

	// �����蔻����擾����
	const std::vector<std::unique_ptr<Collider>>& GetColliders() const override { return m_colliders; }

public:

	void BalloonDetach();

	

private:
	// �ړ�����
	DirectX::SimpleMath::Vector3 GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle);
	// �W�����v����
	//void Jump(const float& elapsedTime);
	// �W�����v�񐔉񕜏���
	void RecoverJump();

	// Imgui
	void DebugImguiRender();

	void RenderComponent(IComponent* component);

private:
	// �O���t�B�b�N�X
	Graphics* m_graphics;
	// �C���v�b�g�}�l�[�W���[
	InputManager* m_inputManager;
	// �����蔻��}�l�[�W���[
	ICamera* m_camera;

	// �e
	IComponent* m_parent;
	// �q�z��
	std::vector<std::unique_ptr<IComponent>> m_child;

	// �I�u�W�F�N�gID
	IComponent::ObjectID m_objectId;
	// �I�u�W�F�N�g�A�N�e�B�u
	bool m_isActive;

	// ��{�I�̎擾�ݒ�
	// �����ʒu
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// ������]�p
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// ���݂̈ʒu
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// ���݂̉�]�p
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// �C����]�p
	DirectX::SimpleMath::Quaternion m_rotationTurretAngle;
	// �C�����x
	DirectX::SimpleMath::Vector3 m_turretVelocity;
	// �傫��
	DirectX::SimpleMath::Vector3 m_scale;

	// �����I���l
	// ����
	float m_mass;
	// �L�l�}�e�B�b�N���ǂ���
	bool m_isKinematic;
	// �d�͐��l
	float m_gravity;
	// �d�͗L��������
	bool m_isGravity;
	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;


	// �����蔻��
	std::vector<std::unique_ptr<Collider>> m_colliders;

	// 3D���f��
	std::unique_ptr<DirectX::Model> m_model;


	// �W�����v����
	std::unique_ptr<Jump> m_jump;
	

	// ���D�̐�
	int m_balloonIndex;
	// �W�����v��
	int m_jumpIndex;
};

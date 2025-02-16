#pragma once

class IObject;
class CommonResources;

class PhysicsBody
{
public:
	// ��Ԃ�ݒ肷��
	void SetIsActive(bool active) { m_isActive = active; }
	// ��Ԃ��擾����
	bool GetIsActive() { return m_isActive; }

	// ���ʂ�ݒ肷��
	void SetMass(float mass) { m_mass = mass; }
	// ���ʂ��擾����
	float GetMass() { return m_mass; }

	// �d�͂��g�p���邩�ǂ�����ݒ�
	void SetUseGravity(bool gravity) { m_useGravity = gravity; }
	// ���x��ݒ肷��
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// ���x���擾����
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// �͂�ݒ肷��
	void SetFoce(const DirectX::SimpleMath::Vector3& foce) { m_force = foce; }
	// �͂��擾����
	DirectX::SimpleMath::Vector3 GetFoce() const { return m_force; }

	// �L�l�}�e�B�b�N��ݒ肷��
	void SetIsKinematic(bool kinematic) { m_isKinematic = kinematic; }
	// �L�l�}�e�B�b�N���擾����
	bool GetIsKinematic() { return m_isKinematic; }

public:
	// �R���X�g���N�^
	PhysicsBody(IObject* object);
	// �f�X�g���N�^
	~PhysicsBody() = default;

public:

	// �X�V����
	void Update();


private:
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �I�u�W�F�N�g
	IObject* m_object;

	// �L�l�}�e�B�b�N
	bool m_isKinematic;
	// �A�N�e�B�u�ݒ�
	bool m_isActive;
	// ����
	float m_mass;	
	// ���C
	float m_friction;
	// �����W��
	float m_restitution;
	// �d��
	float m_gravity;
	// �d�̓A�N�e�B�u
	bool m_useGravity;

	// ���x
	DirectX::SimpleMath::Vector3 m_velocity;
	// ��
	DirectX::SimpleMath::Vector3 m_force;
	// �����x
	DirectX::SimpleMath::Vector3 m_acceleration;

	// �Փ˂��Ă��邩�ǂ���
	bool m_isColliding;
};
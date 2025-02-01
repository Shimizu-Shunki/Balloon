#pragma once

class TweenManager;
class Tween;

class Transform
{
public:
    // �ݒ�
    // ���[�J�����W��ݒ�
    void SetLocalPosition(const DirectX::SimpleMath::Vector3& localPosition) { m_localPosition = localPosition; }
    // ���[�J�����W��ݒ�
    void SetLocalRotation(const DirectX::SimpleMath::Quaternion& localRotation) { m_localRotation = localRotation; }
    // ���[�J���X�P�[����ݒ�
    void SetLocalScale(const DirectX::SimpleMath::Vector3& localScale) { m_localScale = localScale; }
	

    // �擾
    // ���[�J�����W��ݒ�
    DirectX::SimpleMath::Vector3 GetLocalPosition() const { return m_localPosition; }
    // ���[�J����]�p��ݒ�
    DirectX::SimpleMath::Quaternion GetLocalRotation() const { return m_localRotation; }
    // ���[�J���X�P�[����ݒ�
    DirectX::SimpleMath::Vector3 GetLocalScale() const { return m_localScale; }


	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix GetWorldMatrix() const { return m_worldMatrix; }

    // ���[���h���W���擾
    DirectX::SimpleMath::Vector3 GetWorldPosition() const
    {
        // ���[���h�s��̑�4�� (41, 42, 43) �����s�ړ�����
        return DirectX::SimpleMath::Vector3(m_worldMatrix._41, m_worldMatrix._42, m_worldMatrix._43);
    }

    // ���[���h��]���擾
    DirectX::SimpleMath::Quaternion GetWorldRotation() const
    {
        using namespace DirectX::SimpleMath;

        // �X�P�[�����������ĉ�]�s������o��
        Vector3 scale = GetWorldScale();

        Matrix rotationMatrix = m_worldMatrix;
        rotationMatrix._11 /= scale.x;
        rotationMatrix._12 /= scale.x;
        rotationMatrix._13 /= scale.x;

        rotationMatrix._21 /= scale.y;
        rotationMatrix._22 /= scale.y;
        rotationMatrix._23 /= scale.y;

        rotationMatrix._31 /= scale.z;
        rotationMatrix._32 /= scale.z;
        rotationMatrix._33 /= scale.z;

        // ��]�s�񂩂�N�H�[�^�j�I�����쐬
        return Quaternion::CreateFromRotationMatrix(rotationMatrix);
    }

    // ���[���h�X�P�[�����擾
    DirectX::SimpleMath::Vector3 GetWorldScale() const
    {
        using namespace DirectX::SimpleMath;

        // �e���̃X�P�[�����v�Z
        float scaleX = Vector3(m_worldMatrix._11, m_worldMatrix._12, m_worldMatrix._13).Length();
        float scaleY = Vector3(m_worldMatrix._21, m_worldMatrix._22, m_worldMatrix._23).Length();
        float scaleZ = Vector3(m_worldMatrix._31, m_worldMatrix._32, m_worldMatrix._33).Length();

        return Vector3(scaleX, scaleY, scaleZ);
    }

    // �e��ݒ�
    void SetParent(Transform* parent) { m_parent = parent; }
    // �q����ݒ�
    void SetChild(Transform* child) { m_childs.push_back(child); }

    // �e���擾����
    Transform* GetTransform() const { return m_parent; }
    // �q�����擾����
    std::vector<Transform*> GetChilds() const { return m_childs; }

public:
    // �R���X�g���N�^
    Transform();
    // �f�X�g���N�^
    ~Transform() = default;

public:
    // �X�V����
    void Update();

    // Tween���擾����
    Tween* GetTween();

   
private:
	// �e��Transform
	Transform* m_parent;
	// �q��Transform
	std::vector<Transform*> m_childs;

	// ���[�J�����W
	DirectX::SimpleMath::Vector3 m_localPosition;
	// ���[�J����]�p
	DirectX::SimpleMath::Quaternion m_localRotation;
	// ���[�J���X�P�[��
	DirectX::SimpleMath::Vector3 m_localScale;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix m_worldMatrix;

    // TweenManager�̃C���X�^���X
    TweenManager* m_tweenManager;
};
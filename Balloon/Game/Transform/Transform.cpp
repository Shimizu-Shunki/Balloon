#include "Framework/pch.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/Tween/Tween.h"

Transform::Transform()
	:
	m_parent(nullptr)
{
	// TweenManager�̃C���X�^���X���擾����
	m_tweenManager = TweenManager::GetInstance();
}

void Transform::Initialize(
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation,
	DirectX::SimpleMath::Vector3 scale
)
{
	// ���[���h���W�n��ݒ肷��
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
	// ���[�J�����W�n��ݒ肷��
	m_localPosition = position;
	m_localRotation = rotation;
	m_localScale    = scale;
}


void Transform::Update()
{
	// ���[�J���s����v�Z����
		m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(m_localScale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_localRotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);

	if (m_parent != nullptr)
	{
		// �q�̍s��ɐe�̕ψʕ�����悹����
		m_worldMatrix *= m_parent->GetWorldMatrix() ;
	}
	
	// �q���̍s��v�Z���s��
	for (auto& child : m_childs)
	{
		child->Update();
	}
}

// �e��Transofrm��ݒ肷��
void Transform::SetParent(Transform* parent)
{
	using namespace DirectX::SimpleMath;


	if (parent == nullptr) return;

	DirectX::SimpleMath::Matrix parentMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(parent->GetLocalScale()) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(parent->GetLocalRotation()) *
		DirectX::SimpleMath::Matrix::CreateTranslation(parent->GetLocalPosition());

	DirectX::SimpleMath::Matrix childMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(m_localScale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_localRotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);

	childMatrix *= parentMatrix.Invert();

	// ���[�J�����W���v�Z
	m_localPosition = { childMatrix._41,childMatrix._42, childMatrix._43 };


	// �e���̃X�P�[�����v�Z
	float scaleX = Vector3(childMatrix._11, childMatrix._12, childMatrix._13).Length();
	float scaleY = Vector3(childMatrix._21, childMatrix._22, childMatrix._23).Length();
	float scaleZ = Vector3(childMatrix._31, childMatrix._32, childMatrix._33).Length();

	m_localScale = { scaleX, scaleY, scaleZ };

	// �X�P�[�����������ĉ�]�s������o��
	Vector3 scale = m_localScale;

	Matrix rotationMatrix = childMatrix;
	rotationMatrix._11 /= scale.x;
	rotationMatrix._12 /= scale.x;
	rotationMatrix._13 /= scale.x;

	rotationMatrix._21 /= scale.y;
	rotationMatrix._22 /= scale.y;
	rotationMatrix._23 /= scale.y;

	rotationMatrix._31 /= scale.z;
	rotationMatrix._32 /= scale.z;
	rotationMatrix._33 /= scale.z;

	// �s��̐��K���i�I���g�m�[�}�����j
	rotationMatrix = rotationMatrix.Transpose().Invert();

	// ��]�s�񂩂�N�H�[�^�j�I�����쐬
	m_localRotation =  Quaternion::CreateFromRotationMatrix(rotationMatrix);
	
	m_parent = parent;

	// �e�Ɏ������g��ݒ�
	//parent->SetChild(this);
}


// Tween���擾����
Tween* Transform::GetTween()
{
	// �i�s���ł͂Ȃ�tween���擾����
	auto tween = m_tweenManager->GetTween();
	// ���g��ݒ肷��
	tween->SetTransform(this);
	// tween���N������
	tween->Play();
	// Tween��Ԃ�
	return tween;
}
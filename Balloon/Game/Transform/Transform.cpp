#include "Framework/pch.h"
#include "Game/Transform/Transform.h"
#include "Framework/Tween/TweenManager.h"
#include "Framework/Tween/Tween.h"

Transform::Transform()
{
	// TweenManager�̃C���X�^���X���擾����
	m_tweenManager = TweenManager::GetInstance();
}


void Transform::Update()
{
	// ���[���h�s����v�Z����
	m_worldMatrix =
		DirectX::SimpleMath::Matrix::CreateScale(m_localScale) *
		DirectX::SimpleMath::Matrix::CreateFromQuaternion(m_localRotation) *
		DirectX::SimpleMath::Matrix::CreateTranslation(m_localPosition);

	// �e�̃��[���h�s���������
	if(m_parent != nullptr)
	m_worldMatrix = m_parent->GetWorldMatrix() * m_worldMatrix;

	// �q���̍s��v�Z���s��
	for (auto& child : m_childs)
	{
		child->Update();
	}
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
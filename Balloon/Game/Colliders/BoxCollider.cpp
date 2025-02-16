#include "Framework/pch.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Transform/Transform.h"

BoxCollider::BoxCollider(ICollider::ColliderType type)
{
	// �R���C�_�[�^�C�v
	m_colliderType = type;
	// ���
	m_isActive = true;
	// �g���K�[
	m_isTrigger = false;

	// Transform���쐬
	m_transform = std::make_unique<Transform>();
}

bool BoxCollider::DetectCollision(ICollider* collider)
{

	// �{�b�N�X
	DirectX::BoundingBox box;
	// ���葤
	DirectX::BoundingSphere sphere;

	// �{�b�N�X1
	DirectX::BoundingBox box1;
	// �{�b�N�X2
	DirectX::BoundingBox box2;

	// �R���C�_�[�^�C�v�ɉ����ďՓ˔���̏�����ς���
	switch (collider->GetColliderType())
	{
		case ICollider::ColliderType::BOX:
			
			box1.Center = m_transform->GetWorldPosition();
			box1.Extents = m_transform->GetWorldScale() / 2.0f;

			box2.Center = collider->GetTransform()->GetWorldPosition();
			box2.Extents = collider->GetTransform()->GetWorldScale() / 2.0f;
			// ������s��
			return box1.Intersects(box2);
			break;
		case ICollider::ColliderType::SPHERE:

			box.Center = m_transform->GetWorldPosition();
			box.Extents = m_transform->GetWorldScale() / 2.0f;

			sphere.Center = collider->GetTransform()->GetWorldPosition();
			sphere.Radius = collider->GetTransform()->GetWorldScale().x;
			// ������s��
			return box.Intersects(sphere);
			break;

		default:
			return false;
			break;
	}
}

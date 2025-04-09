// ============================================
// 
// �t�@�C����: SphereCollider.cpp
// �T�v: ���̓����蔻��
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/Colliders/SphereCollider.h"
#include "Game/Transform/Transform.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
SphereCollider::SphereCollider()
{
	// �R���C�_�[�^�C�v
	m_colliderType = ICollider::ColliderType::SPHERE;
	// ���
	m_isActive = true;
	// �g���K�[
	m_isTrigger = false;

	// Transform���쐬
	m_transform = std::make_unique<Transform>();
}

/// <summary>
/// ������s��
/// </summary>
/// <param name="collider">����</param>
/// <returns>�Փ˂��Ă��邩�ǂ���</returns>
bool SphereCollider::DetectCollision(ICollider* collider)
{

	// �X�t�B�A
	DirectX::BoundingSphere sphere;
	// ���葤
	DirectX::BoundingBox box;

	// �X�t�B�A
	DirectX::BoundingSphere sphere1;
	// �X�t�B�A
	DirectX::BoundingSphere sphere2;

	// �R���C�_�[�^�C�v�ɉ����ďՓ˔���̏�����ς���
	switch (collider->GetColliderType())
	{
		case ICollider::ColliderType::BOX :
			// ���[���h���W���Z���^�[�Ƃ���
			sphere.Center = m_transform->GetWorldPosition();
			// ���a��Transform��X�����ɐݒ�
			sphere.Radius = m_transform->GetWorldScale().x;

			
			// ���[���h�s����Z���^�[�Ƃ���
			box.Center = collider->GetTransform()->GetWorldPosition();
			// �傫����Transform��X�����Ƃ���
			box.Extents = collider->GetTransform()->GetWorldScale() / 2.0f;

			// ������s��
			return sphere.Intersects(box);
			break;
		case ICollider::ColliderType::SPHERE:

			
			// ���[���h���W���Z���^�[�Ƃ���
			sphere.Center = m_transform->GetWorldPosition();
			// ���a��Transform��X�����ɐݒ�
			sphere.Radius = m_transform->GetWorldScale().x;

			// ���[���h���W���Z���^�[�Ƃ���
			sphere2.Center = collider->GetTransform()->GetWorldPosition();
			// ���a��Transform��X�����ɐݒ�
			sphere2.Radius = collider->GetTransform()->GetWorldScale().x;

			// ������s��
			return sphere.Intersects(sphere2);

			break;

		default:
			return false;
			break;
	}
}

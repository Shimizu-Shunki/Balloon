#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/CollisionManager.h"
// �I�u�W�F�N�g
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Interface/IObject.h"

// �R���C�_�[
#include "Framework/Collider/AABB.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"

#include "Framework/Microsoft/DebugDraw.h"
#include <vector>


CollisionManager::CollisionManager()
	:
	m_objects{},
	m_collisionStates{}
{
	m_commonResources = CommonResources::GetInstance();
}

CollisionManager::~CollisionManager()
{

}

void CollisionManager::Initialize()
{
	m_objects.clear();
	m_pendingObjects.clear();
	m_collisionStates.clear();

	// �f�o�b�O�̎��̂ݍ쐬
#ifdef _DEBUG

	// �x�[�V�b�N�G�t�F�N�g���쐬
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(
		m_commonResources->GetDeviceResources()->GetD3DDevice()
	);
	// ���_�J���[��L���ɂ���
	m_basicEffect->SetVertexColorEnabled(true);
	// �e�N�X�`���𖳌��ɂ���
	m_basicEffect->SetTextureEnabled(false);
	void const* shaderByteCode;
	size_t byteCodeLength;
	// ���_�V�F�[�_�[���擾����
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// ���̓��C�A�E�g�𐶐�����
	m_commonResources->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf()
	);
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
	);
#endif
}

// �����蔻����s��
void CollisionManager::CheckCollision()
{
	for (const auto& [object1, colliders1] : m_objects) // �L�[���擾
	{
		for (const auto& [object2, colliders2] : m_objects) // �L�[���擾
		{
            // �����I�u�W�F�N�g���m�̔�����X�L�b�v
            if (object1 == object2) continue;

			// �~�ő�܂��ɔ�����s���Փ˂��Ă��Ȃ��ꍇ�̓X�L�b�v
			if (!this->CircleCollisionCheck(object1->GetTransform()->GetWorldPosition(),
				object2->GetTransform()->GetWorldPosition())) continue;

			for (const auto& col1 : colliders1)
			{
				for (const auto& col2 : colliders2)
				{
					// �Փ˔�����s��
					this->DetectCollisions(object1, object2, col1, col2);
				}
			}
        }
	}
}

/// <summary>
/// �Փ˔���
/// </summary>
/// <param name="object1">�I�u�W�F�N�g1</param>
/// <param name="object2">�I�u�W�F�N�g2</param>
/// <param name="collider1">�I�u�W�F�N�g1�̓����蔻��</param>
/// <param name="collider2">�I�u�W�F�N�g2�̓����蔻��</param>
void CollisionManager::DetectCollisions(IObject* object1, IObject* object2,ICollider* collider1,ICollider* collider2 )
{
	// �ǂ��炩�̓����蔻�肪��A�N�e�B�u�̏ꍇ�̓X�L�b�v
	if (!collider1->GetIsActive() || !collider2->GetIsActive()) return;

	// ������s��
	bool active = collider1->DetectCollision(collider2);


	// �Փ˃y�A���쐬
	CollisionPair pair{ object1, object2, collider1, collider2 };

	// �Փ˂��Ă��Ȃ���
	if (!active)
	{
		// ���łɑO�t���[���œ������Ă��Ȃ��ꍇ�̓X�L�b�v
		if (m_collisionStates[pair] == active) return;

		// �g���K�[������
		if (collider1->GetIsTrigger())
			// ���ꂽ��
			object1->OnTriggerExit(object2);
		else
			// ���ꂽ��
			object1->OnCollisionExit(object2);

		// �Փ˂��Ă��Ȃ����Ƃ�ۑ�
		m_collisionStates[pair] = false;

		PhysicsBody* body1 = m_physics[object1];
		PhysicsBody* body2 = m_physics[object2];

		if (body1 != nullptr && !body1->GetIsKinematic())
			body1->SetUseGravity(true);
		if(body2 != nullptr && !body2->GetIsKinematic())
			body2->SetUseGravity(true);
		return;
	}

	// ���݂����g���K�[���m����Ȃ��ꍇ�����߂��������s��
	if (!collider1->GetIsTrigger() == !collider2->GetIsTrigger())
	{
		PhysicsBody* body1 = m_physics[object1];
		PhysicsBody* body2 = m_physics[object2];

		// �����߂�����
		AABB::PushBack(
			object1, collider1, body1,
			object2, collider2, body2);
	}


	// �g���K�[������
	if (collider1->GetIsTrigger())
	{
		// ���������u��
		if (m_collisionStates[pair] == false)
			object1->OnTriggerEnter(object2);

		// �������Ă��鎞
		object1->OnTriggerStay(object2);
	}
	else
	{
		// ���������u��
		if (m_collisionStates[pair] == false)
			object1->OnCollisionEnter(object2);

		// �������Ă��鎞
		object1->OnCollisionStay(object2);
	}

	// �Փ˂��Ă��邱�Ƃ�ۑ�
	m_collisionStates[pair] = true;
}


// �A�^�b�`����
void CollisionManager::Attach(IObject* object, ICollider* collider)
{
	// �I�u�W�F�N�g��ۑ�����
	m_pendingObjects[object].push_back(collider);
}

void CollisionManager::PhysicsAttach(IObject* object, PhysicsBody* physics)
{
	m_pendingPhysics[object] = physics;
}

void CollisionManager::Start()
{
	// ���݂̃I�u�W�F�N�g���폜
	m_objects.clear();
	m_physics.clear();
	// �ȍ~
	m_objects = m_pendingObjects;
	m_physics = m_pendingPhysics;
	// ���Z�b�g
	m_pendingObjects.clear();
	m_pendingPhysics.clear();
	m_collisionStates.clear();
}


bool CollisionManager::CircleCollisionCheck(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2)
{
	DirectX::BoundingSphere sphere1;
	DirectX::BoundingSphere sphere2;
	// ���W��ݒ�
	sphere1.Center = pos1;
	sphere2.Center = pos2;
	// �~�̑傫����ݒ�
	sphere1.Radius = 7.0f;
	sphere2.Radius = 7.0f;

		// �f�o�b�O�`��
#ifdef _DEBUG
	
	// �r���[�s���ݒ肷��
	m_basicEffect->SetView(m_commonResources->GetCameraManager()->GetViewMatrix());
	// �v���W�F�N�V�����s���ݒ肷��
	m_basicEffect->SetProjection(m_commonResources->GetCameraManager()->GetProjectionMatrix());
	// ���[���h�s���ݒ肷��
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// �R���e�L�X�g��ݒ肷��
	m_basicEffect->Apply(m_commonResources->GetDeviceResources()->GetD3DDeviceContext());
	// ���̓��C�A�E�g��ݒ肷��
	m_commonResources->GetDeviceResources()->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

	// �O���b�h��`��
	m_primitiveBatch->Begin();
	DX::Draw(m_primitiveBatch.get(), sphere1, DirectX::Colors::Red);
	DX::Draw(m_primitiveBatch.get(), sphere2, DirectX::Colors::Red);
	m_primitiveBatch->End();
#endif


	// ������s��
	return sphere1.Intersects(sphere2);
}

void CollisionManager::Render()
{
#ifdef _DEBUG
	for (const auto& [object1, colliders1] : m_objects) // �L�[���擾
	{
		for (const auto& [object2, colliders2] : m_objects) // �L�[���擾
		{
			for (const auto& col1 : colliders1)
			{
				for (const auto& col2 : colliders2)
				{
					DirectX::BoundingBox box;
					DirectX::BoundingSphere sphere;

					if (col1->GetColliderType() == ICollider::ColliderType::BOX)
					{
						box.Center = col1->GetTransform()->GetWorldPosition();
						box.Extents = col1->GetTransform()->GetWorldScale() / 2.0f;
					}
					else
					{
						sphere.Center = col1->GetTransform()->GetWorldPosition();
						sphere.Radius = col1->GetTransform()->GetWorldScale().x;
					}

					// �r���[�s���ݒ肷��
					m_basicEffect->SetView(m_commonResources->GetCameraManager()->GetViewMatrix());
					// �v���W�F�N�V�����s���ݒ肷��
					m_basicEffect->SetProjection(m_commonResources->GetCameraManager()->GetProjectionMatrix());
					// ���[���h�s���ݒ肷��
					m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
					// �R���e�L�X�g��ݒ肷��
					m_basicEffect->Apply(m_commonResources->GetDeviceResources()->GetD3DDeviceContext());
					// ���̓��C�A�E�g��ݒ肷��
					m_commonResources->GetDeviceResources()->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

					// �O���b�h��`��
					m_primitiveBatch->Begin();
					if (col1->GetColliderType() == ICollider::ColliderType::BOX)
					{
						DX::Draw(m_primitiveBatch.get(), box, DirectX::Colors::Green);
					}
					else
					{
						DX::Draw(m_primitiveBatch.get(), sphere, DirectX::Colors::Green);
					}
					m_primitiveBatch->End();

				}
			}
		}
	}
#endif

}
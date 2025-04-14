// ============================================
// 
// �t�@�C����: CollisionManager.cpp
// �T�v: �����蔻��������A�Ǘ�����N���X
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Message/CollisionMessenger.h"
#include "Game/Message/Message.h"
#include "Framework/CollisionManager.h"
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Interface/IObject.h"
#include "Framework/Collider/AABB.h"
#include "Interface/ICollider.h"
#include "Game/Colliders/BoxCollider.h"
#include "Game/Colliders/SphereCollider.h"
#include "Framework/Microsoft/DebugDraw.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
CollisionManager::CollisionManager()
	:
	m_pendingPhysicsBodys{},
	m_physicsBodys{},
	m_pendingCollider{},
	m_Collider{},
	m_objectIndex{}
{
	m_commonResources = CommonResources::GetInstance();

	m_collisionMessenger = CollisionMessenger::GetInstance();
}



void CollisionManager::Initialize()
{
	m_pendingPhysicsBodys.clear();
	m_physicsBodys.clear();
	m_pendingCollider.clear();
	m_Collider.clear();

	m_objectIndex = 0;
	m_pendingObjectIndex = 0;

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

/// <summary>
/// �����蔻����s��
/// </summary>
void CollisionManager::CheckCollision()
{
	for (int i = 0; i < m_objectIndex; i++)
	{
		for (int j = 0; j < m_objectIndex; j++)
		{
			IObject* object1 = m_collisionMessenger->GetObject(i);
			IObject* object2 = m_collisionMessenger->GetObject(j);

			// �����I�u�W�F�N�g���m�̔�����X�L�b�v
			if (object1 == object2) continue;

			// �~�ő�܂��ɔ�����s���Փ˂��Ă��Ȃ��ꍇ�̓X�L�b�v
			if (!this->CircleCollisionCheck(object1->GetTransform()->GetWorldPosition(),
				object2->GetTransform()->GetWorldPosition())) continue;

			for (const auto& col1 : m_Collider[i])
			{
				for (const auto& col2 : m_Collider[j])
				{

					// �����R���C�_�[���m�̔�����X�L�b�v
					if (!col1->GetIsActive() || !col2->GetIsActive()) continue;
					
					// �Փ˔�����s��
					bool active = this->DetectCollisions(col1, col2);

					// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
					this->HandleCollisionEvents(active, i, j,
						object1, object2, col1, col2);
				}
			}
		}
	}
}

/// <summary>
/// �Փ˔���
/// </summary>
/// <param name="collider1">�I�u�W�F�N�g1�̓����蔻��</param>
/// <param name="collider2">�I�u�W�F�N�g2�̓����蔻��</param>
bool CollisionManager::DetectCollisions(ICollider* collider1,ICollider* collider2 )
{
	// �ǂ��炩�̓����蔻�肪��A�N�e�B�u�̏ꍇ�̓X�L�b�v
	if (!collider1->GetIsActive() || !collider2->GetIsActive())
		return false;

	// ������s��
	return collider1->DetectCollision(collider2);
}

/// <summary>
/// ���b�Z�[�W�𑗐M����
/// </summary>
/// <param name="active">����</param>
/// <param name="index1">�I�u�W�F�N�gID1</param>
/// <param name="index2">�I�u�W�F�N�gID2</param>
/// <param name="object1">�I�u�W�F�N�g1</param>
/// <param name="object2">�I�u�W�F�N�g2</param>
/// <param name="collider1">�����蔻��1</param>
/// <param name="collider2">�����蔻��2</param>
void CollisionManager::HandleCollisionEvents(bool active, int index1, int index2, IObject* object1, IObject* object2,
	ICollider* collider1, ICollider* collider2)
{

	PhysicsBody* body1 = m_physicsBodys[index1];
	PhysicsBody* body2 = m_physicsBodys[index2];

	// �Փ˃y�A���쐬
	CollisionPair pair{ index1, index2, collider1, collider2 };

	// �Փ˂��Ă��Ȃ���
	if (!active)
	{
		// ���łɑO�t���[���œ������Ă��Ȃ��ꍇ�̓X�L�b�v
		if (m_collisionStates[pair] == active) return;

		// �g���K�[������
		if (collider1->GetIsTrigger())
			// ���ꂽ��
			m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_TRIGGER_EXIT , object2);
		else
			// ���ꂽ��
			m_collisionMessenger->Dispatch(index2 , Message::CollisionMessageID::ON_COLLISION_EXIT , object2);

		// �Փ˂��Ă��Ȃ����Ƃ�ۑ�
		m_collisionStates[pair] = false;

		if (body1 != nullptr && !body1->GetIsKinematic())
			body1->SetUseGravity(true);
		if (body2 != nullptr && !body2->GetIsKinematic())
			body2->SetUseGravity(true);
		return;
	}

	// ���݂����g���K�[���m����Ȃ��ꍇ�����߂��������s��
	if (!collider1->GetIsTrigger() == !collider2->GetIsTrigger())
	{
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
			m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_TRIGGER_ENTER , object2);

		// �������Ă��鎞
		m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_TRIGGER_STAY , object2);
	}
	else
	{
		// ���������u��
		if (m_collisionStates[pair] == false)
			m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_COLLISION_ENTER , object2);

		// �������Ă��鎞
		m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_COLLISION_STAY , object2);
	}

	// �Փ˂��Ă��邱�Ƃ�ۑ�
	m_collisionStates[pair] = true;

}


/// <summary>
/// �A�^�b�`����
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="object">�I�u�W�F�N�g</param>
/// <param name="collider">�����蔻��</param>
/// <param name="physicsBody">��������</param>
void CollisionManager::Attach(IObject* object,
	std::vector<ICollider*> collider, PhysicsBody* physicsBody)
{
	// ���b�Z���W���[�ɃI�u�W�F�N�g��o�^
	m_collisionMessenger->Register(m_pendingObjectIndex, object);
	// �����蔻���o�^
	m_pendingCollider.insert({ m_pendingObjectIndex, collider });
	// ����������o�^
	m_pendingPhysicsBodys.insert({ m_pendingObjectIndex,physicsBody });
	// �I�u�W�F�N�g�ԍ��X�V
	m_pendingObjectIndex++;
}



void CollisionManager::Start()
{
	// ���݂̃I�u�W�F�N�g���폜
	m_physicsBodys.clear();
	m_Collider.clear();
	// �ȍ~
	m_physicsBodys = m_pendingPhysicsBodys;
	m_Collider = m_pendingCollider;
	m_objectIndex = m_pendingObjectIndex;
	// ���Z�b�g
	m_pendingPhysicsBodys.clear();
	m_pendingCollider.clear();
	m_collisionStates.clear();
	m_pendingObjectIndex = 0;
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


/// <summary>
/// �f�o�b�O�`��
/// </summary>
void CollisionManager::Render()
{
#ifdef _DEBUG
	for (int i = 0; i < m_objectIndex; i++)
	{
		for (const auto& col : m_Collider[i])
		{
			DirectX::BoundingBox box;
			DirectX::BoundingSphere sphere;

			if (col->GetColliderType() == ICollider::ColliderType::BOX)
			{
				box.Center = col->GetTransform()->GetWorldPosition();
				box.Extents = col->GetTransform()->GetWorldScale() / 2.0f;
			}
			else
			{
				sphere.Center = col->GetTransform()->GetWorldPosition();
				sphere.Radius = col->GetTransform()->GetWorldScale().x;
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
			if (col->GetColliderType() == ICollider::ColliderType::BOX)
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
#endif

}
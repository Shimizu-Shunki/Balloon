#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Framework/CollisionManager.h"
// オブジェクト
#include "Game/PhysicsBody/PhysicsBody.h"
#include "Interface/IObject.h"

// コライダー
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

	// デバッグの時のみ作成
#ifdef _DEBUG

	// ベーシックエフェクトを作成
	m_basicEffect = std::make_unique<DirectX::BasicEffect>(
		m_commonResources->GetDeviceResources()->GetD3DDevice()
	);
	// 頂点カラーを有効にする
	m_basicEffect->SetVertexColorEnabled(true);
	// テクスチャを無効にする
	m_basicEffect->SetTextureEnabled(false);
	void const* shaderByteCode;
	size_t byteCodeLength;
	// 頂点シェーダーを取得する
	m_basicEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	// 入力レイアウトを生成する
	m_commonResources->GetDeviceResources()->GetD3DDevice()->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		m_inputLayout.ReleaseAndGetAddressOf()
	);
	// プリミティブバッチの作成
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(
		m_commonResources->GetDeviceResources()->GetD3DDeviceContext()
	);
#endif
}

// 当たり判定を行う
void CollisionManager::CheckCollision()
{
	for (const auto& [object1, colliders1] : m_objects) // キーを取得
	{
		for (const auto& [object2, colliders2] : m_objects) // キーを取得
		{
            // 同じオブジェクト同士の判定をスキップ
            if (object1 == object2) continue;

			// 円で大まかに判定を行い衝突していない場合はスキップ
			if (!this->CircleCollisionCheck(object1->GetTransform()->GetWorldPosition(),
				object2->GetTransform()->GetWorldPosition())) continue;

			for (const auto& col1 : colliders1)
			{
				for (const auto& col2 : colliders2)
				{
					// 衝突判定を行う
					this->DetectCollisions(object1, object2, col1, col2);
				}
			}
        }
	}
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="object1">オブジェクト1</param>
/// <param name="object2">オブジェクト2</param>
/// <param name="collider1">オブジェクト1の当たり判定</param>
/// <param name="collider2">オブジェクト2の当たり判定</param>
void CollisionManager::DetectCollisions(IObject* object1, IObject* object2,ICollider* collider1,ICollider* collider2 )
{
	// どちらかの当たり判定が非アクティブの場合はスキップ
	if (!collider1->GetIsActive() || !collider2->GetIsActive()) return;

	// 判定を行う
	bool active = collider1->DetectCollision(collider2);


	// 衝突ペアを作成
	CollisionPair pair{ object1, object2, collider1, collider2 };

	// 衝突していない時
	if (!active)
	{
		// すでに前フレームで当たっていない場合はスキップ
		if (m_collisionStates[pair] == active) return;

		// トリガーか判定
		if (collider1->GetIsTrigger())
			// 離れた時
			object1->OnTriggerExit(object2);
		else
			// 離れた時
			object1->OnCollisionExit(object2);

		// 衝突していないことを保存
		m_collisionStates[pair] = false;

		PhysicsBody* body1 = m_physics[object1];
		PhysicsBody* body2 = m_physics[object2];

		if (body1 != nullptr && !body1->GetIsKinematic())
			body1->SetUseGravity(true);
		if(body2 != nullptr && !body2->GetIsKinematic())
			body2->SetUseGravity(true);
		return;
	}

	// お互いがトリガー同士じゃない場合押し戻し処理を行う
	if (!collider1->GetIsTrigger() == !collider2->GetIsTrigger())
	{
		PhysicsBody* body1 = m_physics[object1];
		PhysicsBody* body2 = m_physics[object2];

		// 押し戻し処理
		AABB::PushBack(
			object1, collider1, body1,
			object2, collider2, body2);
	}


	// トリガーか判定
	if (collider1->GetIsTrigger())
	{
		// 当たった瞬間
		if (m_collisionStates[pair] == false)
			object1->OnTriggerEnter(object2);

		// 当たっている時
		object1->OnTriggerStay(object2);
	}
	else
	{
		// 当たった瞬間
		if (m_collisionStates[pair] == false)
			object1->OnCollisionEnter(object2);

		// 当たっている時
		object1->OnCollisionStay(object2);
	}

	// 衝突していることを保存
	m_collisionStates[pair] = true;
}


// アタッチする
void CollisionManager::Attach(IObject* object, ICollider* collider)
{
	// オブジェクトを保存する
	m_pendingObjects[object].push_back(collider);
}

void CollisionManager::PhysicsAttach(IObject* object, PhysicsBody* physics)
{
	m_pendingPhysics[object] = physics;
}

void CollisionManager::Start()
{
	// 現在のオブジェクトを削除
	m_objects.clear();
	m_physics.clear();
	// 以降
	m_objects = m_pendingObjects;
	m_physics = m_pendingPhysics;
	// リセット
	m_pendingObjects.clear();
	m_pendingPhysics.clear();
	m_collisionStates.clear();
}


bool CollisionManager::CircleCollisionCheck(const DirectX::SimpleMath::Vector3& pos1, const DirectX::SimpleMath::Vector3& pos2)
{
	DirectX::BoundingSphere sphere1;
	DirectX::BoundingSphere sphere2;
	// 座標を設定
	sphere1.Center = pos1;
	sphere2.Center = pos2;
	// 円の大きさを設定
	sphere1.Radius = 7.0f;
	sphere2.Radius = 7.0f;

		// デバッグ描画
#ifdef _DEBUG
	
	// ビュー行列を設定する
	m_basicEffect->SetView(m_commonResources->GetCameraManager()->GetViewMatrix());
	// プロジェクション行列を設定する
	m_basicEffect->SetProjection(m_commonResources->GetCameraManager()->GetProjectionMatrix());
	// ワールド行列を設定する
	m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
	// コンテキストを設定する
	m_basicEffect->Apply(m_commonResources->GetDeviceResources()->GetD3DDeviceContext());
	// 入力レイアウトを設定する
	m_commonResources->GetDeviceResources()->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

	// グリッドを描画
	m_primitiveBatch->Begin();
	DX::Draw(m_primitiveBatch.get(), sphere1, DirectX::Colors::Red);
	DX::Draw(m_primitiveBatch.get(), sphere2, DirectX::Colors::Red);
	m_primitiveBatch->End();
#endif


	// 判定を行う
	return sphere1.Intersects(sphere2);
}

void CollisionManager::Render()
{
#ifdef _DEBUG
	for (const auto& [object1, colliders1] : m_objects) // キーを取得
	{
		for (const auto& [object2, colliders2] : m_objects) // キーを取得
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

					// ビュー行列を設定する
					m_basicEffect->SetView(m_commonResources->GetCameraManager()->GetViewMatrix());
					// プロジェクション行列を設定する
					m_basicEffect->SetProjection(m_commonResources->GetCameraManager()->GetProjectionMatrix());
					// ワールド行列を設定する
					m_basicEffect->SetWorld(DirectX::SimpleMath::Matrix::Identity);
					// コンテキストを設定する
					m_basicEffect->Apply(m_commonResources->GetDeviceResources()->GetD3DDeviceContext());
					// 入力レイアウトを設定する
					m_commonResources->GetDeviceResources()->GetD3DDeviceContext()->IASetInputLayout(m_inputLayout.Get());

					// グリッドを描画
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
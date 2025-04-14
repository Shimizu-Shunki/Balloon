// ============================================
// 
// ファイル名: CollisionManager.cpp
// 概要: 当たり判定を処理、管理するクラス
// 
// 製作者 : 清水駿希
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
/// コンストラクタ
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

/// <summary>
/// 当たり判定を行う
/// </summary>
void CollisionManager::CheckCollision()
{
	for (int i = 0; i < m_objectIndex; i++)
	{
		for (int j = 0; j < m_objectIndex; j++)
		{
			IObject* object1 = m_collisionMessenger->GetObject(i);
			IObject* object2 = m_collisionMessenger->GetObject(j);

			// 同じオブジェクト同士の判定をスキップ
			if (object1 == object2) continue;

			// 円で大まかに判定を行い衝突していない場合はスキップ
			if (!this->CircleCollisionCheck(object1->GetTransform()->GetWorldPosition(),
				object2->GetTransform()->GetWorldPosition())) continue;

			for (const auto& col1 : m_Collider[i])
			{
				for (const auto& col2 : m_Collider[j])
				{

					// 同じコライダー同士の判定をスキップ
					if (!col1->GetIsActive() || !col2->GetIsActive()) continue;
					
					// 衝突判定を行う
					bool active = this->DetectCollisions(col1, col2);

					// オブジェクトにメッセージを送信する
					this->HandleCollisionEvents(active, i, j,
						object1, object2, col1, col2);
				}
			}
		}
	}
}

/// <summary>
/// 衝突判定
/// </summary>
/// <param name="collider1">オブジェクト1の当たり判定</param>
/// <param name="collider2">オブジェクト2の当たり判定</param>
bool CollisionManager::DetectCollisions(ICollider* collider1,ICollider* collider2 )
{
	// どちらかの当たり判定が非アクティブの場合はスキップ
	if (!collider1->GetIsActive() || !collider2->GetIsActive())
		return false;

	// 判定を行う
	return collider1->DetectCollision(collider2);
}

/// <summary>
/// メッセージを送信する
/// </summary>
/// <param name="active">判定</param>
/// <param name="index1">オブジェクトID1</param>
/// <param name="index2">オブジェクトID2</param>
/// <param name="object1">オブジェクト1</param>
/// <param name="object2">オブジェクト2</param>
/// <param name="collider1">当たり判定1</param>
/// <param name="collider2">当たり判定2</param>
void CollisionManager::HandleCollisionEvents(bool active, int index1, int index2, IObject* object1, IObject* object2,
	ICollider* collider1, ICollider* collider2)
{

	PhysicsBody* body1 = m_physicsBodys[index1];
	PhysicsBody* body2 = m_physicsBodys[index2];

	// 衝突ペアを作成
	CollisionPair pair{ index1, index2, collider1, collider2 };

	// 衝突していない時
	if (!active)
	{
		// すでに前フレームで当たっていない場合はスキップ
		if (m_collisionStates[pair] == active) return;

		// トリガーか判定
		if (collider1->GetIsTrigger())
			// 離れた時
			m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_TRIGGER_EXIT , object2);
		else
			// 離れた時
			m_collisionMessenger->Dispatch(index2 , Message::CollisionMessageID::ON_COLLISION_EXIT , object2);

		// 衝突していないことを保存
		m_collisionStates[pair] = false;

		if (body1 != nullptr && !body1->GetIsKinematic())
			body1->SetUseGravity(true);
		if (body2 != nullptr && !body2->GetIsKinematic())
			body2->SetUseGravity(true);
		return;
	}

	// お互いがトリガー同士じゃない場合押し戻し処理を行う
	if (!collider1->GetIsTrigger() == !collider2->GetIsTrigger())
	{
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
			m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_TRIGGER_ENTER , object2);

		// 当たっている時
		m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_TRIGGER_STAY , object2);
	}
	else
	{
		// 当たった瞬間
		if (m_collisionStates[pair] == false)
			m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_COLLISION_ENTER , object2);

		// 当たっている時
		m_collisionMessenger->Dispatch(index1 , Message::CollisionMessageID::ON_COLLISION_STAY , object2);
	}

	// 衝突していることを保存
	m_collisionStates[pair] = true;

}


/// <summary>
/// アタッチする
/// </summary>
/// <param name="objectID">オブジェクトID</param>
/// <param name="object">オブジェクト</param>
/// <param name="collider">当たり判定</param>
/// <param name="physicsBody">物理挙動</param>
void CollisionManager::Attach(IObject* object,
	std::vector<ICollider*> collider, PhysicsBody* physicsBody)
{
	// メッセンジャーにオブジェクトを登録
	m_collisionMessenger->Register(m_pendingObjectIndex, object);
	// 当たり判定を登録
	m_pendingCollider.insert({ m_pendingObjectIndex, collider });
	// 物理挙動を登録
	m_pendingPhysicsBodys.insert({ m_pendingObjectIndex,physicsBody });
	// オブジェクト番号更新
	m_pendingObjectIndex++;
}



void CollisionManager::Start()
{
	// 現在のオブジェクトを削除
	m_physicsBodys.clear();
	m_Collider.clear();
	// 以降
	m_physicsBodys = m_pendingPhysicsBodys;
	m_Collider = m_pendingCollider;
	m_objectIndex = m_pendingObjectIndex;
	// リセット
	m_pendingPhysicsBodys.clear();
	m_pendingCollider.clear();
	m_collisionStates.clear();
	m_pendingObjectIndex = 0;
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


/// <summary>
/// デバッグ描画
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
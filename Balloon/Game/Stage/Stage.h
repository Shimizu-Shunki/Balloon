// ============================================
// 
// ファイル名: Stage.h
// 概要: Stage.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/ILeaf.h"
#include "Interface/IObject.h"

class ICollider;
class Model3D;
class PhysicsBody;

class Stage : public ILeaf
{
public:
	// オブジェクトがアクティブかどうかを取得する
	bool GetIsActive() const override { return m_isActive; }
	// オブジェクトがアクティブかどうかを設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }
	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	
public:
	// コンストラクタ
	// カメラの情報、親のオブジェクト
	Stage(IObject* parent);
	// デストラクタ
	~Stage() override = default;

public:
	// 初期化処理
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transformの初期化
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// 更新処理
	void Update() override;
	// 終了処理
	void Finalize() override;

	// オブジェクトメッセージを受け取る
	void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) override;
	// 当たり判定メッセージを受け取る
	void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender) override;

private:

	// 当たり判定の作成
	void CreateCollider();

private:
	// 親のオブジェクト
	IObject* m_parent;

	// オブジェクトID
	IObject::ObjectID m_objectId;
	// オブジェクトアクティブ
	bool m_isActive;

	// 当たり判定
	std::vector<std::unique_ptr<ICollider>> m_boxColliders;

	// Transform 全てのオブジェクトが持つ
	std::unique_ptr<Transform> m_transform;
	// 物理挙動
	std::unique_ptr<PhysicsBody> m_physicsBody;
};

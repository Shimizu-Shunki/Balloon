#pragma once
#include "Interface/ILeaf.h"
#include "Interface/IObject.h"

class ICollider;
class Model3D;
class PhysicsBody;

class Cloud : public ILeaf
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
	Cloud(IObject* parent);
	// デストラクタ
	~Cloud() override = default;

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
	// 親のオブジェクト
	IObject* m_parent;

	// オブジェクトID
	IObject::ObjectID m_objectId;
	// オブジェクトアクティブ
	bool m_isActive;

	// Transform 全てのオブジェクトが持つ
	std::unique_ptr<Transform> m_transform;
	// 当たり判定
	std::unique_ptr<ICollider> m_boxCollider;
	// 物理挙動
	std::unique_ptr<PhysicsBody> m_physicsBody;

	// 3Dモデル
	std::unique_ptr<Model3D> m_model;
	// 風船の数
	int m_balloonIndex;
};

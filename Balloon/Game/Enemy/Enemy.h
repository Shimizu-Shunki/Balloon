#pragma once
#include "Interface/IComposite.h"

class CommonResources;
class PhysicsBody;
class IComposite;
class ICollider;
class Jump;


class Enemy : public IComposite
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
	// 物理的数値
	// 当たり判定

public:
	// コンストラクタ
	// カメラの情報、親のオブジェクト
	Enemy(IObject* parent);
	// デストラクタ
	~Enemy();

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

	// 衝突があった時
	void OnCollisionEnter(IObject* object) override;
	// 衝突している時
	void OnCollisionStay(IObject* object) override;
	// オブジェクトと離れたとき
	void OnCollisionExit(IObject* object) override;

	// 衝突があった時（トリガー）
	void OnTriggerEnter(IObject* object) override;
	// 衝突している時（トリガー）
	void OnTriggerStay(IObject* object) override;
	// オブジェクトと離れたとき（トリガー）
	void OnTriggerExit(IObject* object) override;

	// 部品を追加する
	void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) override;
	// 部品を削除する
	void Detach(std::unique_ptr<IObject> turretPart) override;


public:

	void BalloonDetach();



private:
	// 共有リソース
	CommonResources* m_commonResources;
	// 親のオブジェクト
	IObject* m_parent;
	// 子供のオブジェクト
	std::vector<std::unique_ptr<IObject>> m_childs;

	// オブジェクトID
	IObject::ObjectID m_objectId;
	// オブジェクトアクティブ
	bool m_isActive;

	// Transform 全てのオブジェクトが持つ
	std::unique_ptr<Transform> m_transform;

	// 物理的数値
	std::unique_ptr<PhysicsBody> m_physicsBody;

	// 当たり判定
	std::unique_ptr<ICollider> m_boxCollider;
	std::unique_ptr<ICollider> m_sphereCollider;


	// 風船の数
	int m_balloonIndex;
};

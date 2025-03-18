#pragma once
#include "Interface/IObject.h"

class IObject;
class Transform;
class Image;
class IMaterial;

class StartUI : public IObject
{
public:
	// オブジェクトアクティブを取得する
	bool GetIsActive() const  override { return m_isActive; }
	// オブジェクトアクティブを設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	// オブジェクトのIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }


public:

	// コンストラクタ
	StartUI();
	// デストラクタ
	~StartUI() = default;

	// 更新処理
	void Update();

	// 初期化処理
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transformの初期化
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// 終了処理
	void Finalize() override;

	// 衝突があった時
	void OnCollisionEnter(IObject* object) override { (void)object; };
	// 衝突している時
	void OnCollisionStay(IObject* object) override { (void)object; };
	// オブジェクトと離れたとき
	void OnCollisionExit(IObject* object) override { (void)object; };

	// 衝突があった時（トリガー）
	void OnTriggerEnter(IObject* object) override { (void)object; };
	// 衝突している時（トリガー）
	void OnTriggerStay(IObject* object) override { (void)object; };
	// オブジェクトと離れたとき（トリガー）
	void OnTriggerExit(IObject* object) override { (void)object; };

private:

	// マテリアルの初期化処理
	void InitialMaterial(int width, int height);

private:

	// アクティブ設定
	bool m_isActive;
	// オブジェクトID
	IObject::ObjectID m_objectId;
	// トランスフォーム
	std::unique_ptr<Transform> m_transform;

	// Image
	std::unique_ptr<Image> m_image;
	// マテリアル
	std::unique_ptr<IMaterial> m_material;
};
#pragma once
#include "Interface/IObject.h"
#include "Game/Image/Image.h"

class IObject;
class Image;
class Transform;
class IMaterial;

class TimerUI : public IObject
{
public:
	// オブジェクトアクティブを取得する
	bool GetIsActive() const  override { return m_isActive; }
	// オブジェクトアクティブを設定する
	void SetIsActive(bool isActive) {
		m_isActive = isActive;
		m_image->SetIsActive(isActive);
	}
	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	// オブジェクトのIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }


public:

	// コンストラクタ
	TimerUI(bool isCountingUp = true, float currentTime = 0.0f);
	// デストラクタ
	~TimerUI() = default;

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


	// オブジェクトメッセージを受け取る
	void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) override;
	// 当たり判定メッセージを受け取る
	void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender) override;

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

	float m_currentTime;
	bool m_isCountingUp;
};
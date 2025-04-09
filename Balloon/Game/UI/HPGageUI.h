// ============================================
// 
// ファイル名: HPGageUI.h
// 概要: HPGageUI.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include "Game/Image/Image.h"

class IObject;
class Image;
class Transform;
class IMaterial;

class HPGageUI : public IObject
{
private:
	static const float SPEED_SLOW;
	static const float SPEED_NORMAL;
	static const float SPEED_FAST;

	static const float RECOVERY_DELAY;
	static const float HP_OFFSET_FACTOR;

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
	HPGageUI();
	// デストラクタ
	~HPGageUI() = default;

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
	// HPゲージの見た目を更新する処理
	void UpdateHpGaugeVisual();
	// HP回復処理
	void UpdateHpRecovery(float elapsedTime);

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

	// スピード
	float m_speed;
	// 現在のHP
	float m_currentHp;
	// 回復中かどうか
	bool m_isHealing;

	// 現在の時間
	float m_currentTime;

	// 画像の大きさ
	float m_height , m_width;
	// x座標
	float m_baseX;
	float m_hpOffsetFactor;
};
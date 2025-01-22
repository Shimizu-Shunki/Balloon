#pragma once

#include "Interface/IComponent.h"
#include "Interface/IComposite.h"
#include "Framework/Graphics.h"
#include "Framework/CollisionManager.h"
#include "Game/Collider/Collider.h"
#include <Interface/ICamera.h>


class InputManager;
class Collider;
class Jump;


class Player : public IComposite
{
public:
	// オブジェクトがアクティブかどうかを取得する
	bool GetIsActive() const override { return m_isActive; }
	// オブジェクトがアクティブかどうかを設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }

	// 基本的の取得設定
	// ゲッター
	// 現在の位置を取得する
	DirectX::SimpleMath::Vector3 GetPosition() const override { return m_currentPosition; }
	// 現在の回転角を取得する
	DirectX::SimpleMath::Quaternion GetAngle() const override { return m_currentAngle; }
	// 現在の大きさを取得する
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// セッター
	// 座標を設定する
	void SetPosition(const DirectX::SimpleMath::Vector3& position) override { m_currentPosition = position; }
	// 回転を設定する
	void SetAngle(const DirectX::SimpleMath::Quaternion& angle) override { m_currentAngle = angle; }
	// 大きさを設定する
	void SetScale(const DirectX::SimpleMath::Vector3& scale) override { m_scale = scale; }

	// 物理的数値
	// ゲッター
	// 重力有効無効
	bool GetIsGravity() const override { return m_isGravity; }
	// キネマティック
	bool GetIsKinematic() const override { return m_isKinematic; }
	// 質量
	float GetMass() const override { return m_mass; }
	// 速度
	DirectX::SimpleMath::Vector3 GetVelocity() const override { return m_velocity; }
	// セッター
	// 重力有効無効
	void SetIsGravity(const bool& isGravity) override { m_isGravity = isGravity; }
	// キネマティック
	void SetIsKinematic(const bool& isKinematic) override { m_isKinematic = isKinematic; }
	// 質量
	void SetMass(const float& mass) override { m_mass = mass; }
	// 速度
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) override { m_velocity = velocity; }

	// オブジェクトIDを取得する
	IComponent::ObjectID GetObjectID() const override { return m_objectId; }

	// モデルを取得する
	DirectX::Model* GetModel() const override { return m_model.get(); }
public:
	// コンストラクタ
	Player(ICamera* camera, IComponent* parent,const int balloonIndex, const DirectX::SimpleMath::Vector3& initialPosition, const float& initialAngle);
	// デストラクタ
	~Player();

public:
	// 初期化処理
	void Initialize(ObjectID objectID, const bool& active) override;
	// 更新処理
	void Update(const float elapsedTime, const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) override;
	// 描画処理
	void Render() override;
	// 終了処理
	void Finalize() override;

	// 衝突があった時
	void OnCollisionEnter(IComponent* object);
	// 衝突している時
	void OnCollisionStay(IComponent* object);
	// オブジェクトと離れたとき
	void OnCollisionExit(IComponent* object);

	// 衝突があった時（トリガー）
	void OnTriggerEnter(IComponent* object);
	// 衝突している時（トリガー）
	//void OnTriggerStay(IComponent* object);
	//// オブジェクトと離れたとき（トリガー）
	//void OnTriggerExit(IComponent* object);

	// 砲塔部品を追加する
	void Attach(std::unique_ptr<IComponent> turretParts) override;
	// 砲塔部品を削除する
	void Detach(std::unique_ptr<IComponent> turretPart) override;

	// 当たり判定を取得する
	const std::vector<std::unique_ptr<Collider>>& GetColliders() const override { return m_colliders; }

public:

	void BalloonDetach();

	

private:
	// 移動処理
	DirectX::SimpleMath::Vector3 GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle);
	// ジャンプ処理
	//void Jump(const float& elapsedTime);
	// ジャンプ回数回復処理
	void RecoverJump();

	// Imgui
	void DebugImguiRender();

	void RenderComponent(IComponent* component);

private:
	// グラフィックス
	Graphics* m_graphics;
	// インプットマネージャー
	InputManager* m_inputManager;
	// 当たり判定マネージャー
	ICamera* m_camera;

	// 親
	IComponent* m_parent;
	// 子配列
	std::vector<std::unique_ptr<IComponent>> m_child;

	// オブジェクトID
	IComponent::ObjectID m_objectId;
	// オブジェクトアクティブ
	bool m_isActive;

	// 基本的の取得設定
	// 初期位置
	DirectX::SimpleMath::Vector3 m_initialPosition;
	// 初期回転角
	DirectX::SimpleMath::Quaternion m_initialAngle;
	// 現在の位置
	DirectX::SimpleMath::Vector3 m_currentPosition;
	// 現在の回転角
	DirectX::SimpleMath::Quaternion m_currentAngle;
	// 砲塔回転角
	DirectX::SimpleMath::Quaternion m_rotationTurretAngle;
	// 砲塔速度
	DirectX::SimpleMath::Vector3 m_turretVelocity;
	// 大きさ
	DirectX::SimpleMath::Vector3 m_scale;

	// 物理的数値
	// 質量
	float m_mass;
	// キネマティックかどうか
	bool m_isKinematic;
	// 重力数値
	float m_gravity;
	// 重力有効無効化
	bool m_isGravity;
	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;


	// 当たり判定
	std::vector<std::unique_ptr<Collider>> m_colliders;

	// 3Dモデル
	std::unique_ptr<DirectX::Model> m_model;


	// ジャンプ処理
	std::unique_ptr<Jump> m_jump;
	

	// 風船の数
	int m_balloonIndex;
	// ジャンプ回数
	int m_jumpIndex;
};

#pragma once

class IObject;
class CommonResources;

class PhysicsBody
{
public:
	// 状態を設定する
	void SetIsActive(bool active) { m_isActive = active; }
	// 状態を取得する
	bool GetIsActive() { return m_isActive; }

	// 質量を設定する
	void SetMass(float mass) { m_mass = mass; }
	// 質量を取得する
	float GetMass() { return m_mass; }

	// 重力を使用するかどうかを設定
	void SetUseGravity(bool gravity) { m_useGravity = gravity; }
	// 速度を設定する
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	// 速度を取得する
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	// 力を設定する
	void SetFoce(const DirectX::SimpleMath::Vector3& foce) { m_force = foce; }
	// 力を取得する
	DirectX::SimpleMath::Vector3 GetFoce() const { return m_force; }

	// キネマティックを設定する
	void SetIsKinematic(bool kinematic) { m_isKinematic = kinematic; }
	// キネマティックを取得する
	bool GetIsKinematic() { return m_isKinematic; }

public:
	// コンストラクタ
	PhysicsBody(IObject* object);
	// デストラクタ
	~PhysicsBody() = default;

public:

	// 更新処理
	void Update();


private:
	// 共有リソース
	CommonResources* m_commonResources;

	// オブジェクト
	IObject* m_object;

	// キネマティック
	bool m_isKinematic;
	// アクティブ設定
	bool m_isActive;
	// 質量
	float m_mass;	
	// 摩擦
	float m_friction;
	// 反発係数
	float m_restitution;
	// 重力
	float m_gravity;
	// 重力アクティブ
	bool m_useGravity;

	// 速度
	DirectX::SimpleMath::Vector3 m_velocity;
	// 力
	DirectX::SimpleMath::Vector3 m_force;
	// 加速度
	DirectX::SimpleMath::Vector3 m_acceleration;

	// 衝突しているかどうか
	bool m_isColliding;
};
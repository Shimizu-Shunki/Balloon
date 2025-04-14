// ============================================
// 
// ファイル名: Player.h
// 概要: Player.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IComposite.h"
#include "Interface/IObject.h"

#include <Interface/ICamera.h>

class CommonResources;
class PhysicsBody;
class IComposite;
class ICollider;
class IState;
class Jump;



class Player : public IComposite
{
public:
	static const DirectX::SimpleMath::Vector3 MIN_LIMIT;
	static const DirectX::SimpleMath::Vector3 MAX_LIMIT;

public:
	// オブジェクトがアクティブかどうかを取得する
	bool GetIsActive() const override { return m_isActive; }
	// オブジェクトがアクティブかどうかを設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }
	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	// 物理挙動を取得
	PhysicsBody* GetPhysicsBody() const { return m_physicsBody.get(); }
	// アタック中かどうか取得する
	bool GetIsAttack() { return m_isAttack; }

public:
	// コンストラクタ
	Player(IObject* parent);
	// デストラクタ
	~Player() override = default;

public:
	// 初期化処理
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transformを初期化
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

	// 部品を追加する
	void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) override;
	// 部品を削除する
	void Detach(std::unique_ptr<IObject> turretPart) override;
	// ステートを切り替える
	void ChangeState(IState* newState);

	DirectX::SimpleMath::Vector3 ClampPlayerPosition(DirectX::SimpleMath::Vector3 position);

private:
	// 子オブジェクトを生成
	void CreateChildObjects();
	// 当たり判定を生成
	void CreateCollider();
	// 物理挙動を生成
	void CreatePhysicsBody();
	// ステート作成
	void CreateStates();



	// ステージないにいるかどうか
	bool IsOutsideBounds(const DirectX::SimpleMath::Vector3& position);
	// 力を与える
	DirectX::SimpleMath::Vector3 GetCorrectionVector(const DirectX::SimpleMath::Vector3& position);

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

	// ステート
	std::unique_ptr<IState> m_idleState;
	std::unique_ptr<IState> m_runState;
	std::unique_ptr<IState> m_attackState;
	// 現在のステート
	IState* m_currentState;


	// 膨らませ中かのフラグ
	bool m_isFlating;
	// ステージ内にいるかどうかのフラグ
	bool m_isStage;

	// 風船の数
	int m_balloonIndex;
	// 風船の膨らませる量
	float m_balloonAirAmount;
	// ハイスピード移動
	bool m_isMoveing;
	float m_moveingTime;

	// 現在の大きさ
	float m_currentScale;
	// 膨らんでいる状態
	bool m_isBalloon;
	// 膨らませる速度
	float m_speed;

	// アタック中かどうか
	bool m_isAttack;
};

#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "pch.h"
#include "StepTimer.h"
#include "Interface/ICollision.h"
#include <variant>


class IComponent : public ICollision
{
public:
	enum class ObjectID
	{
		NONE,
		OBJECT,
		CLOUD,
		PLAYER,
		ENEMY,
		CHARACTER,
		BALLOON,
	};

public:

	// オブジェクトアクティブを取得する
	virtual bool GetIsActive() const = 0;
	// オブジェクトアクティブを設定する
	virtual void SetIsActive(bool isActive) = 0;

	// 基本的の取得設定
	// ゲッター
	// 現在の位置を取得する
	virtual DirectX::SimpleMath::Vector3 GetPosition() const = 0;
	// 現在の回転角を取得する
	virtual DirectX::SimpleMath::Quaternion GetAngle() const = 0;
	// 現在の大きさを取得する
	virtual DirectX::SimpleMath::Vector3 GetScale() const = 0;
	// セッター
	// 座標を設定する
	virtual void SetPosition(const DirectX::SimpleMath::Vector3& position) = 0;
	// 回転を設定する
	virtual void SetAngle(const DirectX::SimpleMath::Quaternion& angle) = 0;
	// 大きさを設定する
	virtual void SetScale(const DirectX::SimpleMath::Vector3& scale) = 0;


	// 物理的な値を取得設定
	// ゲッター
	// 重力有効無効
	virtual bool GetIsGravity() const = 0;
	// キネマティック
	virtual bool GetIsKinematic() const = 0;
	// 質量
	virtual float GetMass() const = 0;
	// 速度
	virtual  DirectX::SimpleMath::Vector3 GetVelocity() const = 0;
	// セッター
	// 重力有効無効
	virtual void SetIsGravity(const bool& isGravity) = 0;
	// キネマティック
	virtual void SetIsKinematic(const bool& isKinematic) = 0;
	// 質量
	virtual void SetMass(const float& mass) = 0;
	// 速度
	virtual void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) = 0;


	// オブジェクトのIDを取得する
	virtual IComponent::ObjectID GetObjectID() const = 0;
	// モデルを取得する
	virtual DirectX::Model* GetModel() const = 0;

public:
	// 仮想デストラクタ
	virtual ~IComponent() = default;
	// 初期化する
	virtual void Initialize(ObjectID objectID , const bool &active) = 0;
	// 更新する
	virtual void Update(const float elapsedTime,const DirectX::SimpleMath::Vector3& position, const DirectX::SimpleMath::Quaternion& angle) = 0;
	// 描画する
	virtual void Render() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;

	

	

};

#endif		// ICOMPONENT_DEFINED
#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "Framework/pch.h"
#include "Framework/StepTimer.h"
#include "Interface/ICollision.h"
#include "Game/Transform/Transform.h"
#include <variant>


class IObject : public ICollision
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

	// Transformの取得
	virtual Transform* GetTransform() const = 0;
	
	// オブジェクトのIDを取得する
	virtual IObject::ObjectID GetObjectID() const = 0;
	// モデルを取得する
	virtual DirectX::Model* GetModel() const = 0;

public:
	// 仮想デストラクタ
	virtual ~IObject() = default;
	// 初期化する
	virtual void Initialize(ObjectID objectID , const bool &active) = 0;
	// 更新する
	virtual void Update() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};

#endif		// ICOMPONENT_DEFINED
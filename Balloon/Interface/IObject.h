#pragma once
#include "Interface/IObserver.h"
#include "Game/Transform/Transform.h"

class IObject :public IObserver
{
public:
	enum class ObjectID
	{
		NODE_BASE,

		PLAYER,
		PLAYER_BODY,
		PLAYER_HEAD,
		PLAYER_LEFT_ARM,
		PLAYER_LEFT_FOOT,
		PLAYER_RIGHT_ARM,
		PLAYER_RIGHT_FOOT,

		ENEMY,
		ENEMY_BODY,
		ENEMY_HEAD,
		ENEMY_LEFT_ARM,
		ENEMY_LEFT_FOOT,
		ENEMY_RIGHT_ARM,
		ENEMY_RIGHT_FOOT,

		BALLOON,
		BALLOON_BLUE,
		BALLOON_GREEN,
		BALLOON_PINK,
		BALLOON_RED,
		BALLOON_YELLOW,
		BALLOON_PURPLE,

		SUN,

		EFFECT_CONTROLLER,
	};

public:
	// オブジェクトのアクティブ設定
	virtual void SetIsActive(const bool& isActive) = 0;
	// オブジェクトのアクティブ状態を取得
	virtual bool GetIsActive() const = 0;

	// オブジェクト番号を取得する
	virtual int GetObjectNumber() const = 0;

	// オブジェクトIDを取得する
	virtual IObject::ObjectID GetObjectID() const = 0;
	// Transformを取得する
	virtual Transform* GetTransform() const = 0;

	// 親オブジェクトを取得する
	virtual IObject* GetParent() const = 0;

public:
	// コンストラクタ
	virtual ~IObject() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};


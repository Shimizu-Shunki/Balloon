#pragma once
#ifndef ICOMPONENT_DEFINED
#define ICOMPONENT_DEFINED
#include "Framework/pch.h"
#include "Framework/StepTimer.h"
#include "Interface/ICollision.h"
#include "Interface/IObserver.h"
#include "Game/Transform/Transform.h"
#include <variant>


class IObject : public IObserver
{
public:
	enum class ObjectID
	{
		NONE,
		OBJECT,
		CLOUD,
		PLAYER,
		PLAYER_BODY,
		PLAYER_HEAD,
		PLAYER_LEFT_ARM,
		PLAYER_RIGHT_ARM,
		PLAYER_LEFT_FOOT,
		PLAYER_RIGHT_FOOT,
		ENEMY,
		ENEMY_BODY,
		ENEMY_HEAD,
		ENEMY_LEFT_ARM,
		ENEMY_RIGHT_ARM,
		ENEMY_LEFT_FOOT,
		ENEMY_RIGHT_FOOT,
		CHARACTER,
		BALLOON,

		TitleLogoUI,
		StartUI,
		MenuButtonUI,
		KeyGuideUI,
		MenuButtonFrameUI,

		PLAYER_ICON_UI,
		PLAY_SCENE_KEYS_GUIDE_UI,
		TIME_FRAME_UI,
		SCORE_FRAME_UI,
		BALLOON_GAGE_FRAME_UI,
		BALLOON_GAGE_UI,
		HEIGHT_METER_UI,
		HP_GAGE_UI,
		HP_GAGE_FRAME_UI,
		READY_GO_UI,
		TIMER_UI,
		SCORE_UI,
		CLOUD_FRAME_UI,
		STAGE_SELECT_UI,
		STAGE_SELECT_TEXT_UI,
		STAGE_SELECT_KEY_GUIDE,
		FAILED_TEXT_UI,
		CLEAR_TEXT_UI,
		RESULT_SCENE_KEY_GUIDE_UI,

		STAGE_NUMBER,
	

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

public:
	// 仮想デストラクタ
	virtual ~IObject() = default;
	// 初期化する
	virtual void Initialize(ObjectID objectID , const bool &active) = 0;
	// Transformを初期化
	virtual void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) = 0;

	// 更新する
	virtual void Update() = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};

#endif		// ICOMPONENT_DEFINED
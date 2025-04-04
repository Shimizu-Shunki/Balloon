#pragma once

class Message
{
public:
	// オブジェクトメッセージID
	enum ObjectMessageID : int
	{
		// プレイヤー状態
		PLAYER_IDLE = 0,
		PLAYER_RUN,
		PLAYER_ATTACK,

		ADD_SCORE_TEN,
		ADD_SCORE_ONE_HUNDRED,
		ADD_SCORE_ONE_THOUSAND,
		SUBTRACT_SCORE_TEN,
		SUBTRACT_ONE_HUNDRED,
		SUBTRACT_ONE_THOUSAND,
		RESET_SCORE,

		// 敵状態
		IDLING = 10,								
		STRIKE_FORWARDING			
	};

	// シーンメッセージID
	enum SceneMessageID : int
	{
		FADE_IN = 0,
		FADE_OUT,
		MAIN,
		COUNTDOWN,
	};

	// 当たり判定メッセージID
	enum CollisionMessageID : int
	{
		ON_COLLISION_ENTER = 0,
		ON_COLLISION_STAY,
		ON_COLLISION_EXIT,
		ON_TRIGGER_ENTER,
		ON_TRIGGER_STAY,
		ON_TRIGGER_EXIT,
	};
};
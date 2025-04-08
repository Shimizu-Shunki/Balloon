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
		// スコア
		ADD_SCORE_TEN,
		ADD_SCORE_ONE_HUNDRED,
		ADD_SCORE_ONE_THOUSAND,
		SUBTRACT_SCORE_TEN,
		SUBTRACT_SCORE_ONE_HUNDRED,
		SUBTRACT_SCORE_ONE_THOUSAND,
		RESET_SCORE,
		// HP
		SUBTRACT_HP01,
		SUBTRACT_HP005,
		RECOVERY_SPEED_SLOW,
		RECOVERY_SPEED_NORMAL,
		RECOVERY_SPEED_FAST,
		// 風船の大きさ
		ON_BALLOON,
		OFF_BALLOON,
		BALLOON_SPEED_SLOW,
		BALLOON_SPEED_NORMAL,
		BALLOON_SPEED_FAST,
	};

	// シーンメッセージID
	enum SceneMessageID : int
	{
		FADE_IN = 0,
		FADE_OUT,
		MAIN,
		COUNTDOWN,

		FADE_OUT_MENU_SCENE,
		FADE_OUT_STAGE_SCENE,
		FADE_OUT_EXIT_GAME,
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
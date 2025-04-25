#pragma once

class Message
{
public:

	// メッセージID
	enum class MessageID : int
	{
		NONE = -1,

		// プレイヤー
		PLAYER_IDLING = 0,
		PLAYER_ATTCK,
		PLAYER_DOWN,
		PLAYER_SKILL,

	};


	enum class SceneMessageID : int
	{
		FADE_OUT,
		FADE_OUT_CANGE_TITLE_SCENE,
		FADE_OUT_CANGE_SELECT_SCEEN,
		FADE_OUT_CANGE_PLAY_SCENE,
		FADE_OUT_CANGE_GAME_CLEAR_SCENE,
		FADE_OUT_CANGE_GAME_OVER_SCENE,

		FADE_IN,

		COUNTDOWN,
		MAIN,
		SETTING,
	};
};
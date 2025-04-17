#pragma once

class Message
{
public:

	// メッセージID
	enum class MessageID : int
	{
		// プレイヤー
		PLAYER_IDLING = 0,
		PLAYER_ATTCK,
		PLAYER_DOWN,
		PLAYER_SKILL,

	};
};
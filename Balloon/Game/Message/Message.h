#pragma once

class Message
{
public:

	// ���b�Z�[�WID
	enum class MessageID : int
	{
		// �v���C���[
		PLAYER_IDLING = 0,
		PLAYER_ATTCK,
		PLAYER_DOWN,
		PLAYER_SKILL,

	};
};
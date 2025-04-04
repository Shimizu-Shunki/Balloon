#pragma once

class Message
{
public:
	// �I�u�W�F�N�g���b�Z�[�WID
	enum ObjectMessageID : int
	{
		// �v���C���[���
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

		// �G���
		IDLING = 10,								
		STRIKE_FORWARDING			
	};

	// �V�[�����b�Z�[�WID
	enum SceneMessageID : int
	{
		FADE_IN = 0,
		FADE_OUT,
		MAIN,
		COUNTDOWN,
	};

	// �����蔻�胁�b�Z�[�WID
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
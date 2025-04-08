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
	// �I�u�W�F�N�g�A�N�e�B�u���擾����
	virtual bool GetIsActive() const = 0;
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ肷��
	virtual void SetIsActive(bool isActive) = 0;

	// Transform�̎擾
	virtual Transform* GetTransform() const = 0;
	
	// �I�u�W�F�N�g��ID���擾����
	virtual IObject::ObjectID GetObjectID() const = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~IObject() = default;
	// ����������
	virtual void Initialize(ObjectID objectID , const bool &active) = 0;
	// Transform��������
	virtual void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) = 0;

	// �X�V����
	virtual void Update() = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};

#endif		// ICOMPONENT_DEFINED
#pragma once
#ifndef ICAMERA_DEFINED
#define IICAMERA_DEFINED
#include "Framework/pch.h"
#include "Framework/StepTimer.h"
#include "Interface/IObject.h"
#include "Game/Transform/Transform.h"
#include "Framework/CameraManager.h"

class CameraManager;

class ICamera
{
public:
	// Transform���擾����
	virtual Transform* GetTransform() const = 0;
	// �r���[�s����쐬����
	virtual DirectX::SimpleMath::Matrix GetViewMatrix() const = 0;

public:
	// ���z�f�X�g���N�^
	virtual ~ICamera() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update() = 0;
	// �r���[�s��̍쐬
	virtual DirectX::SimpleMath::Matrix CalculateViewMatrix() = 0;
};


#endif		// ICAMERA_DEFINED
#pragma once
#include "Interface/IObserver.h"
#include "Game/Transform/Transform.h"

class IObject :IObserver
{


public:
	// �R���X�g���N�^
	virtual ~IObject() = default;
	// ����������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update(const float& elapsedTime) = 0;
	// �㏈�����s��
	virtual void Finalize() = 0;
};
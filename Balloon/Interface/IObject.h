#pragma once
#include "Interface/IObserver.h"
#include "Game/Transform/Transform.h"

class IObject :IObserver
{


public:
	// コンストラクタ
	virtual ~IObject() = default;
	// 初期化する
	virtual void Initialize() = 0;
	// 更新する
	virtual void Update(const float& elapsedTime) = 0;
	// 後処理を行う
	virtual void Finalize() = 0;
};
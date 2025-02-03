#pragma once
#include "Framework/pch.h"
#include "Game/Transform/Transform.h"
#include "Game/Material/SpriteMaterial.h"

class ISprite
{
public:
	// Transformを取得する
	virtual Transform* GetTransform() const = 0;
	// マテリアルを取得する
	virtual SpriteMaterial* GetSpriteMaterial() const = 0;

public:
	virtual ~ISprite() = default;

	// 初期化
	virtual void Initialize() = 0;
	// 更新処理
	virtual void Update() = 0;

	virtual void Begin() = 0;

	virtual void End() = 0;
};
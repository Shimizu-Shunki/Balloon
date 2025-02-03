#pragma once
#include "Framework/pch.h"
#include "Game/Transform/Transform.h"
#include "Game/Material/SpriteMaterial.h"

class ISprite
{
public:
	// Transform���擾����
	virtual Transform* GetTransform() const = 0;
	// �}�e���A�����擾����
	virtual SpriteMaterial* GetSpriteMaterial() const = 0;

public:
	virtual ~ISprite() = default;

	// ������
	virtual void Initialize() = 0;
	// �X�V����
	virtual void Update() = 0;

	virtual void Begin() = 0;

	virtual void End() = 0;
};
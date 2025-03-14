#pragma once
#include "Framework/pch.h"
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

class ISprite : public IMaterial
{
public:
	virtual const UIVertexBuffer* GetVertexBuffer() const = 0;
};
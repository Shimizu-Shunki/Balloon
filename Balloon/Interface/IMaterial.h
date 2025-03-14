#pragma once
#include "Framework/pch.h"

class IMaterial
{
public:
	// ���z�f�X�g���N�^
	virtual ~IMaterial() = default;

	virtual void BeginMaterial() = 0;

	virtual void EndMaterial() = 0;

	virtual void UpdateConstBuffer() = 0;
	
};
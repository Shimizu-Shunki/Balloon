#pragma once
#include "Framework/pch.h"

class IMaterial
{
public:
	// ���z�f�X�g���N�^
	virtual ~IMaterial() = default;

	virtual void SetMaterial() = 0;
	
};
#pragma once
#include "Framework/pch.h"

class IMaterial
{
public:
	// 仮想デストラクタ
	virtual ~IMaterial() = default;

	virtual void SetMaterial() = 0;
	
};
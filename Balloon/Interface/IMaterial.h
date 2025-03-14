#pragma once
#include "Framework/pch.h"

class IMaterial
{
public:
	// 仮想デストラクタ
	virtual ~IMaterial() = default;

	virtual void BeginMaterial() = 0;

	virtual void EndMaterial() = 0;

	virtual void UpdateConstBuffer() = 0;
	
};
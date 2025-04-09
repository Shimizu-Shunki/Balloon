// ============================================
// 
// ファイル名: ISprite.h
// 概要: UIスプライトの頂点情報取得を定義する（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Framework/pch.h"
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

class ISprite : public IMaterial
{
public:
	virtual const UIVertexBuffer* GetVertexBuffer() const = 0;
};
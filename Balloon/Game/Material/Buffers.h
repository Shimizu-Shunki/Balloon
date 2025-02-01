#pragma once
#include "Framework/pch.h"

// UIの共通頂点バッファ
struct VertexBuffer
{
	DirectX::SimpleMath::Vector4 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Vector4 tangent;
	DirectX::SimpleMath::Vector4 color;
	DirectX::SimpleMath::Vector2 textureCoordinate;
};
// UIの共通定数バッファ
struct ConstBuffer
{
	DirectX::SimpleMath::Vector2 windowSize;     // ウィンドウサイズ
	DirectX::SimpleMath::Vector2 textureSize;    // テクスチャサイズ
	UINT              useTexture;                // テクスチャ使用フラグ
	UINT              useRuleTexture;            // ルール画像使用フラグ
	float             ruleProgress;              // ルール画像適用度
	UINT              ruleInverse;               // ルールの反転
};
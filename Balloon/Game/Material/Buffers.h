#pragma once
#include "Framework/pch.h"

// UIの共通頂点バッファ
struct VertexBuffer
{
    DirectX::SimpleMath::Vector4 position;          // 位置
    DirectX::SimpleMath::Vector3 rotate;            // 回転
    DirectX::SimpleMath::Vector3 scale;           // スケール
	DirectX::SimpleMath::Vector4 rect;
    DirectX::SimpleMath::Vector4 color;             // 頂点カラー
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
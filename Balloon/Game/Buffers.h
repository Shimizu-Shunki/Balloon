#pragma once
#include "pch.h"

// UIの共通頂点バッファ
struct UIVertexBuffer
{
    DirectX::SimpleMath::Vector4 position; // 位置
    DirectX::SimpleMath::Vector3 rotation; // 回転
    DirectX::SimpleMath::Vector3 scale;    // スケール
	DirectX::SimpleMath::Vector4 rect;     // 矩形情報
    DirectX::SimpleMath::Vector4 color;    // 頂点カラー
};

// UIの共通定数バッファ
struct UIConstBuffer
{
	DirectX::SimpleMath::Vector2 windowSize;  // ウィンドウサイズ
	DirectX::SimpleMath::Vector2 textureSize; // テクスチャサイズ
	float useTexture;                         // テクスチャ使用フラグ
	float useRuleTexture;                     // ルール画像使用フラグ
	float ruleProgress;                       // ルール画像適用度
	float ruleInverse;                        // ルールの反転
	DirectX::SimpleMath::Vector4 time;        // タイム
};											  

// ライトの定数バッファ用構造体
struct DirectionalLightBuffer
{
	DirectX::XMMATRIX lightViewProjection;	// ライトの投影空間へ座標変換する行列
	DirectX::XMVECTOR lightPosition;		// ライトの位置
	DirectX::XMVECTOR lightDirection;		// ライトの方向
	DirectX::XMVECTOR lightAmbient;			// ライトの環境光
};

struct PBRLitConstantBuffer
{
	DirectX::SimpleMath::Vector4 baseColor; // 基本色
	float matallic;                         // 金属度
	float smoothness;                       // 表面の滑らかさ
	float useBaseMap;                       // ベースカラーテクスチャを使用するか
	float useNormalMap;                     // 法線マップを使用するか
};

struct AmbientLightParameters
{
	DirectX::SimpleMath::Vector3 ambientLightColor;
	float ambientLightIntensity;
};

struct SkyBoxConstBuffer
{
	DirectX::SimpleMath::Matrix worldMatrix;
	DirectX::SimpleMath::Matrix viewMatrix;
	DirectX::SimpleMath::Matrix projectionMatrix;
	DirectX::SimpleMath::Vector4 dayProgress;
};
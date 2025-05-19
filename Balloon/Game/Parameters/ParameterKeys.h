#pragma once

// パラメータの種類
enum class ParametersID
{
	// エフェクト
	EFFECT,
	// ステアリングビヘイビア
	STEERING_BEHAVIOR, 
	// プレイヤー
	PLAYER,
	// 敵
	ENEMY,

	PARTICLE,

	BALLOON_EXPLOSION,

};


enum class ParameterKeysF
{
	// プレイヤー
	PlayerBrakingRate,
	PlayerMass,
	PlayerMaxForce,
	PlayerMaxSpeed,
	PlayerMaxTurnRate,
	PlayerRadius,
	PlayerScale,
	// 敵

	// 風船

	// UI

	// 風の挙動 
	WindMinStrength,
	WindMaxStrength,
	WindMinDuration,
	WindMaxDuration,
	WindIdleTime,

	// ノックバック
	KnockbackCount,
	KnockbackFoce,
	KnockbackRadius,

	// パーティクル
	EmissionRate,
	EmissionDuration,
	ParticleLifetime,
	EmitSpeedMin,
	EmitSpeedMax,
	StartSizeMin,
	StartSizeMax,
	EndSizeMin,
	EndSizeMax,
	StartRotationMin,
	StartRotationMax,
	RotationSpeedMin,
	RotationSpeedMax,
	RandomnessFactor

};

enum class ParameterKeysI
{
	// プレイヤー
	Player,
	// 敵
	Number
	// 風船

	// UI
};

enum class ParameterKeysB
{
	// パーティクル
	IsLooping,
	IsGravityEnabled,
};

enum class ParameterKeysV3
{
	// プレイヤー
	Player,
	// 敵

	// 風船

	// UI


	// パーティクル
	EmitPositionMin,
	EmitPositionMax,
	EmitDirectionMin,
	EmitDirectionMax,
	GravityAcceleration,
};

enum class ParameterKeysV4
{
	// パーティクル
	StartColor,
	EndColor,
};

enum class ParameterKeysS
{
	Texture,
	Shader,
};

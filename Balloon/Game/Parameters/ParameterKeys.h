#pragma once

// �p�����[�^�̎��
enum class ParametersID
{
	// �G�t�F�N�g
	EFFECT,
	// �X�e�A�����O�r�w�C�r�A
	STEERING_BEHAVIOR, 
	// �v���C���[
	PLAYER,
	// �G
	ENEMY,

	PARTICLE,

	BALLOON_EXPLOSION,

};


enum class ParameterKeysF
{
	// �v���C���[
	PlayerBrakingRate,
	PlayerMass,
	PlayerMaxForce,
	PlayerMaxSpeed,
	PlayerMaxTurnRate,
	PlayerRadius,
	PlayerScale,
	// �G

	// ���D

	// UI

	// ���̋��� 
	WindMinStrength,
	WindMaxStrength,
	WindMinDuration,
	WindMaxDuration,
	WindIdleTime,

	// �m�b�N�o�b�N
	KnockbackCount,
	KnockbackFoce,
	KnockbackRadius,

	// �p�[�e�B�N��
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
	// �v���C���[
	Player,
	// �G
	Number
	// ���D

	// UI
};

enum class ParameterKeysB
{
	// �p�[�e�B�N��
	IsLooping,
	IsGravityEnabled,
};

enum class ParameterKeysV3
{
	// �v���C���[
	Player,
	// �G

	// ���D

	// UI


	// �p�[�e�B�N��
	EmitPositionMin,
	EmitPositionMax,
	EmitDirectionMin,
	EmitDirectionMax,
	GravityAcceleration,
};

enum class ParameterKeysV4
{
	// �p�[�e�B�N��
	StartColor,
	EndColor,
};

enum class ParameterKeysS
{
	Texture,
	Shader,
};

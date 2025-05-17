#pragma once
#include "pch.h"


// UI�̋��ʒ��_�o�b�t�@
struct UIVertexBuffer
{
	DirectX::SimpleMath::Vector4 position; // ���S���W�i�X�N���[����ԁj
	DirectX::SimpleMath::Vector3 rotate;   // rotate.xy = scale�Arotate.z = rotation�p
	DirectX::SimpleMath::Vector2 size;     // �e�N�X�`���\���T�C�Y�i�X�N���[�����W�n�j
	DirectX::SimpleMath::Vector4 rect;     // xy: UV offset, zw: UV scale
	DirectX::SimpleMath::Vector4 color;    // RGBA�J���[
	DirectX::SimpleMath::Vector4 rule;     // x: useRule, y: ruleProgress, z: inverse, w: reserved
};


// UI�̒萔�o�b�t�@
struct UIConstBuffer
{
	DirectX::SimpleMath::Vector2 windowSize;
	float useTexture;
	float padding0;
	DirectX::SimpleMath::Vector4 time;
};

// ���C�g�̒萔�o�b�t�@�p�\����
struct DirectionalLightBuffer
{
	DirectX::XMMATRIX lightViewProjection;	// ���C�g�̓��e��Ԃ֍��W�ϊ�����s��
	DirectX::XMVECTOR lightPosition;		// ���C�g�̈ʒu
	DirectX::XMVECTOR lightDirection;		// ���C�g�̕���
	DirectX::XMVECTOR lightAmbient;			// ���C�g�̊���
};

struct PBRLitConstantBuffer
{
	DirectX::SimpleMath::Vector4 baseColor; // ��{�F
	float matallic;                         // �����x
	float smoothness;                       // �\�ʂ̊��炩��
	float useBaseMap;                       // �x�[�X�J���[�e�N�X�`�����g�p���邩
	float useNormalMap;                     // �@���}�b�v���g�p���邩
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

struct ParticleConstBuffer
{
	DirectX::SimpleMath::Matrix worldMatrix;
	DirectX::SimpleMath::Matrix viewMatrix;
	DirectX::SimpleMath::Matrix projectionMatrix;
	DirectX::SimpleMath::Matrix billboardMatrix;
	DirectX::SimpleMath::Vector4 time;
};
#pragma once
#include "pch.h"

// UI�̋��ʒ��_�o�b�t�@
struct UIVertexBuffer
{
    DirectX::SimpleMath::Vector4 position; // �ʒu
    DirectX::SimpleMath::Vector3 rotation; // ��]
    DirectX::SimpleMath::Vector3 scale;    // �X�P�[��
	DirectX::SimpleMath::Vector4 rect;     // ��`���
    DirectX::SimpleMath::Vector4 color;    // ���_�J���[
};

// UI�̋��ʒ萔�o�b�t�@
struct UIConstBuffer
{
	DirectX::SimpleMath::Vector2 windowSize;  // �E�B���h�E�T�C�Y
	DirectX::SimpleMath::Vector2 textureSize; // �e�N�X�`���T�C�Y
	float useTexture;                         // �e�N�X�`���g�p�t���O
	float useRuleTexture;                     // ���[���摜�g�p�t���O
	float ruleProgress;                       // ���[���摜�K�p�x
	float ruleInverse;                        // ���[���̔��]
	DirectX::SimpleMath::Vector4 time;        // �^�C��
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
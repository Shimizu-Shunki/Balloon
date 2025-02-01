#pragma once
#include "Framework/pch.h"

// UI�̋��ʒ��_�o�b�t�@
struct VertexBuffer
{
	DirectX::SimpleMath::Vector4 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Vector4 tangent;
	DirectX::SimpleMath::Vector4 color;
	DirectX::SimpleMath::Vector2 textureCoordinate;
};
// UI�̋��ʒ萔�o�b�t�@
struct ConstBuffer
{
	DirectX::SimpleMath::Vector2 windowSize;     // �E�B���h�E�T�C�Y
	DirectX::SimpleMath::Vector2 textureSize;    // �e�N�X�`���T�C�Y
	UINT              useTexture;                // �e�N�X�`���g�p�t���O
	UINT              useRuleTexture;            // ���[���摜�g�p�t���O
	float             ruleProgress;              // ���[���摜�K�p�x
	UINT              ruleInverse;               // ���[���̔��]
};
// ============================================
// 
// �t�@�C����: DefaultUi.h
// �T�v: DefaultUi.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Buffers.h"
#include "Interface/IMaterial.h"

class IMaterial;

class DefaultUi : public IMaterial
{
public:
	// �s�N�Z���V�F�[�_�[��ݒ�
	void SetPixelShader(ID3D11PixelShader* pixelShader) { m_pixelShader = pixelShader; }

	// �萔�o�b�t�@�̃Z�b�^�[�ƃQ�b�^�[
	// �܂Ƃ߂čX�V�i�S�Ă̒l����x�ɃZ�b�g�j
	void SetUIConstBuffer(
		const DirectX::SimpleMath::Vector2& winSize,
		const DirectX::SimpleMath::Vector2& texSize,
		float useTex, float useRuleTex, float ruleProg, float ruleInv);

	// �ʂ̒l��ύX
	void SetWindowSize(const DirectX::SimpleMath::Vector2& size) { m_constBuffer.windowSize = size; }
	void SetTextureSize(const DirectX::SimpleMath::Vector2& size) { m_constBuffer.textureSize = size; }
	void SetUseTexture(bool flag) { m_constBuffer.useTexture = flag; }
	void SetUseRuleTexture(bool flag) { m_constBuffer.useRuleTexture = flag; }
	void SetRuleProgress(float progress) { m_constBuffer.ruleProgress = progress; }
	void SetRuleInverse(float inverse) { m_constBuffer.ruleInverse = inverse; }

private:
	// �X�N���[���T�C�Y
	const float SCREEN_WIDTH = 1280.0f;
	const float SCREEN_HEIGHT = 720.0f;

public:
	// �R���X�g���N�^
	DefaultUi();
	// �f�X�g���N�^
	~DefaultUi();
	
	// �}�e���A����K������
	void BeginMaterial() override;
	// �}�e���A���̉��
	void EndMaterial() override;
	// �萔�o�b�t�@���X�V����
	void UpdateConstBuffer() override;


private:
	// UI�̒萔�o�b�t�@�I�u�W�F�N�g���쐬
	void UiCreateBuffer();

private:
	// �f�o�C�X
	ID3D11Device1* m_device;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;

	// �萔�o�b�t�@
	UIConstBuffer m_constBuffer;
	// �萔�o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constBufferObject;

	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader*    m_pixelShader;
};
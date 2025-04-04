#pragma once
#include "Game/Material/Buffers.h"
#include "Interface/IMaterial.h"

class IMaterial;
class Resources;

class BalloonMaterial : public IMaterial
{
public:
	// �x�[�X�J���[��ݒ�
	void SetBaseColor(const DirectX::SimpleMath::Vector4& color) { m_PBRLitconstantBuffer.baseColor = color; }
	// �����l��ݒ�
	void SetMatallic(float matallic) { m_PBRLitconstantBuffer.matallic = matallic; }
	// �e����ݒ�
	void SetSmoothness(float smoothness) { m_PBRLitconstantBuffer.smoothness = smoothness; }
	// �x�[�X�}�b�v���g�p���邩�ݒ�
	void SetUseBaseMap(float active) { m_PBRLitconstantBuffer.useBaseMap = active; }
	// �@���}�b�v���g�p���邩�ݒ�
	void SetUseNormalMap(float active) { m_PBRLitconstantBuffer.useNormalMap = active; }

	// �x�[�X�}�b�v��ݒ肷��
	void SetBaseMap(ID3D11ShaderResourceView* baseMap) { m_baseMap = baseMap; }
	// �m�[�}���}�b�v��ݒ肷��
	void SetNormalMap(ID3D11ShaderResourceView* normalMap) { m_normalMap = normalMap; }
	// ���}�b�v��ݒ�
	void SetSkyMap(ID3D11ShaderResourceView* skyMap) { m_skyMap = skyMap; }

public:
	// �R���X�g���N�^
	BalloonMaterial();
	// �f�X�g���N�^
	~BalloonMaterial() = default;

	void Initialize(Resources* resources);

	void BeginMaterial() override;

	void EndMaterial() override;

	void UpdateConstBuffer() override;

private:

	// �C���v�b�g���C�A�E�g
	ID3D11InputLayout* m_inputLayout;

	ID3D11DeviceContext1* m_context;

	DirectX::CommonStates* m_states;

	// �V�F�[�_�[
	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_vertexShader;
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader* m_pixelShader;

	// �萔�o�b�t�@
	PBRLitConstantBuffer m_PBRLitconstantBuffer;
	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// ���C���e�N�X�`��
	ID3D11ShaderResourceView* m_baseMap;
	// �m�[�}���}�b�v
	ID3D11ShaderResourceView* m_normalMap;
	// ���}�b�v
	ID3D11ShaderResourceView* m_skyMap;
};
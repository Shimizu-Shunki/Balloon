#pragma once


class SkyBox
{
private:
	struct MatricesConstBuffer
	{
		DirectX::SimpleMath::Matrix worldMatrix;
		DirectX::SimpleMath::Matrix viewMatrix;
		DirectX::SimpleMath::Matrix projectionMatrix;
	};

public:
	// �R���X�g���N�^
	SkyBox();
	// �f�X�g���N�^
	~SkyBox() = default;

	// ����������
	void Initialize();
	// �X�V����
	void Update(DirectX::SimpleMath::Matrix view , DirectX::SimpleMath::Matrix projection);
	// �`�揈��
	void Render();

private:

	// �X�J�C�{�b�N�X���f��
	std::unique_ptr<DirectX::GeometricPrimitive> m_skyboxModel;
	// �C���v�b�g���C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout>    m_skyInputLayout;
	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader>   m_skyVertexShader;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader>    m_skyPixelShader;

	// ���e�N�X�`���i�L���[�u�}�b�v�j
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubemap;

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;
};
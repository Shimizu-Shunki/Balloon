#pragma once

class CommonResources;

class SeaMaterial
{
public:

	//	�f�[�^�󂯓n���p�R���X�^���g�o�b�t�@(���M��)
	struct ConstBuffer
	{
		DirectX::SimpleMath::Matrix		matWorld;
		DirectX::SimpleMath::Matrix		matView;
		DirectX::SimpleMath::Matrix		matProj;
		DirectX::SimpleMath::Vector4	Diffuse;
		DirectX::SimpleMath::Vector4    TessellationFactor;
	};

	// �R���X�g���N�^
	SeaMaterial();
	// �f�X�g���N�^
	~SeaMaterial();

public:

	// ����������
	void Initialize();
	// �`�揈��
	void Render();

private:
	// �u�����h�X�e�[�g�̍쐬
	void CreateBlendState(ID3D11Device1* device);
	// �[�x�X�e���V���X�e�[�g�̍쐬
	void CreateDepthStencilState(ID3D11Device1* device);
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	void CreateRasterizerState(ID3D11Device1* device);


private:

	CommonResources* m_commonResources;

	// ���_�V�F�[�_�[
	ID3D11VertexShader* m_vertexShader;
	// �n���V�F�[�_�[
	ID3D11HullShader* m_hullShader;
	// �h���C���V�F�[�_�[
	ID3D11DomainShader* m_domainShader;
	// �s�N�Z���V�F�[�_�[
	ID3D11PixelShader* m_pixelShader;

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBuffer;

	// ���̓��C�A�E�g
	ID3D11InputLayout* m_inputLayout;


	Microsoft::WRL::ComPtr<ID3D11Buffer>	m_CBuffer;

	// ���_�o�b�t�@
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;

	// �e�N�X�`��
	ID3D11ShaderResourceView* m_texture;

	float m_time;

	float m_index;
};
#pragma once
#include "Buffers.h"

class SpriteMaterial
{
private:
	//	�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> DEFAULT_INPUT_LAYOUT;

	// �X�N���[���T�C�Y
	const float SCREEN_WIDTH = 1280.0f;
	const float SCREEN_HEIGHT = 720.0f;

public:
	// �R���X�g���N�^
	SpriteMaterial(ID3D11Device1* device , ID3D11DeviceContext1* context);
	// �f�X�g���N�^
	~SpriteMaterial();

	// ���_�V�F�[�_�[�̃��[�h
	void LoadVertexShader(const wchar_t* path , std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout = DEFAULT_INPUT_LAYOUT);
	// �W�I���g���V�F�[�_�[�̃��[�h
	void LoadGeometryShader(const wchar_t* path);
	// �s�N�Z���V�F�[�_�[�̃��[�h
	void LoadPixelShader(const wchar_t* path);
	
	// �萔�o�b�t�@�̒ǉ�

	// �e�N�X�`���̃��[�h
	void LoadTexture(ID3D11ShaderResourceView* texture, int& width, int& height);
	// ���[���摜�̃��[�h
	void LoadRuleTexture(ID3D11ShaderResourceView* texture);

	// �S�Ă��Z�b�g����`�揀��
	void Begin();
	// �I�������@���
	void End();

private:
	// �u�����h�X�e�[�g�̍쐬
	void CreateBlendState();
	// �[�x�X�e���V���X�e�[�g�̍쐬
	void CreateDepthStencilState();
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	void CreateRasterizerState();
	

private:
	// �f�o�C�X
	ID3D11Device1* m_device;
	// �R���e�L�X�g
	ID3D11DeviceContext1* m_context;

	// ���ʂ̃o�b�t�@
	// ���_�o�b�t�@
	VertexBuffer m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vBuffer;
	// �萔�o�b�t�@
	ConstBuffer m_constBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_cBuffer;

	// �e�N�X�`��
	ID3D11ShaderResourceView* m_texture;
	// ���[���e�N�X�`��
	ID3D11ShaderResourceView* m_ruleTexture;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	// ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	// �W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_geometryShader;
	// �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	// �u�����h�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11BlendState> m_blendState;
	// �[�x�X�e���V���X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	// ���X�^���C�U�[�X�e�[�g
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> m_rasterizerState;
	//	�R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates> m_states;
};
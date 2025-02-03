#include "Framework/pch.h"
#include "Game/Material/SpriteMaterial.h"
#include <Framework/Microsoft/ReadData.h>

/// <summary>
/// �C���v�b�g���C�A�E�g
/// </summary>
const std::vector<D3D11_INPUT_ELEMENT_DESC> SpriteMaterial::DEFAULT_INPUT_LAYOUT =
{
	// �Z�}���e�B�b�N�� �C���f�b�N�X �t�H�[�}�b�g                          ���̓X���b�g �I�t�Z�b�g �f�[�^���                     �C���X�^���X�X�e�b�v��
		{ "SV_Position",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,                                                   D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 position
		{ "NORMAL",    0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4),                D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 rotate
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 scale
		{ "TEXCOORD",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 rect
		{ "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 } // float4 color};
};

/// <summary>
/// �R���X�g���N�^
/// </summary>
SpriteMaterial::SpriteMaterial(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_device = device;
	m_context = context;

	m_ruleTexture = nullptr;

		// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<DirectX::CommonStates>(m_device);

	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃o�[�e�b�N�X�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(VertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	device->CreateBuffer(&desc, nullptr, &m_vBuffer);

	// �u�����h�X�e�[�g�̍쐬
	this->CreateBlendState();
	// �[�x�X�e���V���X�e�[�g�̍쐬
	this->CreateDepthStencilState();
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	this->CreateRasterizerState();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
SpriteMaterial::~SpriteMaterial()
{

}

/// <summary>
/// ���_�V�F�[�_�[�����[�h
/// </summary>
void SpriteMaterial::LoadVertexShader(const wchar_t* path , std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayout)
{
	std::vector<uint8_t> blob;
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);
	//	�C���v�b�g���C�A�E�g�̍쐬
	m_device->CreateInputLayout(&DEFAULT_INPUT_LAYOUT[0],
		static_cast<UINT>(DEFAULT_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_inputLayout.GetAddressOf());
}
/// <summary>
/// �W�I���g���V�F�[�_�[�����[�h
/// </summary>
void SpriteMaterial::LoadGeometryShader(const wchar_t* path)
{
	// �W�I���g���V�F�[�_�����[�h����
	std::vector<uint8_t> blob;
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_geometryShader.ReleaseAndGetAddressOf())
	);
}
/// <summary>
/// �s�N�Z���V�F�[�_�[�����[�h
/// </summary>
void SpriteMaterial::LoadPixelShader(const wchar_t* path)
{
	// �s�N�Z���V�F�[�_�����[�h����
	std::vector<uint8_t> blob;
	blob = DX::ReadData(path);
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_pixelShader.ReleaseAndGetAddressOf())
	);
}
/// <summary>
/// �e�N�X�`�������[�h����
/// </summary>
void SpriteMaterial::LoadTexture(ID3D11ShaderResourceView* texture, int& width, int& height)
{
	// �摜���Z�b�g
	m_texture = texture;

	// �摜�̃T�C�Y���擾����
	// �ꎞ�I�ȕϐ��̐錾
	Microsoft::WRL::ComPtr<ID3D11Resource> resource;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> texture2D;
	D3D11_TEXTURE2D_DESC desc;

	// �e�N�X�`���̏����擾����================================
	// �e�N�X�`����ID3D11Resource�Ƃ��Č���
	m_texture->GetResource(resource.GetAddressOf());
	// ID3D11Resource��ID3D11Texture2D�Ƃ��Č���
	resource.As(&texture2D);
	// �e�N�X�`�������擾����
	texture2D->GetDesc(&desc);

	// �e�N�X�`���T�C�Y���擾���Afloat�^�ɕϊ�����
	width = static_cast<int>(desc.Width);
	height = static_cast<int>(desc.Height);
}
/// <summary>
/// ���[���摜�����[�h����
/// </summary>
void SpriteMaterial::LoadRuleTexture(ID3D11ShaderResourceView* texture)
{
	// ���[���摜���擾����
	m_ruleTexture = texture;
}
/// <summary>
/// �V�F�[�_�[�̐ݒ�
/// </summary>
void SpriteMaterial::Begin()
{
	// ���_�o�b�t�@�̃f�[�^���X�V
	m_context->UpdateSubresource(m_vBuffer.Get(), 0, NULL, &m_vertexBuffer, 0, 0);
	
	// �萔�o�b�t�@��ݒ肷��
	for (const auto& buffer : m_cBuffers)
	{
		// �萔�o�b�t�@���V�F�[�_�[�ɐݒ�
		ID3D11Buffer* cb[1] = { buffer.Get() };
		m_context->VSSetConstantBuffers(0, 1, cb);
		m_context->GSSetConstantBuffers(0, 1, cb);
		m_context->PSSetConstantBuffers(0, 1, cb);
	}
	
	// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
	ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
	m_context->PSSetSamplers(0, 1, sampler);

	// �u�����h�X�e�[�g��ݒ� (�������`��p)
	m_context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);
	// �[�x�X�e���V���X�e�[�g��ݒ� (�[�x�o�b�t�@�̏������݂ƎQ��)
	//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_rasterizerState.Get());
	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_inputLayout.Get());

	// �v���~�e�B�u�g�|���W�[��ݒ� (�|�C���g���X�g)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// ���_�o�b�t�@��ݒ�
	ID3D11Buffer* buffers[] = { m_vBuffer.Get() };
	UINT stride[] = { sizeof(VertexBuffer) };
	UINT offset[] = { 0 };
	m_context->IASetVertexBuffers(0, 1, buffers, stride, offset);

	// �V�F�[�_�[�o�^
	m_context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	m_context->GSSetShader(m_geometryShader.Get(), nullptr, 0);
	m_context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	// �s�N�Z���V�F�[�_�[�Ƀe�N�X�`�����\�[�X��ݒ�
	m_context->PSSetShaderResources(0, 1, &m_texture);

	if(m_ruleTexture != nullptr)
		m_context->PSSetShaderResources(1, 1, &m_ruleTexture);
}
/// <summary>
/// �V�F�[�_�[�̉��
/// </summary>
void SpriteMaterial::End()
{
	// �V�F�[�_�[�̉��
	m_context->VSSetShader(nullptr, nullptr, 0);
	m_context->GSSetShader(nullptr, nullptr, 0);
	m_context->PSSetShader(nullptr, nullptr, 0);
}

// �u�����h�X�e�[�g�̍쐬
void SpriteMaterial::CreateBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE;  // �J�o���b�W���A���t�@�Ɋ�Â��ėL��������
	blendDesc.IndependentBlendEnable = FALSE; // �����̃����_�[�^�[�Q�b�g��Ɨ����Đݒ肷��

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;              // �u�����h��L����
	rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;        // �\�[�X�̃A���t�@
	rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // �t�A���t�@
	rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;           // ���Z�u�����h
	rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;              // �A���t�@�l�̃\�[�X
	rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;             // �A���t�@�l�̃f�X�e�B�l�[�V����
	rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;           // �A���t�@�l�̉��Z
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA�S�Ă�L��

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// �J�X�^���u�����h�X�e�[�g���쐬

	m_device->CreateBlendState(&blendDesc, &m_blendState);
}

// �[�x�X�e���V���X�e�[�g�̍쐬
void SpriteMaterial::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;                          // �[�x�e�X�g��L����
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // �[�x�o�b�t�@�̏������݂�L����
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;      // �[�x�e�X�g���� (�������ꍇ�̂ݕ`��)
	depthStencilDesc.StencilEnable = FALSE;                       // �X�e���V���e�X�g�𖳌���

	// �[�x�X�e���V���X�e�[�g���쐬
	m_device->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState);
}

// ���X�^���C�U�[�X�e�[�g�̍쐬
void SpriteMaterial::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // �h��Ԃ� (�܂��� D3D11_FILL_WIREFRAME)
	rasterDesc.CullMode = D3D11_CULL_NONE;       // �J�����O�Ȃ� (�܂��� D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // ���v���̒��_������\�ʂƂ��ĔF��
	rasterDesc.DepthClipEnable = TRUE;           // �[�x�N���b�s���O��L����
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	m_device->CreateRasterizerState(&rasterDesc, &m_rasterizerState);
}
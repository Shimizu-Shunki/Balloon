// ============================================
// 
// �t�@�C����: RenderManager.cpp
// �T�v: �S�Ẵ��f���AUI�̕`����s���N���X
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Framework/RenderManager.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Game/Transform/Transform.h"
#include "Game/ShadowMap/CascadedShadowMap.h"
#include "Framework/Resources/ShaderResources.h"
#include "Game/Model3D/Model3D.h"
#include "Game/Sky/SkyBox.h"
#include "Game/Material/Buffers.h"
#include "Game/Image/Image.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
RenderManager::RenderManager()
	:
	m_sprite{},
	m_pendingSprite{},
	m_skyBox{},
	m_models{},
	m_pendingModels{}
{
	// ���L���\�[�X
	auto commonResources = CommonResources::GetInstance();
	// �f�o�C�X
	m_device = commonResources->GetDeviceResources()->GetD3DDevice();
	// �R���e�L�X�g
	m_context = commonResources->GetDeviceResources()->GetD3DDeviceContext();
	// �R�����X�e�[�g
	m_commonStates = commonResources->GetCommonStates();
	// �J�����Ǘ��N���X
	m_cameraManager = commonResources->GetCameraManager();

	// �e�X�e�[�g�쐬
	this->CreateSpriteBlendState();
	this->CreateSpriteDepthStencilState();
	this->CreateSpriteRasterizerState();
	this->CreateSmplerState();

	// �C���v�b�g���C�A�E�g��ݒ�
	m_spriteInputLayout = commonResources->GetResources()->GetShaderResources()->GetUIinputLayout();

	m_shadowMap = std::make_unique<CascadedShadowMap>();
	m_shadowMap->Initialize();

	m_skyBox = std::make_unique<SkyBox>();
	m_skyBox->Initialize();

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
	// �V�F�[�_�[�Ƀf�[�^��n�����߂̃R���X�^���g�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(AmbientLightParameters);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	m_device->CreateBuffer(&bd, nullptr, &m_ambientLightBuffer);
	// ���C�g��
	AmbientLightParameters ambientLight;
	ambientLight.ambientLightColor = DirectX::SimpleMath::Vector3(0.8, 0.9, 1.0);
	ambientLight.ambientLightIntensity = 0.8f;
	// �萔�o�b�t�@�̃f�[�^���X�V
	m_context->UpdateSubresource(m_ambientLightBuffer.Get(), 0, NULL, &ambientLight, 0, 0);

	// �V�F�[�_�[�Ƀf�[�^��n�����߂�UI�̃o�[�e�b�N�X�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC desc = {};
	ZeroMemory(&desc, sizeof(desc));
	desc.ByteWidth = sizeof(UIVertexBuffer);
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	desc.CPUAccessFlags = 0;
	m_device->CreateBuffer(&desc, nullptr, &m_UIvertexBuffer);

	m_UIvertexShader = commonResources->GetResources()->GetShaderResources()->GetUI_VS();
	m_UIGeometryShader = commonResources->GetResources()->GetShaderResources()->GetUI_GS();
}


void RenderManager::SwitchRenderbleObjects()
{
	// ���݂̃I�u�W�F�N�g���폜����
	m_models.clear();
	// ���̃I�u�W�F�N�g���i�[����
	m_models = m_pendingModels;

	for (auto model : m_models)
	{
		model->GetMaterial()->UpdateConstBuffer();
	}

	// ���݂̃X�v���C�g���폜����
	m_sprite.clear();
	// ���̃X�v���C�g���i�[����
	m_sprite = m_pendingSprite;

	for (auto sprite : m_sprite)
	{
		sprite->GetMaterial()->UpdateConstBuffer();
	}

	m_pendingSprite.clear();
	m_pendingModels.clear();
}

void RenderManager::Render()
{
	// �v���W�F�N�V�����s����擾����
	const DirectX::SimpleMath::Matrix& projectionMatrix = m_cameraManager->GetProjectionMatrix();
	// �r���[�s����擾����
	const DirectX::SimpleMath::Matrix& viewMatrix       = m_cameraManager->GetViewMatrix();

	m_skyBox->Update(viewMatrix,projectionMatrix);
	m_skyBox->Render(m_context,m_commonStates);

	// �e�p�`��
	m_shadowMap->Begin();
	// ���f���̕`��
	for (const auto& model : m_models)
	{
		if (model->GetIsShadow() && model->GetObject()->GetIsActive())
			m_shadowMap->Draw(model->GetModel(), m_context, m_commonStates, model->GetObject()->GetTransform()->GetWorldMatrix());
	}
	m_shadowMap->End();

	// ���f���̕`��
	for (const auto& model : m_models)
	{
		if (model->GetObject()->GetIsActive())
			model->Render(m_context, m_commonStates, viewMatrix, projectionMatrix, m_ambientLightBuffer.Get());
	}

	// �X�v���C�g�̕`��
	this->SpriteRender();
}


void RenderManager::SpriteRender()
{
	// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
	ID3D11SamplerState* sampler[1] = { m_samplerState.Get() };
	m_context->PSSetSamplers(0, 1, sampler);
	// �u�����h�X�e�[�g��ݒ� (�������`��p)
	m_context->OMSetBlendState(m_spriteBlendState.Get(), nullptr, 0xFFFFFFFF);
	// �[�x�X�e���V���X�e�[�g��ݒ� (�[�x�o�b�t�@�̏������݂ƎQ��)
	//context->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	// ���X�^���C�U�[�X�e�[�g�̐ݒ�
	m_context->RSSetState(m_spriteRasterizerState.Get());
	// ���̓��C�A�E�g��ݒ�
	m_context->IASetInputLayout(m_spriteInputLayout);
	// �v���~�e�B�u�g�|���W�[��ݒ� (�|�C���g���X�g)
	m_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// �X�v���C�g�̕`��
	for (auto sprite : m_sprite)
	{
		if (sprite == nullptr || !sprite->GetIsActive()) continue;

		auto material = sprite->Render(m_context, m_UIvertexBuffer.Get());

		// ���_�V�F�[�_�[�̐ݒ�
		m_context->VSSetShader(m_UIvertexShader, nullptr, 0);
		// �W�I���g���V�F�[�_�[�̐ݒ�
		m_context->GSSetShader(m_UIGeometryShader, nullptr, 0);
		// �`��
		m_context->Draw(1, 0);
		// �}�e���A���̉��
		material->EndMaterial();
	}
}



// �u�����h�X�e�[�g�̍쐬
void RenderManager::CreateSpriteBlendState()
{
	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable  = FALSE; // �J�o���b�W���A���t�@�Ɋ�Â��ėL��������
	blendDesc.IndependentBlendEnable = FALSE; // �����̃����_�[�^�[�Q�b�g��Ɨ����Đݒ肷��

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;                                   // �u�����h��L����
	rtBlendDesc.SrcBlend              = D3D11_BLEND_SRC_ALPHA;        // �\�[�X�̃A���t�@
	rtBlendDesc.DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;    // �t�A���t�@
	rtBlendDesc.BlendOp               = D3D11_BLEND_OP_ADD;           // ���Z�u�����h
	rtBlendDesc.SrcBlendAlpha         = D3D11_BLEND_ONE;              // �A���t�@�l�̃\�[�X
	rtBlendDesc.DestBlendAlpha        = D3D11_BLEND_ZERO;             // �A���t�@�l�̃f�X�e�B�l�[�V����
	rtBlendDesc.BlendOpAlpha          = D3D11_BLEND_OP_ADD;           // �A���t�@�l�̉��Z
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA�S�Ă�L��

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// �J�X�^���u�����h�X�e�[�g���쐬
	m_device->CreateBlendState(&blendDesc, &m_spriteBlendState);
}

// �[�x�X�e���V���X�e�[�g�̍쐬
void RenderManager::CreateSpriteDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable    = TRUE;                       // �[�x�e�X�g��L����
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL; // �[�x�o�b�t�@�̏������݂�L����
	depthStencilDesc.DepthFunc      = D3D11_COMPARISON_LESS;      // �[�x�e�X�g���� (�������ꍇ�̂ݕ`��)
	depthStencilDesc.StencilEnable  = FALSE;                      // �X�e���V���e�X�g�𖳌���

	// �[�x�X�e���V���X�e�[�g���쐬
	m_device->CreateDepthStencilState(&depthStencilDesc, &m_spriteDepthStencilState);
}

// ���X�^���C�U�[�X�e�[�g�̍쐬
void RenderManager::CreateSpriteRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterDesc = {};
	rasterDesc.FillMode = D3D11_FILL_SOLID;      // �h��Ԃ� (�܂��� D3D11_FILL_WIREFRAME)
	rasterDesc.CullMode = D3D11_CULL_NONE;       // �J�����O�Ȃ� (�܂��� D3D11_CULL_FRONT / D3D11_CULL_BACK)
	rasterDesc.FrontCounterClockwise = FALSE;    // ���v���̒��_������\�ʂƂ��ĔF��
	rasterDesc.DepthClipEnable       = TRUE;     // �[�x�N���b�s���O��L����
	// ���X�^���C�U�[�X�e�[�g�̍쐬
	m_device->CreateRasterizerState(&rasterDesc, &m_spriteRasterizerState);
}

void RenderManager::CreateSmplerState()
{
	D3D11_SAMPLER_DESC samplerDesc = {};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;  // �ٕ����t�B���^�ō��i��
	samplerDesc.MaxAnisotropy = 16;                 // �ő�16�{�ٕ̈����t�B���^�����O
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;  // �J��Ԃ��iU���j
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;  // �J��Ԃ��iV���j
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;  // �J��Ԃ��iW���j
	samplerDesc.MipLODBias = 0.0f;                  // MIP�}�b�v�̃o�C�A�X�Ȃ�
	samplerDesc.MinLOD = 0;                         // �ŏ�LOD
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;         // �ő�LOD�i�t���𑜓x�j
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS; // ��r�Ȃ��i�ʏ�̃e�N�X�`���p�j

	m_device->CreateSamplerState(&samplerDesc, m_samplerState.GetAddressOf());
}
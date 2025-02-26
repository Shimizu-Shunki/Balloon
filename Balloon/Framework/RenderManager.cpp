#include "Framework/pch.h"
#include "Framework/RenderManager.h"
#include "Framework/CommonResources.h"
#include "Framework/CameraManager.h"
#include "Game/Transform/Transform.h"
#include "Game/ShadowMap/CascadedShadowMap.h"

RenderManager::RenderManager()
	:
	m_sprite{},
	m_pendingSprite{},
	m_skySphere{},
	m_renderableObjects{},
	m_pendingRenderableObjects{}
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

	// �R�����X�e�[�g�̍쐬
	m_states = std::make_unique<DirectX::CommonStates>(m_device);
	// �e�X�e�[�g�쐬
	this->CreateSpriteBlendState();
	this->CreateSpriteDepthStencilState();
	this->CreateSpriteRasterizerState();

	// �C���v�b�g���C�A�E�g��ݒ�
	m_spriteInputLayout = commonResources->GetResources()->GetUIinputLayout();

	m_shadowMap = std::make_unique<CascadedShadowMap>();
	m_shadowMap->Initialize();
}


void RenderManager::SwitchRenderbleObjects()
{
	// ���݂̃I�u�W�F�N�g���폜����
	m_renderableObjects.clear();
	// ���̃I�u�W�F�N�g���i�[����
	m_renderableObjects = m_pendingRenderableObjects;

	// ���݂̃X�v���C�g���폜����
	m_sprite.clear();
	// ���̃X�v���C�g���i�[����
	m_sprite = m_pendingSprite;

	m_pendingSprite.clear();
	m_pendingRenderableObjects.clear();
}

void RenderManager::Render()
{
	// �X�J�C�X�t�B�A��`�悷�� �X�J�C�X�t�B�A���Ȃ��ꍇ�G���[�������s���`����s��Ȃ�
	if (!m_sky) {
		throw std::runtime_error("m_skySphere.model is nullptr!");
	}

	// �v���W�F�N�V�����s����擾����
	const DirectX::SimpleMath::Matrix& projectionMatrix = m_cameraManager->GetProjectionMatrix();
	// �r���[�s����擾����
	const DirectX::SimpleMath::Matrix& viewMatrix       = m_cameraManager->GetViewMatrix();


	// ���f���̃G�t�F�N�g�����X�V����
	m_sky->UpdateEffects([](DirectX::IEffect* effect)
	{
		// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
		DirectX::DX11::BasicEffect* basicEffect = dynamic_cast<DirectX::DX11::BasicEffect*>(effect);
		if (basicEffect)
		{
			// �ʂ̃��C�g�����ׂĖ���������
			basicEffect->SetLightEnabled(0, false);
			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// ���f����������������
			basicEffect->SetEmissiveColor(DirectX::Colors::White);
		}
	});
	// �X�J�C�X�t�B�A��`�悷��
	m_sky->Draw(m_context, *m_commonStates, m_skySphere->GetWorldMatrix(),
		viewMatrix, projectionMatrix);

	// �e�p�`��
	m_shadowMap->Begin();
	// ���f���̕`��
	for (const auto& model : m_renderableObjects)
	{
		if (model.model != nullptr && model.object->GetIsActive())
			m_shadowMap->Draw(model.model,model.object->GetTransform()->GetWorldMatrix());
	}
	m_shadowMap->End();

	// ���f���̕`��
	for (const auto& model : m_renderableObjects)
	{
		if(model.model != nullptr && model.object->GetIsActive() )
		model.model->Draw(m_context, *m_commonStates, model.object->GetTransform()->GetWorldMatrix(),
			viewMatrix, projectionMatrix
		);
	}

	// �X�v���C�g�̕`��
	this->SpriteRender();
}


void RenderManager::SpriteRender()
{
	// �X�v���C�g�̕`��
	for (const auto& sprite : m_sprite)
	{
		if (sprite != nullptr)
		{
			// �}�e���A���̓K��
			sprite->Begin();

			// �T���v���[�X�e�[�g���s�N�Z���V�F�[�_�[�ɐݒ�
			ID3D11SamplerState* sampler[1] = { m_states->LinearWrap() };
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

			// �`��
			m_context->Draw(1, 0);
			// �}�e���A���̉��
			sprite->End();
		}
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
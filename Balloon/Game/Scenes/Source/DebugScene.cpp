#include "Framework/pch.h"
#include "Framework/CommonResources.h"
#include "Game/Scenes/Header/DebugScene.h"
#include "Interface/IScene.h"
#include "Interface/IObject.h"

#include "Game/Cameras/DebugCamera.h"
#include <Framework/Microsoft/ReadData.h>
#include <VertexTypes.h>
#include "Game/Material/PBRLit.h"
#include "Game/Sky/SkyBox.h"

DebugScene::DebugScene()
{
	m_commonResources = CommonResources::GetInstance();
}


DebugScene::~DebugScene()
{

}

void DebugScene::Initialize()
{
	ID3D11Device1* device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	// �萔�o�b�t�@�p�̃o�b�t�@�I�u�W�F�N�g���쐬����
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = static_cast<UINT>(sizeof(AmbientLightParameters));	// 16�̔{�����w�肷��
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	DX::ThrowIfFailed(
		device->CreateBuffer(&bufferDesc, nullptr, m_constantBuffer.ReleaseAndGetAddressOf())
	);


	D3D11_BLEND_DESC blendDesc = {};
	blendDesc.AlphaToCoverageEnable = FALSE; // �J�o���b�W���A���t�@�Ɋ�Â��ėL��������
	blendDesc.IndependentBlendEnable = FALSE; // �����̃����_�[�^�[�Q�b�g��Ɨ����Đݒ肷��

	D3D11_RENDER_TARGET_BLEND_DESC rtBlendDesc = {};
	rtBlendDesc.BlendEnable = TRUE;                                   // �u�����h��L����
	rtBlendDesc.SrcBlend = D3D11_BLEND_SRC_ALPHA;        // �\�[�X�̃A���t�@
	rtBlendDesc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;    // �t�A���t�@
	rtBlendDesc.BlendOp = D3D11_BLEND_OP_ADD;           // ���Z�u�����h
	rtBlendDesc.SrcBlendAlpha = D3D11_BLEND_ONE;              // �A���t�@�l�̃\�[�X
	rtBlendDesc.DestBlendAlpha = D3D11_BLEND_ZERO;             // �A���t�@�l�̃f�X�e�B�l�[�V����
	rtBlendDesc.BlendOpAlpha = D3D11_BLEND_OP_ADD;           // �A���t�@�l�̉��Z
	rtBlendDesc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // RGBA�S�Ă�L��

	blendDesc.RenderTarget[0] = rtBlendDesc;

	// �J�X�^���u�����h�X�e�[�g���쐬
	device->CreateBlendState(&blendDesc, &m_blendState);

	// ���f���擾
	m_sphereModel = m_commonResources->GetResources()->GetSphere();
	// ���f���̃G�t�F�N�g��ݒ肷��
	/*m_sphereModel->UpdateEffects([&](DirectX::IEffect* effect)
		{
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
			if (basicEffect)
			{
				basicEffect->SetLightingEnabled(true);
				basicEffect->SetPerPixelLighting(true);
				basicEffect->SetTextureEnabled(true);
				basicEffect->SetVertexColorEnabled(true);
				basicEffect->SetFogEnabled(false);
			}
		}
	);*/
	// �R�����X�e�[�g�擾
	m_commonStates = m_commonResources->GetCommonStates();

	// �f�o�b�O�J����
	m_debugCamera = std::make_unique<DebugCamera>();
	m_debugCamera->Initialize(1280, 720);

	// �V�F�[�_�[
	std::vector<uint8_t> blob;
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\PBRLit_VS.cso");
	DX::ThrowIfFailed(
		device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_vertexShader.ReleaseAndGetAddressOf())
	);

	//	�C���v�b�g���C�A�E�g�̍쐬
	device->CreateInputLayout(&DirectX::VertexPositionNormalTangentColorTexture::InputElements[0],
		static_cast<UINT>(DirectX::VertexPositionNormalTangentColorTexture::InputElementCount),
		blob.data(), blob.size(),
		m_inputLayout.GetAddressOf());

	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\PBRLit_PS.cso");
	DX::ThrowIfFailed(
		device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_pixelShader.ReleaseAndGetAddressOf())
	);

	// �e�N�X�`�����[�h
	// ���C���e�N�X�`��
	DirectX::CreateWICTextureFromFile(
		device, L"Resources\\Textures\\Cow_Color3.png", nullptr, m_mainTexture.ReleaseAndGetAddressOf());
	// �m�[�}���}�b�v
	DirectX::CreateWICTextureFromFile(
		device, L"Resources\\Textures\\woodNor.png", nullptr, m_normalMap.ReleaseAndGetAddressOf());
	// �X�J�C�}�b�v
	DirectX::CreateDDSTextureFromFile(
		device, L"Resources\\Textures\\Skybox.dds", nullptr, m_skyMap.ReleaseAndGetAddressOf());

	using namespace DirectX::SimpleMath;

	m_PBRLit = std::make_unique<PBRLit>();
	m_PBRLit->Initialize();
	m_PBRLit->SetBaseColor(DirectX::SimpleMath::Vector4::One);
	m_PBRLit->SetMatallic(1.0f); // 0.3
	m_PBRLit->SetSmoothness(0.0f); // 0.7
	m_PBRLit->SetUseBaseMap(1.0f);
	m_PBRLit->SetUseNormalMap(0.0f);
	m_PBRLit->SetBaseMap(m_mainTexture.Get());
	m_PBRLit->SetNormalMap(m_normalMap.Get());
	m_PBRLit->SetSkyMap(m_skyMap.Get());

	// ���f���̃G�t�F�N�g�����X�V����
	m_sphereModel->UpdateEffects([](DirectX::IEffect* effect) {
		// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
		DirectX::BasicEffect* basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
		if (basicEffect)
		{
			// �g�U���ˌ�
			Color diffuseColor = Color(0.3231373f, 0.3607844f, 0.3937255f);
			// ���C�g���Ƃ炷����
			Vector3 lightDirection(0.0f,1.0f,0.0f);

			//// ���C�g��L��������
			//// �����f���N���X�ł̓f�t�H���g�œ����I�Ƀ��C�g���L��������Ă���
			//basicEffect->SetLightingEnabled(true);

			// �ʂ̃��C�g��L����/����������
			basicEffect->SetLightEnabled(0, true);	// �f�t�H���g�l�ŗL��
			basicEffect->SetLightEnabled(1, false);
			basicEffect->SetLightEnabled(2, false);

			// �[���Ԃ̃��C�g�Ɋg�U���ˌ���ݒ肷��
			basicEffect->SetLightDiffuseColor(0, diffuseColor);
			// �[���Ԃ̃��C�g���Ƃ炷������ݒ肷��
			basicEffect->SetLightDirection(0, lightDirection);


		}
	});

	m_skyBox = std::make_unique<SkyBox>();
	m_skyBox->Initialize();
	
}

void DebugScene::Start()
{
	// BGM���Đ�����
}

void DebugScene::Update()
{
	// �J�������X�V
	m_debugCamera->Update();

	m_PBRLit->UpdateConstantBuffer();
	
	m_commonResources->GetCameraManager()->SetViewMatrix(m_debugCamera->GetViewMatrix());

	// GPU���g�p���郊�\�[�X�̃�������CPU����A�N�Z�X����ۂɗ��p����\����
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	// �R���e�L�X�g
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �萔�o�b�t�@���}�b�v����
	context->Map(m_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);

	// �萔�o�b�t�@�ɑ���f�[�^����������
	AmbientLightParameters* cb = static_cast<AmbientLightParameters*>(mappedResource.pData);
	cb->ambientLightColor = DirectX::SimpleMath::Vector3::One;
	cb->ambientLightIntensity = 0.7f;
	// �}�b�v����������
	context->Unmap(m_constantBuffer.Get(), 0);

	m_skyBox->Update(m_debugCamera->GetViewMatrix(), m_commonResources->GetCameraManager()->GetProjectionMatrix());
}

void DebugScene::Render()
{
	DirectX::DX11::CommonStates* states = m_commonResources->GetCommonStates();
	ID3D11DeviceContext1* context       = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();

	DirectX::SimpleMath::Matrix world      = DirectX::SimpleMath::Matrix::CreateTranslation(DirectX::SimpleMath::Vector3::Down * 9.0f);
	DirectX::SimpleMath::Matrix view       = m_debugCamera->GetViewMatrix();
	DirectX::SimpleMath::Matrix projection = m_commonResources->GetCameraManager()->GetProjectionMatrix();

	if (!m_vertexShader || !m_pixelShader)
	{
		OutputDebugStringA("Error: Shader not set!\n");
		return;
	}

	// ���f���`��
	m_sphereModel->Draw(context, *states, world, view, projection, false, [&]
		{
			// //�u�����h�X�e�[�g��ݒ� (�������`��p)
			//context->OMSetBlendState(m_blendState.Get(), nullptr, 0xFFFFFFFF);

			//// �C���v�b�g���C�A�E�g�̐ݒ�
			//context->IASetInputLayout(m_inputLayout.Get());

			//// �e�N�X�`���̐ݒ�
			//std::vector<ID3D11ShaderResourceView*> tex = {
			//	m_mainTexture.Get(),
			//	m_normalMap.Get(),
			//	m_skyMap.Get(),
			//};

			//context->VSSetShaderResources(0, (UINT)tex.size(), tex.data());
			//context->PSSetShaderResources(0, (UINT)tex.size(), tex.data());

			//// �V�F�[�_�[��ݒ�
			//context->VSSetShader(m_vertexShader.Get() , nullptr, 0);
			//context->PSSetShader(m_pixelShader.Get()  , nullptr, 0);

			//// �T���v���[�X�e�[�g���w�肷��
			//ID3D11SamplerState* sampler[] = { states->LinearWrap() };
			//context->VSSetSamplers(0, 1, sampler);
			//context->PSSetSamplers(0, 1, sampler);
		
		// �萔�o�b�t�@���w�肷��
		ID3D11Buffer* cbuf[] = { m_constantBuffer.Get() };
		context->VSSetConstantBuffers(1, 1, cbuf);
		context->PSSetConstantBuffers(1, 1, cbuf);

		m_PBRLit->SetMaterial();
		});

	m_skyBox->Render();
	//m_commonResources->GetRenderManager()->Render();
}


void DebugScene::Finalize()
{

}


#include "Framework/pch.h"
#include "Framework/Resources.h"
#include "Framework/CommonResources.h"
#include "Microsoft/ReadData.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

const std::vector<D3D11_INPUT_ELEMENT_DESC> Resources::UI_INPUT_LAYOUT =
{ 
   // �Z�}���e�B�b�N�� �C���f�b�N�X �t�H�[�}�b�g         ���̓X���b�g    �I�t�Z�b�g                                                                                                                                         �f�[�^���        �C���X�^���X�X�e�b�v��
		{ "SV_Position",0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  0,                                                                                                                                                         D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 position
		{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4),                                                                                                                      D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 rotate
		{ "TEXCOORD" ,  0, DXGI_FORMAT_R32G32B32_FLOAT,    0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3),                                                                               D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float3 scale
		{ "TEXCOORD" ,  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3),                                        D3D11_INPUT_PER_VERTEX_DATA, 0 }, // float4 rect
		{ "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,  sizeof(DirectX::SimpleMath::Vector4) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector3) + sizeof(DirectX::SimpleMath::Vector4), D3D11_INPUT_PER_VERTEX_DATA, 0 }  // float4 color
};
const std::vector<D3D11_INPUT_ELEMENT_DESC> Resources::SEA_INPUT_LAYOUT =
{
	{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                    D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(DirectX::SimpleMath::Vector3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

// Resources�N���X�̃C���X�^���X���擾����
Resources* const Resources::GetInstance()
{
	if (m_resources == nullptr)
	{
		// Resources�N���X�̃C���X�^���X�𐶐�����
		m_resources.reset(new Resources());
	}
	// Resources�N���X�̃C���X�^���X��Ԃ�
	return m_resources.get();
}

// ���\�[�X�����[�h����
void Resources::LoadResource()
{
	m_commonResources = CommonResources::GetInstance();

	m_device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	// �G�t�F�N�g�t�@�N�g���𐶐�����
	m_effectFactory = std::make_unique<DirectX::EffectFactory>(m_device);
	// ���\�[�X�f�B���N�g����ݒ肷��
	m_effectFactory->SetDirectory(L"Resources\\Models\\PlayerModels");
	// �v���C���[�@�����f�������[�h����
	m_playerHeadModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\Head.cmo", *m_effectFactory);
	// �v���C���[�@�̃��f�������[�h����
	m_playerBodyModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\Body.cmo", *m_effectFactory);
	// �v���C���[�@�E�r���f�������[�h����
	m_playerRightArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\RightArm.cmo", *m_effectFactory);
	// �v���C���[�@���r���f�������[�h����
	m_playerLeftArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\LeftArm.cmo", *m_effectFactory);
	// �v���C���[�@�E�����f�������[�h����
	m_playerRightFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\RightFoot.cmo", *m_effectFactory);
	// �v���C���[�@�������f�������[�h����
	m_playerLeftFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\PlayerModels\\LeftFoot.cmo", *m_effectFactory);

	// ���\�[�X�f�B���N�g����ݒ�
	m_effectFactory->SetDirectory(L"Resources\\Models\\EnemyModel");
	// �G�@�����f�������[�h����
	m_enemyHeadModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\EnemyModel\\EnemyFace.cmo", *m_effectFactory);

	// ���\�[�X�f�B���N�g����ݒ肷��
	m_effectFactory->SetDirectory(L"Resources\\Models");
	// �v���C���[�@���D���f�������[�h����
	m_balloonModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\Balloon.cmo", *m_effectFactory);
	// �v���C���[�@�_���f�������[�h����
	m_cloudModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\Cloud.cmo", *m_effectFactory);
	// ���\�[�X�f�B���N�g����ݒ肷��
	m_effectFactory->SetDirectory(L"Resources\\Models\\SkySphere");
	// �v���C���[�@�X�J�C�X�t�B�A���f�������[�h����
	m_skySphere = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Models\\SkySphere\\SkySphere.cmo", *m_effectFactory);

	//�@�e�N�X�`���̃��[�h
	// �^�C�g�����S
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\Logo.png", nullptr, m_titleLogo.ReleaseAndGetAddressOf());
	// �X�^�[�g�e�L�X�g
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\StartText.png", nullptr, m_startText.ReleaseAndGetAddressOf());
	// �X�y�[�X�L�[
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\SpaceKey.png", nullptr, m_spaceKey.ReleaseAndGetAddressOf());

	// �W�����v�t���[��
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\JumpFrameUI.png", nullptr, m_jampFrame.ReleaseAndGetAddressOf());
	// �W�����v������
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\JumpBar.png", nullptr, m_jampMemori.ReleaseAndGetAddressOf());
	// �^�C���t���[��
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\TimeFrame.png", nullptr, m_timeFrame.ReleaseAndGetAddressOf());
	// �^�C���Q�[�W
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\TimerBar.png", nullptr, m_timeGage.ReleaseAndGetAddressOf());
	// �i���o�[�Y
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\numberx128.png", nullptr, m_numbers.ReleaseAndGetAddressOf());
	// ���[���摜
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\200.png", nullptr, m_ruleTexture.ReleaseAndGetAddressOf());
	// �Q�[���N���A�e�L�X�g�摜
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\ClearText.png", nullptr, m_clearText.ReleaseAndGetAddressOf());
	// �Q�[���I�[�o�[�e�L�X�g�摜
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\FailedText.png", nullptr, m_failedText.ReleaseAndGetAddressOf());
	// �C�摜
	DirectX::CreateWICTextureFromFile(
		m_device, L"Resources\\Textures\\water5.png", nullptr, m_SeaTexture.ReleaseAndGetAddressOf());

	// �V�F�[�_�[
	std::vector<uint8_t> blob;
	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\UI_VS.cso");
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_UI_VS.ReleaseAndGetAddressOf())
	);
	//	�C���v�b�g���C�A�E�g�̍쐬
	m_device->CreateInputLayout(&UI_INPUT_LAYOUT[0],
		static_cast<UINT>(UI_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_UIinputLayout.GetAddressOf());

	// �W�I���g���V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\UI_GS.cso");
	DX::ThrowIfFailed(
		m_device->CreateGeometryShader(blob.data(), blob.size(), nullptr, m_UI_GS.ReleaseAndGetAddressOf())
	);
	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\UI_PS.cso");
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_UI_PS.ReleaseAndGetAddressOf())
	);

	// ���_�V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_VS.cso");
	DX::ThrowIfFailed(
		m_device->CreateVertexShader(blob.data(), blob.size(), nullptr, m_SeaVS.ReleaseAndGetAddressOf())
	);

	//	�C���v�b�g���C�A�E�g�̍쐬
	m_device->CreateInputLayout(&SEA_INPUT_LAYOUT[0],
		static_cast<UINT>(SEA_INPUT_LAYOUT.size()),
		blob.data(), blob.size(),
		m_SeaInputLayout.GetAddressOf());

	// �n���V�F�[�_�[�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_HS.cso");
	DX::ThrowIfFailed(
		m_device->CreateHullShader(blob.data(), blob.size(), nullptr, m_SeaHS.ReleaseAndGetAddressOf())
	);

	// �h���C���V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_DS.cso");
	DX::ThrowIfFailed(
		m_device->CreateDomainShader(blob.data(), blob.size(), nullptr, m_SeaDS.ReleaseAndGetAddressOf())
	);

	// �s�N�Z���V�F�[�_�����[�h����
	blob = DX::ReadData(L"Resources\\Shaders\\cso\\Sea_PS.cso");
	DX::ThrowIfFailed(
		m_device->CreatePixelShader(blob.data(), blob.size(), nullptr, m_SeaPS.ReleaseAndGetAddressOf())
	);
}

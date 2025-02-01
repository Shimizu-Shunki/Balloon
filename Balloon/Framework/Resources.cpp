#include "Framework/pch.h"
#include "Framework/Resources.h"
#include "Framework/CommonResources.h"

std::unique_ptr<Resources> Resources::m_resources = nullptr;

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
		m_device, L"Resources\\Textures\\132.png", nullptr, m_ruleTexture.ReleaseAndGetAddressOf());
}

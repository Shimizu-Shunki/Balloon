#include "pch.h"
#include "Framework/Resources.h"

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
	m_device = m_graphics->GetDeviceResources()->GetD3DDevice();

	// ���\�[�X�f�B���N�g����ݒ肷��
	m_graphics->GetFX()->SetDirectory(L"Resources\\Model\\PlayerModels");
	// �v���C���[�@�����f�������[�h����
	m_playerHeadModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\Head.cmo", *m_graphics->GetFX());
	// �v���C���[�@�̃��f�������[�h����
	m_playerBodyModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\Body.cmo", *m_graphics->GetFX());
	// �v���C���[�@�E�r���f�������[�h����
	m_playerRightArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\RightArm.cmo", *m_graphics->GetFX());
	// �v���C���[�@���r���f�������[�h����
	m_playerLeftArmModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\LeftArm.cmo", *m_graphics->GetFX());
	// �v���C���[�@�E�����f�������[�h����
	m_playerRightFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\RightFoot.cmo", *m_graphics->GetFX());
	// �v���C���[�@�������f�������[�h����
	m_playerLeftFootModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\PlayerModels\\LeftFoot.cmo", *m_graphics->GetFX());

	// ���\�[�X�f�B���N�g����ݒ肷��
	m_graphics->GetFX()->SetDirectory(L"Resources\\Model");
	// �v���C���[�@���D���f�������[�h����
	m_balloonModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\Balloon.cmo", *m_graphics->GetFX());
	// �v���C���[�@�_���f�������[�h����
	m_cloudModel = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\Cloud2.cmo", *m_graphics->GetFX());
	// �v���C���[�@�X�J�C�X�t�B�A���f�������[�h����
	m_skySphere = DirectX::Model::CreateFromCMO(m_device, L"Resources\\Model\\SkySphere3.cmo", *m_graphics->GetFX());
}

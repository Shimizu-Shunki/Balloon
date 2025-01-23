#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Graphics.h"

// Resources�N���X���`����
class Resources
{
public:
	// �v���C���[�@�����f�����擾����
	DirectX::Model* GetPlayerHeadModel() { return m_playerHeadModel.get(); }
	// �v���C���[�@�̃��f�����擾����
	DirectX::Model* GetPlayerBodyModel() { return m_playerBodyModel.get(); }
	// �v���C���[�@�E�r���f�����擾����
	DirectX::Model* GetPlayerRightArmModel() { return m_playerRightArmModel.get(); }
	// �v���C���[�@���r���f�����擾����
	DirectX::Model* GetPlayerLeftArmModel() { return m_playerLeftArmModel.get(); }
	// �v���C���[�@�E�����f�����擾����
	DirectX::Model* GetPlayerRightFootModel() { return m_playerRightFootModel.get(); }
	// �v���C���[�@�������f�����擾����
	DirectX::Model* GetPlayerLeftFootModel() { return m_playerLeftFootModel.get(); }

	// ���D�̃��f�����擾����
	DirectX::Model* GetBalloonModel() { return m_balloonModel.get(); }
	// �_�̃��f�����擾����
	DirectX::Model* GetCloudModel() { return m_cloudModel.get(); }

	// �X�J�C�X�t�B�A���擾����
	DirectX::Model* GetSkySphere() { return m_skySphere.get(); }

public:
	Resources(Resources&&) = default;
	Resources& operator= (Resources&&) = default;
	Resources& operator= (Resources const&) = delete;
	// �f�X�g���N�^
	~Resources() = default;
	// Resouces�N���X�̃C���X�^���X���擾����
	static Resources* const GetInstance();
	// ���\�[�X�����[�h����
	void LoadResource();

private:
	// �R���X�g���N�^
	Resources() noexcept
		:
		m_playerHeadModel{},
		m_playerBodyModel{},
		m_playerRightArmModel{},
		m_playerLeftArmModel{},
		m_playerRightFootModel{},
		m_playerLeftFootModel{},
		m_balloonModel{},
		m_cloudModel{}
	{
		
	}

private:
	// ���\�[�X
	static std::unique_ptr<Resources> m_resources;
	// �O���t�B�b�N�X
	Graphics* m_graphics = Graphics::GetInstance();
	// �f�o�C�X
	ID3D11Device* m_device = m_graphics->GetDeviceResources()->GetD3DDevice();


	// �v���C���[�@�����f��
	std::unique_ptr<DirectX::Model> m_playerHeadModel;
	// �v���C���[�@�̃��f��
	std::unique_ptr<DirectX::Model> m_playerBodyModel;
	// �v���C���[�@�E�r���f��
	std::unique_ptr<DirectX::Model> m_playerRightArmModel;
	// �v���C���[�@���r���f��
	std::unique_ptr<DirectX::Model> m_playerLeftArmModel;
	// �v���C���[�@�E�����f��
	std::unique_ptr<DirectX::Model> m_playerRightFootModel;
	// �v���C���[�@�������f��
	std::unique_ptr<DirectX::Model> m_playerLeftFootModel;

	// ���D���f��
	std::unique_ptr<DirectX::Model> m_balloonModel;
	// �_�̃��f��
	std::unique_ptr<DirectX::Model> m_cloudModel;

	// �X�J�C�X�t�B�A���f��
	std::unique_ptr<DirectX::Model> m_skySphere;
};

#endif		// RESOURCES_DEFINED
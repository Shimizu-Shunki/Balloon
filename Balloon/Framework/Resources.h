#pragma once
#ifndef RESOURCES_DEFINED
#define RESOURCES_DEFINED
#include "Model.h"
#include "Graphics.h"

class CommonResources;

// Resources�N���X���`����
class Resources
{
public:
	// ���f�����擾����
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

	// �e�N�X�`�����擾����
	// �^�C�g�����S���擾����
	ID3D11ShaderResourceView* GetTitleLogo() { return m_titleLogo.Get(); }
	// �X�^�[�g�e�L�X�g���擾����
	ID3D11ShaderResourceView* GetStartText() { return m_startText.Get(); }
	// �W�����v�t���[��
	ID3D11ShaderResourceView* GetJampFrame() { return m_jampFrame.Get(); }
	// �W�����v������
	ID3D11ShaderResourceView* GetJampMemori() { return m_jampMemori.Get(); }
	// �^�C���t���[��
	ID3D11ShaderResourceView* GetTimeFrame() { return m_timeFrame.Get(); }
	// �^�C���Q�[�W
	ID3D11ShaderResourceView* GetTimeGage() { return m_timeGage.Get(); }
	// �i���o�[�Y
	ID3D11ShaderResourceView* GetNumbers() { return m_numbers.Get(); }
	// ���[���摜
	ID3D11ShaderResourceView* GetRuleTexture() { return m_ruleTexture.Get(); }


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
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �f�o�C�X
	ID3D11Device* m_device;
	// �G�t�F�N�g�t�@�N�g���[
	std::unique_ptr<DirectX::EffectFactory> m_effectFactory;


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

	// �e�N�X�`��
	
	// �^�C�g���V�[��
	// �^�C�g�����S
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleLogo;
	// �X�^�[�g�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_startText;

	// �v���C�V�[��
	// �W�����v�t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jampFrame;
	// �W�����v������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_jampMemori;
	// �^�C���t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeFrame;
	// �^�C���Q�[�W
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeGage;
	// �i���o�[�Y
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_numbers;

	// ���[���摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ruleTexture;
};

#endif		// RESOURCES_DEFINED
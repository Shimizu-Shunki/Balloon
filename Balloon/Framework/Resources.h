#pragma once
#include "Model.h"
#include "Graphics.h"

class CommonResources;

// Resources�N���X���`����
class Resources
{
public:
	//	UI�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> UI_INPUT_LAYOUT;
	//	�C�C���v�b�g���C�A�E�g
	static const std::vector<D3D11_INPUT_ELEMENT_DESC> SEA_INPUT_LAYOUT;

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

	// �G�@�����f�����擾����
	DirectX::Model* GetEnemyHeadModel() { return m_enemyHeadModel.get(); }

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
	// �X�y�[�X�L�[
	ID3D11ShaderResourceView* GetSpaceKey() { return m_spaceKey.Get(); }
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
	// �C�摜
	ID3D11ShaderResourceView* GetSeaTexture() { return m_SeaTexture.Get(); }


	// �V�F�[�_�[���擾����
	// UI �C���v�b�g���C�A�E�g���擾����
	ID3D11InputLayout* GetUIinputLayout() { return m_UIinputLayout.Get(); }
	// UI ���_�V�F�[�_�[���擾
	ID3D11VertexShader*   GetUI_VS() { return m_UI_VS.Get(); }
	// UI �W�I���g���V�F�[�_�[���擾
	ID3D11GeometryShader* GetUI_GS() { return m_UI_GS.Get(); }
	// UI �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader*    GetUI_PS() { return m_UI_PS.Get(); }

	// �C �C���v�b�g���C�A�E�g���擾
	ID3D11InputLayout* GetSeaInputLayout() { return m_SeaInputLayout.Get(); }
	// �C ���_�V�F�[�_�[���擾
	ID3D11VertexShader* GetSeaVS() { return m_SeaVS.Get(); }
	// �C �W�I���g���V�F�[�_�[���擾
	ID3D11HullShader*   GetSeaHS() { return m_SeaHS.Get(); }
	// �C �W�I���g���V�F�[�_�[���擾
	ID3D11DomainShader* GetSeaDS() { return m_SeaDS.Get(); }
	// �C �s�N�Z���V�F�[�_�[���擾
	ID3D11PixelShader*  GetSeaPS() { return m_SeaPS.Get(); }



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
		m_enemyHeadModel{},
		m_balloonModel{},
		m_cloudModel{},
		m_spaceKey{},
		m_jampFrame{},
		m_jampMemori{},
		m_timeFrame{},
		m_timeGage{},
		m_numbers{},
		m_ruleTexture{},
		m_SeaTexture{},
		m_UIinputLayout{},
		m_UI_VS{},
		m_UI_GS{},
		m_UI_PS{},
		m_SeaInputLayout{},
		m_SeaVS{},
		m_SeaHS{},
		m_SeaDS{},
		m_SeaPS{}
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

	// �G�@�����f��
	std::unique_ptr<DirectX::Model> m_enemyHeadModel;


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
	// �X�y�[�X�L�[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_spaceKey;

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

	// �C�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SeaTexture;

	// �V�F�[�_�[
	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_UIinputLayout;

	// UI ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_UI_VS;
	// UI �W�I���g���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_UI_GS;
	// UI �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_UI_PS;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_SeaInputLayout;

	// �C ���_�V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_SeaVS;
	// �C �n���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11HullShader> m_SeaHS;
	// �C �h���C���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11DomainShader> m_SeaDS;
	// �C �s�N�Z���V�F�[�_�[
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_SeaPS;

};
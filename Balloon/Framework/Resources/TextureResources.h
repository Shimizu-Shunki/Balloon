#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

class TextureResources
{
public:
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
	// �Q�[���N���A�e�L�X�g
	ID3D11ShaderResourceView* GetClearTextTexture() { return m_clearText.Get(); }
	// �Q�[���I�[�o�[�e�L�X�g
	ID3D11ShaderResourceView* GetFailedTextTexture() { return m_failedText.Get(); }

	// �v���C���[
	ID3D11ShaderResourceView* GetPlayerTexture() { return m_playerTexture.Get(); }
	// �G
	ID3D11ShaderResourceView* GetEnemyTexture() { return m_enemyTexture.Get(); }

	// ���@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetMeatNormalMap() { return m_meatNormalMap.Get(); }
	// �؁@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetWoodNormalMap() { return m_woodNormalMap.Get(); }
	// ��@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetRockNormalMap() { return m_rockNormalMap.Get(); }
	// �C�@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetSeaNormalMap() { return m_seaNormalMap.Get(); }

	// �L���[�u�}�b�v
	ID3D11ShaderResourceView* GetCubeMap() { return m_cubeMap.Get(); }
	// �L���[�u�}�b�v �[��
	ID3D11ShaderResourceView* GetEveningCubeMap() { return m_eveningCubeMap.Get(); }


public:
	TextureResources(const TextureResources&) = delete;             // �R�s�[�֎~
	TextureResources& operator=(const TextureResources&) = delete;  // �R�s�[����֎~
	TextureResources(const TextureResources&&) = delete;            // ���[�u�֎~
	TextureResources& operator=(const TextureResources&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static TextureResources* GetInstance()
	{
		static TextureResources instance;
		return &instance;
	}
	// ���\�[�X�����[�h����
	void LoadResource(const nlohmann::json& data);

private:
	// �R���X�g���N�^
	TextureResources();

private:
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

	// �Q�[���N���A�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clearText;
	// �Q�[���N���A�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_failedText;

	// �C�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SeaTexture;

	// �v���C���[�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playerTexture;
	// �G�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_enemyTexture;

	// ���@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_meatNormalMap;
	// �؁@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_woodNormalMap;
	// ��@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_rockNormalMap;
	// �C�@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_seaNormalMap;

	// �L���[�u�}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubeMap;
	// �L���[�u�}�b�v�@�[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_eveningCubeMap;
};
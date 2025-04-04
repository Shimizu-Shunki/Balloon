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
	
	
	// ���[���摜
	ID3D11ShaderResourceView* GetRuleTexture() { return m_ruleTexture.Get(); }
	// �C�摜
	ID3D11ShaderResourceView* GetSeaTexture() { return m_SeaTexture.Get(); }
	// �Q�[���N���A�e�L�X�g
	ID3D11ShaderResourceView* GetClearTextTexture() { return m_clearText.Get(); }
	// �Q�[���I�[�o�[�e�L�X�g
	ID3D11ShaderResourceView* GetFailedTextTexture() { return m_failedText.Get(); }
	
	// ���f�B�S�[
	ID3D11ShaderResourceView* GetReadyGoTexture() { return m_readyGo.Get(); }
	// ���j���[�{�^���e�L�X�g
	ID3D11ShaderResourceView* GetMenuButtonText() { return m_menuButtonText.Get(); }
	// �ԍ��X�v���C�g�V�[�g
	ID3D11ShaderResourceView* GetNumbers() { return m_numbers.Get(); }
	// �ԍ��X�v���C�g�V�[�g1
	ID3D11ShaderResourceView* GetNumbers1() { return m_numbers1.Get(); }
	// �L�[�������
	ID3D11ShaderResourceView* GetKeyGuide() { return m_keyGuide.Get(); }
	// ���j���[�{�^���t���[��
	ID3D11ShaderResourceView* GetMenuButtonFrame() { return m_menuButtonFrame.Get(); }
	// ���j���[�{�^���t���[��2
	ID3D11ShaderResourceView* GetMenuButtonFrame2() { return m_menuButtonFrame2.Get(); }
	// �X�^�[�g�e�L�X�g
	ID3D11ShaderResourceView* GetStartText() { return m_startText.Get(); }

	// �v���C���[�A�C�R��
	ID3D11ShaderResourceView* GetPlayerIcon() { return m_playerIcon.Get(); }
	// �v���C�V�[���L�[�K�C�h
	ID3D11ShaderResourceView* GetPlaySceneKeysGuide() { return m_playSceneKeysGuide.Get(); }
	// �^�C���t���[��
	ID3D11ShaderResourceView* GetTimeFrame() { return m_timeFrame.Get(); }
	// �X�R�A�t���[��
	ID3D11ShaderResourceView* GetScoreFrame() { return m_scoreFrame.Get(); }
	// �o���[���Q�[�W�t���[��
	ID3D11ShaderResourceView* GetBalloonGageFrame() { return m_balloonGageFrame.Get(); }
	// �o���[���Q�[�W
	ID3D11ShaderResourceView* GetBalloonGage() { return m_balloonGage.Get(); }
	// �������[�^�[
	ID3D11ShaderResourceView* GetHeightMeter() { return m_heightMeter.Get(); }
	// HP�Q�[�W
	ID3D11ShaderResourceView* GetHPGage() { return m_hpGage.Get(); }
	// HP�Q�[�W�t���[��
	ID3D11ShaderResourceView* GetHPGageFrame() { return m_hpGageFrame.Get(); }


	// �v���C���[
	ID3D11ShaderResourceView* GetPlayerTexture() { return m_playerTexture.Get(); }
	// �G
	ID3D11ShaderResourceView* GetEnemyTexture() { return m_enemyTexture.Get(); }
	// ���D
	ID3D11ShaderResourceView* GetBalloonTexture() { return m_balloonTexture.Get(); }

	// ���@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetMeatNormalMap() { return m_meatNormalMap.Get(); }
	// �؁@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetWoodNormalMap() { return m_woodNormalMap.Get(); }
	// ��@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetRockNormalMap() { return m_rockNormalMap.Get(); }
	// �C�@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetSeaNormalMap() { return m_seaNormalMap.Get(); }
	// �_�@�m�[�}���}�b�v
	ID3D11ShaderResourceView* GetCloudNormalMap() { return m_cloudNormalMap.Get(); }

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
	
	// �v���C�V�[��
	// �v���C���[�A�C�R��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playerIcon;
	// �v���C�V�[���L�[�K�C�h
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playSceneKeysGuide;
	// �^�C���t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeFrame;
	// �X�R�A�t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_scoreFrame;
	// �o���[���Q�[�W�t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_balloonGageFrame;
	// �o���[���Q�[�W
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_balloonGage;
	// �������[�^�[
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_heightMeter;
	// HP�Q�[�W
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hpGage;
	// HP�Q�[�W�t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_hpGageFrame;
	

	// ���[���摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_ruleTexture;

	// �Q�[���N���A�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_clearText;
	// �Q�[���N���A�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_failedText;

	// �C�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_SeaTexture;

	// ���f�B�S�[�@
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_readyGo;
	// ���j���[�{�^��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_menuButtonText;
	// �����X�v���C�g�V�[�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_numbers;
	// �L�[�������
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_keyGuide;
	// ���j���[�{�^���t���[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_menuButtonFrame;
	// ���j���[�{�^���t���[��2
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_menuButtonFrame2;
	// �X�^�[�g�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_startText;

	// �X�^�[�g�e�L�X�g
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_numbers1;


	// �v���C���[�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_playerTexture;
	// �G�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_enemyTexture;
	// ���D�e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_balloonTexture;

	// ���@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_meatNormalMap;
	// �؁@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_woodNormalMap;
	// ��@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_rockNormalMap;
	// �C�@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_seaNormalMap;
	// �_�@�m�[�}���}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cloudNormalMap;

	// �L���[�u�}�b�v
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_cubeMap;
	// �L���[�u�}�b�v�@�[��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_eveningCubeMap;
};
// ============================================
// 
// �t�@�C����: FadeOutState.cpp
// �T�v: �t�F�[�h�A�E�g�̃X�e�[�g
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/Fade/Fade.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Game/Scenes/Header/GameOverScene.h"
#include "Game/Scenes/Header/TitleScene.h"
#include "Game/Scenes/Header/MenuScene.h"
#include "Game/Scenes/Header/PlayScene.h"
#include "Game/Scenes/Header/StageSelectScene.h"
#include "Framework/SceneManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="fade">�t�F�[�h����</param>
/// <param name="chageSceneID">�V�[��ID</param>
FadeOutState::FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID)
{
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_sceneManager = SceneManager::GetInstance();
	// �V�[��ID�o�^
	m_chageSceneId = chageSceneID;
	// �t�F�[�h�������擾
	m_fade = fade;
}


/// <summary>
/// ��������
/// </summary>
void FadeOutState::PreUpdate()
{
	switch (m_chageSceneId)
	{
		case FadeOutState::ChageSceneID::TITLE_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<TitleScene>();
			m_fade->ChangeSceneFadeOUT<TitleScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::MENU_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<MenuScene>();
			m_fade->ChangeSceneFadeOUT<MenuScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::SELECT_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<StageSelectScene>();
			m_fade->ChangeSceneFadeOUT<StageSelectScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::PLAY_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<PlayScene>();
			m_fade->ChangeSceneFadeOUT<PlayScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::GAME_CLEAR_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<GameClearScene>();
			m_fade->ChangeSceneFadeOUT<GameClearScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::GAME_OVER_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<GameOverScene>();
			m_fade->ChangeSceneFadeOUT<GameOverScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::EXIT_GAME:
			// �Q�[���I���t�F�[�h�A�E�g
			m_fade->ExitGameFadeOUT(1.0f);
			break;
		default:
			break;
	}
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void FadeOutState::Update(const float& deltaTime)
{
	(void)deltaTime;

	// �t�F�[�h�̍X�V
	m_fade->Update();
}

/// <summary>
/// �I������
/// </summary>
void FadeOutState::PostUpdate()
{

}
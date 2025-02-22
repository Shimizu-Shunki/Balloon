#include "Framework/pch.h"
#include "Game/States/Fade/FadeOutState.h"
#include "Game/Fade/Fade.h"
#include "Game/Scenes/Header/GameClearScene.h"
#include "Game/Scenes/Header/GameOverScene.h"
#include "Game/Scenes/Header/TitleScene.h"

// �R���X�g���N�^
FadeOutState::FadeOutState(Fade* fade, const FadeOutState::ChageSceneID& chageSceneID)
{
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_sceneManager = SceneManager::GetInstance();

	m_chageSceneId = chageSceneID;

	m_fade = fade;
}

// �f�X�g���N�^
FadeOutState::~FadeOutState()
{

}

// ����������
void FadeOutState::OnStateEnter(StateController* stateController)
{
	switch (m_chageSceneId)
	{
		case FadeOutState::ChageSceneID::TITLE_SCENE:
			// ���̃V�[���̏�������񓯊��Ŏ��s
			m_sceneManager->PrepareScene<TitleScene>();
			m_fade->ChangeSceneFadeOUT<TitleScene>(1.0f);
			break;
		case FadeOutState::ChageSceneID::SELECT_SCENE:

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
		default:
			break;
	}
}

// �X�V����
void FadeOutState::OnStateUpdate(StateController* stateController, const float& deltaTime)
{
	
}

// �I������
void FadeOutState::OnStateExit(StateController* stateController)
{

}
#include "pch.h"
#include "Scenes/ResultScene/ResultScene.h"

#include "Framework/InputManager.h"

#include "Interface/IScene.h"




ResultScene::ResultScene(SceneManager* scene_manager)
{
	// �O���t�B�b�N�X�C���X�^���X���擾����
	m_graphics = Graphics::GetInstance();
	// �V�[���}�l�[�W���[�̃C���X�^���X���擾����
	m_scene_manager = scene_manager;
	// �C���v�b�g�}�l�[�W���[�̃C���X�^���X���擾����
	m_input_manager = InputManager::GetInstance();
}

void ResultScene::Initialize()
{

}

void ResultScene::Start()
{

}


void ResultScene::Update(float elapsed_time)
{
	
}

void ResultScene::Render()
{
	m_graphics->GetSpriteBatch()->Begin();
	m_graphics->DrawString(10.0f, 60.0f, L"ResultScene");
	m_graphics->GetSpriteBatch()->End();
}

void ResultScene::Finalize()
{

}
#include "pch.h"
#include "Scenes/ResultScene/ResultScene.h"

#include "Framework/InputManager.h"

#include "Interface/IScene.h"




ResultScene::ResultScene(SceneManager* scene_manager)
{
	// グラフィックスインスタンスを取得する
	m_graphics = Graphics::GetInstance();
	// シーンマネージャーのインスタンスを取得する
	m_scene_manager = scene_manager;
	// インプットマネージャーのインスタンスを取得する
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
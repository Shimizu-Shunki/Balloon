#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/SceneMessenger.h"

SceneMessenger::SceneMessenger()
{

}


void SceneMessenger::Register(IScene* scene)
{
	// シーンを登録する
	m_scene = scene;
}

/// <summary>
/// オブジェクトを解除する
/// </summary>
void SceneMessenger::Clear()
{
	m_scene = nullptr;
}


/// <summary>
/// シーンにメッセージを送信する
/// </summary>
/// <param name="messageID"></param>
void SceneMessenger::Dispatch(Message::SceneMessageID messageID)
{
	m_scene->OnSceneMessegeAccepted(messageID);
}
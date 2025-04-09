// ============================================
// 
// ファイル名: SceneMessenger.cpp
// 概要: シーンのメッセンジャー（シングルトン）
// 
// 製作者 : 清水駿希
// 
// ============================================
#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/SceneMessenger.h"

/// <summary>
/// コンストラクタ
/// </summary>
SceneMessenger::SceneMessenger()
	:
	m_scene{}
{

}

/// <summary>
/// オブジェクトを登録する
/// </summary>
/// <param name="objectID"></param>
/// <param name="object"></param>
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
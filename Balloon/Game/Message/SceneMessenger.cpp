#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/SceneMessenger.h"

SceneMessenger::SceneMessenger()
{

}


void SceneMessenger::Register(IScene* scene)
{
	// �V�[����o�^����
	m_scene = scene;
}

/// <summary>
/// �I�u�W�F�N�g����������
/// </summary>
void SceneMessenger::Clear()
{
	m_scene = nullptr;
}


/// <summary>
/// �V�[���Ƀ��b�Z�[�W�𑗐M����
/// </summary>
/// <param name="messageID"></param>
void SceneMessenger::Dispatch(Message::SceneMessageID messageID)
{
	m_scene->OnSceneMessegeAccepted(messageID);
}
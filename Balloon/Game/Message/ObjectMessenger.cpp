#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/ObjectMessenger.h"


ObjectMessenger::ObjectMessenger()
{

}

void ObjectMessenger::Register(int objectID, IObject* object)
{
	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g��o�^����
	m_pendingObjects.emplace(objectID, object);
}

/// <summary>
/// �I�u�W�F�N�g����������
/// </summary>
void ObjectMessenger::Clear()
{
	m_objects.clear();
}


void ObjectMessenger::Dispatch(int objectID, Message::ObjectMessageID messageID)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
		it->second->OnObjectMessegeAccepted(messageID);
	}
}

void ObjectMessenger::ApplyChanges()
{
	// ���݂̕����N���A����
	m_objects.clear();
	// �����i�K�̂��̂𔽉f
	m_objects = m_pendingObjects;
	// �����i�K�̂��̂��N���A����
	m_pendingObjects.clear();
}

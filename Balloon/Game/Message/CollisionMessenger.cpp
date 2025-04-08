#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/CollisionMessenger.h"

CollisionMessenger::CollisionMessenger()
{

}

/// <summary>
/// �I�u�W�F�N�g��o�^����
/// </summary>
/// <param name="objectID"></param>
/// <param name="object"></param>
void CollisionMessenger::Register(int objectID, IObject* object)
{
	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g��o�^����
	m_pendingObjects.emplace(objectID, object);
}

/// <summary>
/// �I�u�W�F�N�g����������
/// </summary>
void CollisionMessenger::Clear()
{
	m_objects.clear();
}

/// <summary>
/// �V�[���Ƀ��b�Z�[�W�𑗐M����
/// </summary>
/// <param name="messageID"></param>
void CollisionMessenger::Dispatch(int objectID, Message::CollisionMessageID messageID, IObject* sender)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
		it->second->OnCollisionMessegeAccepted(messageID , sender);
	}
}

IObject* CollisionMessenger::GetObject(int objectID)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);

	return it->second;
}

void CollisionMessenger::ApplyChanges()
{
	// ���݂̕����N���A����
	m_objects.clear();
	// �����i�K�̂��̂𔽉f
	m_objects = m_pendingObjects;
	// �����i�K�̂��̂��N���A����
	m_pendingObjects.clear();
}
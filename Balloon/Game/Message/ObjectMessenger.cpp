#include "pch.h"
#include "Game/Message/ObjectMessenger.h"

ObjectMessenger::ObjectMessenger()
{

}


// �I�u�W�F�N�g��o�^����
void ObjectMessenger::Register(int objectID, IObject* object)
{
	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g��o�^����
	m_objects.emplace(objectID, object);
}

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
void ObjectMessenger::Dispatch(int objectID, Message::MessageData messageData)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
		it->second->OnMessegeAccepted(messageData);
	}
}

// �I�u�W�F�N�g�Ƀ��b�Z�[�W�𑗐M����
void ObjectMessenger::Dispatch(int objectID, Message::MessageID messageID)
{
	Message::MessageData messageData(messageID);

	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// ���M����I�u�W�F�N�g�̃��b�Z�[�W�n���h�����Ăяo��
		it->second->OnMessegeAccepted(messageData);
	}
}


// �I�u�W�F�N�g���擾����
IObject* ObjectMessenger::GetObjectI(int objectID)
{
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g����������
	auto it = m_objects.find(objectID);
	// ���b�Z�[�W�𑗐M����I�u�W�F�N�g�����������ꍇ
	if (it != m_objects.end())
	{
		// �I�u�W�F�N�g���擾����
		return it->second;
	}
	return nullptr;
}
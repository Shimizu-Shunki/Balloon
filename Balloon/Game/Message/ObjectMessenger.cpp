// ============================================
// 
// �t�@�C����: CollisionMessenger.cpp
// �T�v: �I�u�W�F�N�g�̃��b�Z���W���[�i�V���O���g���j
// 
// ����� : �����x��
// 
// ============================================
#include "Framework/pch.h"
#include <unordered_map>
#include "Game/Message/ObjectMessenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ObjectMessenger::ObjectMessenger()
	:
	m_objects{},
	m_pendingObjects{}
{

}

/// <summary>
/// �I�u�W�F�N�g��o�^
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="object">�I�u�W�F�N�g</param>
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

/// <summary>
/// ���b�Z�[�W���M
/// </summary>
/// <param name="objectID">�I�u�W�F�N�gID</param>
/// <param name="messageID">���b�Z�[�WID</param>
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

/// <summary>
/// ���b�Z�[�W���M�i���b�Z�[�W�f�[�^��n����悤�ɂ���֐��j
/// </summary>
/// <param name="objectID"></param>
/// <param name="messageData"></param>
void ObjectMessenger::Dispatch(int objectID, MessageData messageData)
{

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

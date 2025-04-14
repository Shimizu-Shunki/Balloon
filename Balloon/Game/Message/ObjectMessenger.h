// ============================================
// 
// �t�@�C����: ObjectMessenger.h
// �T�v: ObjectMessenger.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Game/Message/Message.h"
#include "Interface/IObject.h"

class ObjectMessenger
{
public:

	struct MessageData
	{
		Message::ObjectMessageID id;
		int intValue = 0;
		float floatValue = 0.0f;
		bool boolValue = false;
	};

public:
	// �I�u�W�F�N�g��o�^����
	void Register(int objectID, IObject* object);
	// �I�u�W�F�N�g��S�ĉ�������
	void Clear();
	// ���b�Z�[�W�𑗐M����
	void Dispatch(int objectID, Message::ObjectMessageID messageID);
	void Dispatch(int objectID, MessageData messageData);

private:
	//	�R���X�g���N�^
	ObjectMessenger();
	// �f�X�g���N�^
	~ObjectMessenger() = default;
public:
	ObjectMessenger(const ObjectMessenger&) = delete;             // �R�s�[�֎~
	ObjectMessenger& operator=(const ObjectMessenger&) = delete;  // �R�s�[����֎~
	ObjectMessenger(const ObjectMessenger&&) = delete;            // ���[�u�֎~
	ObjectMessenger& operator=(const ObjectMessenger&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static ObjectMessenger* GetInstance()
	{
		static ObjectMessenger instance;
		return &instance;
	}

	// �����i�K�̕��𔽉f
	void ApplyChanges();

private:

	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g�}�b�s���O
	std::unordered_map<int, IObject*> m_objects;

	// �����i�K�@�I�u�W�F�N�gID�ƃI�u�W�F�N�g�}�b�s���O
	std::unordered_map<int, IObject*> m_pendingObjects;

};
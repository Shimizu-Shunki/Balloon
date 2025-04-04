#pragma once
#include "Game/Message/Message.h"
#include "Interface/IObject.h"

class CollisionMessenger
{
public:
	// �I�u�W�F�N�g��o�^����
	void Register(int objectID, IObject* object);
	// �I�u�W�F�N�g��S�ĉ�������
	void Clear();
	// ���b�Z�[�W�𑗐M����
	void Dispatch(int objectID , Message::CollisionMessageID messageID , IObject* sender);

	// �o�^�����I�u�W�F�N�g���擾����
	IObject* GetObject(int objectID);

private:
	//	�R���X�g���N�^
	CollisionMessenger();
	// �f�X�g���N�^
	~CollisionMessenger() = default;
public:
	CollisionMessenger(const CollisionMessenger&) = delete;             // �R�s�[�֎~
	CollisionMessenger& operator=(const CollisionMessenger&) = delete;  // �R�s�[����֎~
	CollisionMessenger(const CollisionMessenger&&) = delete;            // ���[�u�֎~
	CollisionMessenger& operator=(const CollisionMessenger&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static CollisionMessenger* GetInstance()
	{
		static CollisionMessenger instance;
		return &instance;
	}

private:

	// �I�u�W�F�N�gID�ƃI�u�W�F�N�g�}�b�s���O
	std::unordered_map<int, IObject*> m_objects;

};
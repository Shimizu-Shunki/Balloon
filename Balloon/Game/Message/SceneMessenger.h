#pragma once
#include "Game/Message/Message.h"
#include "Interface/IScene.h"

class SceneMessenger
{
public:
	// �V�[����o�^����
	void Register(IScene* scene);
	// �V�[������������
	void Clear();
	// ���b�Z�[�W�𑗐M����
	void Dispatch(Message::SceneMessageID messageID);

private:
	//	�R���X�g���N�^
	SceneMessenger();
	// �f�X�g���N�^
	~SceneMessenger() = default;
public:
	SceneMessenger(const SceneMessenger&) = delete;             // �R�s�[�֎~
	SceneMessenger& operator=(const SceneMessenger&) = delete;  // �R�s�[����֎~
	SceneMessenger(const SceneMessenger&&) = delete;            // ���[�u�֎~
	SceneMessenger& operator=(const SceneMessenger&&) = delete; // ���[�u����֎~

	//	�V���O���g���C���X�^���X�̎擾
	static SceneMessenger* GetInstance()
	{
		static SceneMessenger instance;
		return &instance;
	}

private:
	// �V�[��
	IScene* m_scene;
};
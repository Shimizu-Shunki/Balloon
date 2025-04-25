#pragma once
#include "Interface/IObject.h"
#include "Interface/IState.h"

class UIObject : public IObject
{
public:
	// �I�u�W�F�N�g���J�E���g�A�b�v����
	static int CountUpNumber();
	// ���݂̃I�u�W�F�N�g�J�E���g���擾
	static int ResetNumber();

public:

	// �R���X�g���N�^
	UIObject();
	// �f�X�g���N�^
	~UIObject();
	// ����������
	void Initialize();
	// �X�V����
	void Update(const float& elapsedTime);
	// �㏈�����s��
	void Finalize();

private:
	// �I�u�W�F�N�g�ԍ�
	static int s_objectNumber;
	// ���݂̃��b�Z�[�W
	Message m_currentMessage;
};
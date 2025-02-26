#pragma once
#include "Interface/IObject.h"

class IObject;

class ICollision
{
	/*�E�����蔻��@
		�㉺���E�̓����蔻��
		�g���K�[�Ȃ�
		�����������i����̃I�u�W�F�N�g�j
		�������Ă��鎞�i����̃I�u�W�F�N�g�j
		���ꂽ�u�ԁi����̃I�u�W�F�N�g�j
		�ڍׂȓ����蔻��i����̃I�u�W�F�N�g�A�ǂ̕����ɓ������Ă��邩�j
		�g���K�[����
		�����������i����̃I�u�W�F�N�g�j
		�������Ă��鎞�i����̃I�u�W�F�N�g�j*/

public:
	// �Փ˂���������
	virtual void OnCollisionEnter(IObject* object) = 0;
	// �Փ˂��Ă��鎞
	virtual void OnCollisionStay(IObject* object) = 0;
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	virtual void OnCollisionExit(IObject* object) = 0;

	// �Փ˂����������i�g���K�[�j
	virtual void OnTriggerEnter(IObject* object) = 0;
	// �Փ˂��Ă��鎞�i�g���K�[�j
	virtual void OnTriggerStay(IObject* object) = 0;
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	virtual void OnTriggerExit(IObject* object) = 0;
};

#pragma once
#include "Interface/IComponent.h"
#include "Game/Collider/Collider.h"

class IComponent;
class Collider;

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
	// �����蔻����擾����
	virtual const std::vector<std::unique_ptr<Collider>>& GetColliders() const = 0;

	// �Փ˂���������
	virtual void OnCollisionEnter(IComponent* object) {};
	// �Փ˂��Ă��鎞
	virtual void OnCollisionStay(IComponent* object) {};
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	virtual void OnCollisionExit(IComponent* object) {};

	// �Փ˂����������i�g���K�[�j
	virtual void OnTriggerEnter(IComponent* object) {};
	// �Փ˂��Ă��鎞�i�g���K�[�j
	virtual void OnTriggerStay(IComponent* object) {};
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	virtual void OnTriggerExit(IComponent* object) {};
};

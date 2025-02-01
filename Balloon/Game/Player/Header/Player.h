#pragma once

#include "Interface/IComposite.h"
#include "Interface/IObject.h"
#include "Framework/Graphics.h"

#include <Interface/ICamera.h>

class CommonResources;
class IComposite;



class Player : public IComposite
{
public:
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ������擾����
	bool GetIsActive() const override { return m_isActive; }
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ�����ݒ肷��
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectId; }
	// ���f�����擾����
	DirectX::Model* GetModel() const override { return m_model; }

	// Transform�̎擾
	Transform* GetTransform() const override { return m_transform.get(); }
	// �����I���l
	// �����蔻��
	
public:
	// �R���X�g���N�^
	// �J�����̏��A�e�̃I�u�W�F�N�g
	Player(ICamera* camera, IObject* parent);
	// �f�X�g���N�^
	~Player();

public:
	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
	// �X�V����
	void Update() override;
	// �I������
	void Finalize() override;

	// �Փ˂���������
	void OnCollisionEnter(IObject* object) override;
	// �Փ˂��Ă��鎞
	void OnCollisionStay(IObject* object) override;
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	void OnCollisionExit(IObject* object) override;

	// �Փ˂����������i�g���K�[�j
	void OnTriggerEnter(IObject* object) override;
	// �Փ˂��Ă��鎞�i�g���K�[�j
	void OnTriggerStay(IObject* object) override;
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	void OnTriggerExit(IObject* object) override;

	// ���i��ǉ�����
	void Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId) override;
	// ���i���폜����
	void Detach(std::unique_ptr<IObject> turretPart) override;


public:

	void BalloonDetach();

private:
	// �ړ�����
	DirectX::SimpleMath::Vector3 GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle);
	// �W�����v����
	//void Jump(const float& elapsedTime);
	// �W�����v�񐔉񕜏���
	void RecoverJump();


private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �e�̃I�u�W�F�N�g
	IObject* m_parent;
	// �q���̃I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_childs;

	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectId;
	// �I�u�W�F�N�g�A�N�e�B�u
	bool m_isActive;

	// Transform �S�ẴI�u�W�F�N�g������
	std::unique_ptr<Transform> m_transform;

	// �����I���l


	// �J����
	ICamera* m_camera;

	// 3D���f��
	DirectX::Model* m_model;
	// ���D�̐�
	int m_balloonIndex;
};

#pragma once

#include "Interface/IComposite.h"
#include "Interface/ILeaf.h"
#include "Interface/IObject.h"
#include "Framework/Graphics.h"

#include <Interface/ICamera.h>

class CommonResources;
class IComposite;


// ���D�@�q�I�u�W�F�N�g�͂Ȃ�
class Balloon : public ILeaf
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
	Balloon(IObject* parent , float angle);
	// �f�X�g���N�^
	~Balloon();

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

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;
	// �e�̃I�u�W�F�N�g
	IObject* m_parent;
	
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectId;
	// �I�u�W�F�N�g�A�N�e�B�u
	bool m_isActive;

	// Transform �S�ẴI�u�W�F�N�g������
	std::unique_ptr<Transform> m_transform;

	// �����I���l

	// 3D���f��
	DirectX::Model* m_model;

	// ��]�p
	float m_angle;
};

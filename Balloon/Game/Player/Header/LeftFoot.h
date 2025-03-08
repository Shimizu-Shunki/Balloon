#pragma once
#include "Interface/ILeaf.h"
#include "Interface/IObject.h"

class Model3D;

class LeftFoot : public ILeaf
{
public:
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ������擾����
	bool GetIsActive() const override { return m_isActive; }
	// �I�u�W�F�N�g���A�N�e�B�u���ǂ�����ݒ肷��
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// �I�u�W�F�N�gID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectId; }
	// Transform�̎擾
	Transform* GetTransform() const override { return m_transform.get(); }

public:
	// �R���X�g���N�^
	// �J�����̏��A�e�̃I�u�W�F�N�g
	LeftFoot(IObject* parent);
	// �f�X�g���N�^
	~LeftFoot() override = default;

public:
	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transform�̏�����
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// �X�V����
	void Update() override;
	// �I������
	void Finalize() override;

	// �Փ˂���������
	void OnCollisionEnter(IObject* object) override { (void)object; };
	// �Փ˂��Ă��鎞
	void OnCollisionStay(IObject* object) override  { (void)object; };
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	void OnCollisionExit(IObject* object) override  { (void)object; };

	// �Փ˂����������i�g���K�[�j
	void OnTriggerEnter(IObject* object) override   { (void)object; };
	// �Փ˂��Ă��鎞�i�g���K�[�j
	void OnTriggerStay(IObject* object) override    { (void)object; };
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	void OnTriggerExit(IObject* object) override    { (void)object; };

private:
	// �e�̃I�u�W�F�N�g
	IObject* m_parent;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectId;
	// �I�u�W�F�N�g�A�N�e�B�u
	bool m_isActive;

	// Transform �S�ẴI�u�W�F�N�g������
	std::unique_ptr<Transform> m_transform;
	// 3D���f��
	std::unique_ptr<Model3D> m_model;
};

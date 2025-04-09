// ============================================
// 
// �t�@�C����: BalloonGageUI.h
// �T�v: BalloonGageUI.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include "Game/Image/Image.h"

class IObject;
class Image;
class Transform;
class IMaterial;

class BalloonGageUI : public IObject
{
private:
	static const float SPEED_SLOW;
	static const float SPEED_NORMAL;
	static const float SPEED_FAST;

public:
	// �I�u�W�F�N�g�A�N�e�B�u���擾����
	bool GetIsActive() const  override { return m_isActive; }
	// �I�u�W�F�N�g�A�N�e�B�u��ݒ肷��
	void SetIsActive(bool isActive) {
		m_isActive = isActive;
		m_image->SetIsActive(isActive);
	}
	// Transform�̎擾
	Transform* GetTransform() const override { return m_transform.get(); }
	// �I�u�W�F�N�g��ID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectId; }

public:

	// �R���X�g���N�^
	BalloonGageUI();
	// �f�X�g���N�^
	~BalloonGageUI() = default;

	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
	// �X�V����
	void Update() override;
	// Transform�̏�����
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// �I������
	void Finalize() override;
	// �I�u�W�F�N�g���b�Z�[�W���󂯎��
	void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) override;
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender) override;

private:
	// �}�e���A���̏���������
	void InitialMaterial(int width, int height);

private:

	// �A�N�e�B�u�ݒ�
	bool m_isActive;
	// �I�u�W�F�N�gID
	IObject::ObjectID m_objectId;
	// �g�����X�t�H�[��
	std::unique_ptr<Transform> m_transform;

	// Image
	std::unique_ptr<Image> m_image;
	// �}�e���A��
	std::unique_ptr<IMaterial> m_material;

	// ���݂̑傫��
	float m_currentScale;
	// �c���ł�����
	bool m_isBalloon;
	// �c��܂��鑬�x
	float m_speed;
};
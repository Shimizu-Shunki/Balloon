// ============================================
// 
// �t�@�C����: MenuButtonFrameUI.h
// �T�v: MenuButtonFrameUI.cpp�̃w�b�_�[�t�@�C��
// 
// ����� : �����x��
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include "Game/Image/Image.h"

class IObject;
class Transform;
class Image;
class IMaterial;

class MenuButtonFrameUI : public IObject
{
private:
	static const float STAGE_SELECT_WIDTH;
	static const float SETTING_WIDTH;
	static const float EXIT_WIDTH;

	static const float STAGE_SELECT_WIDTH2;
	static const float SETTING_WIDTH2;
	static const float EXIT_WIDTH2;

	static const float BUTTON_HEIGHT;
	static const float BUTTON_HEIGHT2;

public:
	// �{�^���̎��
	enum class ButtonType
	{
		STAGE_SELECT,
		SETTING,
		EXIT,
	};

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
	MenuButtonFrameUI(MenuButtonFrameUI::ButtonType buttonType , bool buttonActive);
	// �f�X�g���N�^
	~MenuButtonFrameUI() = default;

	// �X�V����
	void Update();

	// ����������
	void Initialize(ObjectID objectID, const bool& active) override;
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


	void SetIsButtonActive(bool buttonActive);

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

	// �{�^���^�C�v
	ButtonType m_buttonType;
	// �{�^���A�N�e�B�u
	bool m_isButtonActive;

	// �{�^����Rect�̐ݒ�l
	DirectX::SimpleMath::Vector4 m_rect;

	// �t���[���@���D
	// Image
	std::unique_ptr<Image> m_image;
	// �}�e���A��
	std::unique_ptr<IMaterial> m_material;

	// �t���[���@���D�j��
	// Image
	std::unique_ptr<Image> m_image2;
	// �}�e���A��
	std::unique_ptr<IMaterial> m_material2;
};
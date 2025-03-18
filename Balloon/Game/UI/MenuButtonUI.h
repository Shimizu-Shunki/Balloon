#pragma once
#include "Interface/IObject.h"

class IObject;
class Transform;
class Image;
class IMaterial;

class MenuButtonUI : public IObject
{
private:
	static const float STAGE_SELECT_WIDTH;
	static const float SETTING_WIDTH;
	static const float EXIT_WIDTH;

	static const float BUTTON_HEIGHT;
	

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
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// Transform�̎擾
	Transform* GetTransform() const override { return m_transform.get(); }
	// �I�u�W�F�N�g��ID���擾����
	IObject::ObjectID GetObjectID() const override { return m_objectId; }


public:

	// �R���X�g���N�^
	MenuButtonUI(MenuButtonUI::ButtonType buttonType , bool buttonActive);
	// �f�X�g���N�^
	~MenuButtonUI() = default;

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

	// �Փ˂���������
	void OnCollisionEnter(IObject* object) override { (void)object; };
	// �Փ˂��Ă��鎞
	void OnCollisionStay(IObject* object) override { (void)object; };
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ�
	void OnCollisionExit(IObject* object) override { (void)object; };

	// �Փ˂����������i�g���K�[�j
	void OnTriggerEnter(IObject* object) override { (void)object; };
	// �Փ˂��Ă��鎞�i�g���K�[�j
	void OnTriggerStay(IObject* object) override { (void)object; };
	// �I�u�W�F�N�g�Ɨ��ꂽ�Ƃ��i�g���K�[�j
	void OnTriggerExit(IObject* object) override { (void)object; };


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

	// Image
	std::unique_ptr<Image> m_image;
	// �}�e���A��
	std::unique_ptr<IMaterial> m_material;
};
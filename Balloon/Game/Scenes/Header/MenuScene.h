#pragma once
#include "Interface/IScene.h"

class CommonResources;
class InputManager;

class MenuScene : public IScene
{
public:
	// �R���X�g���N�^
	MenuScene();
	// �f�X�g���N�^
	~MenuScene();

public:
	// ����������
	void Initialize() override;
	// �X�^�[�g����
	void Start()  override;
	// �X�V����
	void Update() override;
	// �`�揈��
	void Render() override;
	// �I������
	void Finalize() override;

private:
	template <typename T>
	T* SearchObject(IObject::ObjectID objectID)
	{
		for (const auto& object : m_objects)
		{
			if (object->GetObjectID() == objectID)
			{
				T* castedObject = dynamic_cast<T*>(object.get());
				if (!castedObject)
				{
					throw std::runtime_error("dynamic_cast failed: Invalid type conversion");
				}
				return castedObject;
			}
		}

		return nullptr;
	}


	template <typename T, typename... Args>
	T* Attach(
		IObject::ObjectID objectId,
		bool isActive,
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale,
		Args&&... args)
	{
		// �I�u�W�F�N�g�̍쐬
		std::unique_ptr<IObject> object = std::make_unique<T>(std::forward<Args>(args)...);
		// �I�u�W�F�N�g�̏�����
		object->Initialize(objectId, isActive);
		// Transform�̏�����
		object->InitialTransform(position, rotation, scale);

		IObject* returnObject = object.get();
		// �I�u�W�F�N�g�̒ǉ�
		m_objects.push_back(std::move(object));

		return dynamic_cast<T*>(returnObject);
	}

	void SelectButton();

private:

	// ���L���\�[�X
	CommonResources* m_commonResources;

	InputManager* m_inputManager;

	// UI�I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_objects;

	// ���݂̃{�^��
	int m_buttonIndex;
};
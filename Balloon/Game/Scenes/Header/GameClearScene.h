#pragma once
#include "Interface/IScene.h"
#include "Interface/IObject.h"


class CommonResources;
class Fade;
class IObject;

class GameClearScene : public IScene
{
public:
	// �R���X�g���N�^
	GameClearScene();
	// �f�X�g���N�^
	~GameClearScene();

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
	// �V�[���̃X�e�[�g��ύX����
	void ChangeState(IState* newState) override;
	// �����蔻�胁�b�Z�[�W���󂯎��
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

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

	void CreateCamera();

private:
	// ���L���\�[�X
	CommonResources* m_commonResources;

	// �t�F�[�h����
	std::unique_ptr<Fade> m_fade;

	// �I�u�W�F�N�g
	std::vector<std::unique_ptr<IObject>> m_objects;

	// ���݂̃X�e�[�g
	IState* m_currentState;
	// �e�X�e�[�g
	std::unique_ptr<IState> m_fadeInState;
	std::unique_ptr<IState> m_fadeOutState;
	std::unique_ptr<IState> m_gameClearMainState;
};
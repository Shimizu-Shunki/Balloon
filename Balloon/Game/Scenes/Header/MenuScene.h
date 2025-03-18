#pragma once
#include "Interface/IScene.h"

class CommonResources;
class InputManager;

class MenuScene : public IScene
{
public:
	// コンストラクタ
	MenuScene();
	// デストラクタ
	~MenuScene();

public:
	// 初期化処理
	void Initialize() override;
	// スタート処理
	void Start()  override;
	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// 終了処理
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
		// オブジェクトの作成
		std::unique_ptr<IObject> object = std::make_unique<T>(std::forward<Args>(args)...);
		// オブジェクトの初期化
		object->Initialize(objectId, isActive);
		// Transformの初期化
		object->InitialTransform(position, rotation, scale);

		IObject* returnObject = object.get();
		// オブジェクトの追加
		m_objects.push_back(std::move(object));

		return dynamic_cast<T*>(returnObject);
	}

	void SelectButton();

private:

	// 共有リソース
	CommonResources* m_commonResources;

	InputManager* m_inputManager;

	// UIオブジェクト
	std::vector<std::unique_ptr<IObject>> m_objects;

	// 現在のボタン
	int m_buttonIndex;
};
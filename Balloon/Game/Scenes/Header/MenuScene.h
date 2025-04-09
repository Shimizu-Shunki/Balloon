// ============================================
// 
// ファイル名: MenuScene.h
// 概要: MenuScene.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IScene.h"

class CommonResources;
class InputManager;
class Fade;

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
	// シーンのステートを変更する
	void ChangeState(IState* newState) override;
	// 当たり判定メッセージを受け取る
	void OnSceneMessegeAccepted(Message::SceneMessageID messageID) override;

private:
	// オブジェクトを検索する
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

	// オブジェクトを追加する
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

	// ステートコントローラーの作成
	void CreateStateStateController();

private:

	// 共有リソース
	CommonResources* m_commonResources;

	InputManager* m_inputManager;

	// UIオブジェクト
	std::vector<std::unique_ptr<IObject>> m_objects;

	// フェード
	std::unique_ptr<Fade> m_fade;
	
	// 現在のステート
	IState* m_currentState;
	// 各ステート
	std::unique_ptr<IState> m_fadeInState;
	std::unique_ptr<IState> m_fadeOutState;
	std::unique_ptr<IState> m_menuMainState;

	// 現在のボタン
	int m_buttonIndex;
};
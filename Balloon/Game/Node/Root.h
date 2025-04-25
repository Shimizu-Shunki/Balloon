#pragma once
#include "Interface/IObject.h"
#include "Game/Node/NodeBase.h"
#include "Interface/IComposite.h"

class Transform;

class Root : public NodeBase, public IComposite
{
public:
	// オブジェクトのアクティブ設定
	void SetIsActive(const bool& isActive) override { m_isActive = isActive; }
	// オブジェクトのアクティブ状態を取得
	bool GetIsActive() const override { return m_isActive; }

	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectID; }
	// Transformを取得する
	Transform* GetTransform() const override { return m_transform.get(); }

public:

	// コンストラクタ
	Root(IObject* parent, IObject::ObjectID objectID,
		const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Quaternion& rotation,
		const DirectX::SimpleMath::Vector3& scale
	);
	// デストラクタ
	~Root();

public:

	// 初期化する
	void Initialize() override;
	// 更新する
	void Update(const float& elapsedTime) override;
	// 後処理を行う
	void Finalize() override;

	// オブジェクトをアタッチする
	void Attach(std::unique_ptr<IObject> node) override;
	// オブジェクトを削除する
	void Detach(std::unique_ptr<IObject> node) override;

	// メッセージを取得する
	void OnMessegeAccepted(Message::MessageID messageID) override;
	// キーが押下げられたら通知する
	void OnKeyPressed(KeyType type , const DirectX::Keyboard::Keys& key) override;

private:

	// オブジェクトID
	IObject::ObjectID m_objectID;
	// 状態
	bool m_isActive;
	// Transform
	std::unique_ptr<Transform> m_transform;
};
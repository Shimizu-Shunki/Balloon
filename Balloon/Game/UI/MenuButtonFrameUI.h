// ============================================
// 
// ファイル名: MenuButtonFrameUI.h
// 概要: MenuButtonFrameUI.cppのヘッダーファイル
// 
// 製作者 : 清水駿希
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
	// ボタンの種類
	enum class ButtonType
	{
		STAGE_SELECT,
		SETTING,
		EXIT,
	};

public:
	// オブジェクトアクティブを取得する
	bool GetIsActive() const  override { return m_isActive; }
	// オブジェクトアクティブを設定する
	void SetIsActive(bool isActive) {
		m_isActive = isActive;
		m_image->SetIsActive(isActive);
	}
	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	// オブジェクトのIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }


public:

	// コンストラクタ
	MenuButtonFrameUI(MenuButtonFrameUI::ButtonType buttonType , bool buttonActive);
	// デストラクタ
	~MenuButtonFrameUI() = default;

	// 更新処理
	void Update();

	// 初期化処理
	void Initialize(ObjectID objectID, const bool& active) override;
	// Transformの初期化
	void InitialTransform(
		DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Quaternion rotation,
		DirectX::SimpleMath::Vector3 scale
	) override;
	// 終了処理
	void Finalize() override;

	// オブジェクトメッセージを受け取る
	void OnObjectMessegeAccepted(Message::ObjectMessageID messageID) override;
	// 当たり判定メッセージを受け取る
	void OnCollisionMessegeAccepted(Message::CollisionMessageID messageID, IObject* sender) override;


	void SetIsButtonActive(bool buttonActive);

private:

	// マテリアルの初期化処理
	void InitialMaterial(int width, int height);

private:

	// アクティブ設定
	bool m_isActive;
	// オブジェクトID
	IObject::ObjectID m_objectId;
	// トランスフォーム
	std::unique_ptr<Transform> m_transform;

	// ボタンタイプ
	ButtonType m_buttonType;
	// ボタンアクティブ
	bool m_isButtonActive;

	// ボタンのRectの設定値
	DirectX::SimpleMath::Vector4 m_rect;

	// フレーム　風船
	// Image
	std::unique_ptr<Image> m_image;
	// マテリアル
	std::unique_ptr<IMaterial> m_material;

	// フレーム　風船破裂
	// Image
	std::unique_ptr<Image> m_image2;
	// マテリアル
	std::unique_ptr<IMaterial> m_material2;
};
#pragma once
#include "Interface/IObject.h"

class IObject;
class Transform;
class Image;
class IMaterial;

class Text : public IObject
{
public:
	// オブジェクトアクティブを取得する
	bool GetIsActive() const  override { return m_isActive; }
	// オブジェクトアクティブを設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	// オブジェクトのIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }


public:

	// コンストラクタ
	Text();
	// デストラクタ
	~Text() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();

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

	// Image
	std::unique_ptr<Image> m_image;
	// マテリアル
	std::unique_ptr<IMaterial> m_material;
};
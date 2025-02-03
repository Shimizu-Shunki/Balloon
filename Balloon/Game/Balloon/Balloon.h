#pragma once

#include "Interface/IComposite.h"
#include "Interface/ILeaf.h"
#include "Interface/IObject.h"
#include "Framework/Graphics.h"

#include <Interface/ICamera.h>

class CommonResources;
class IComposite;


// 風船　子オブジェクトはなし
class Balloon : public ILeaf
{
public:
	// オブジェクトがアクティブかどうかを取得する
	bool GetIsActive() const override { return m_isActive; }
	// オブジェクトがアクティブかどうかを設定する
	void SetIsActive(bool isActive) { m_isActive = isActive; }
	// オブジェクトIDを取得する
	IObject::ObjectID GetObjectID() const override { return m_objectId; }
	// モデルを取得する
	DirectX::Model* GetModel() const override { return m_model; }

	// Transformの取得
	Transform* GetTransform() const override { return m_transform.get(); }
	// 物理的数値
	// 当たり判定

public:
	// コンストラクタ
	// カメラの情報、親のオブジェクト
	Balloon(IObject* parent , float angle);
	// デストラクタ
	~Balloon();

public:
	// 初期化処理
	void Initialize(ObjectID objectID, const bool& active) override;
	// 更新処理
	void Update() override;
	// 終了処理
	void Finalize() override;

	// 衝突があった時
	void OnCollisionEnter(IObject* object) override;
	// 衝突している時
	void OnCollisionStay(IObject* object) override;
	// オブジェクトと離れたとき
	void OnCollisionExit(IObject* object) override;

	// 衝突があった時（トリガー）
	void OnTriggerEnter(IObject* object) override;
	// 衝突している時（トリガー）
	void OnTriggerStay(IObject* object) override;
	// オブジェクトと離れたとき（トリガー）
	void OnTriggerExit(IObject* object) override;

private:
	// 共有リソース
	CommonResources* m_commonResources;
	// 親のオブジェクト
	IObject* m_parent;
	
	// オブジェクトID
	IObject::ObjectID m_objectId;
	// オブジェクトアクティブ
	bool m_isActive;

	// Transform 全てのオブジェクトが持つ
	std::unique_ptr<Transform> m_transform;

	// 物理的数値

	// 3Dモデル
	DirectX::Model* m_model;

	// 回転角
	float m_angle;
};

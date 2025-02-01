#pragma once

#include "Interface/IComposite.h"
#include "Interface/IObject.h"
#include "Framework/Graphics.h"

#include <Interface/ICamera.h>

class CommonResources;
class IComposite;



class Player : public IComposite
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
	Player(ICamera* camera, IObject* parent);
	// デストラクタ
	~Player();

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

	// 部品を追加する
	void Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId) override;
	// 部品を削除する
	void Detach(std::unique_ptr<IObject> turretPart) override;


public:

	void BalloonDetach();

private:
	// 移動処理
	DirectX::SimpleMath::Vector3 GetMovementDirection(const DirectX::SimpleMath::Quaternion& angle);
	// ジャンプ処理
	//void Jump(const float& elapsedTime);
	// ジャンプ回数回復処理
	void RecoverJump();


private:
	// 共有リソース
	CommonResources* m_commonResources;
	// 親のオブジェクト
	IObject* m_parent;
	// 子供のオブジェクト
	std::vector<std::unique_ptr<IObject>> m_childs;

	// オブジェクトID
	IObject::ObjectID m_objectId;
	// オブジェクトアクティブ
	bool m_isActive;

	// Transform 全てのオブジェクトが持つ
	std::unique_ptr<Transform> m_transform;

	// 物理的数値


	// カメラ
	ICamera* m_camera;

	// 3Dモデル
	DirectX::Model* m_model;
	// 風船の数
	int m_balloonIndex;
};

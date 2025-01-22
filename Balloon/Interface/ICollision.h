#pragma once
#include "Interface/IComponent.h"
#include "Game/Collider/Collider.h"

class IComponent;
class Collider;

class ICollision
{
	/*・当たり判定　
		上下左右の当たり判定
		トリガーなし
		当たった時（相手のオブジェクト）
		当たっている時（相手のオブジェクト）
		離れた瞬間（相手のオブジェクト）
		詳細な当たり判定（相手のオブジェクト、どの方向に当たっているか）
		トリガーあり
		当たった時（相手のオブジェクト）
		当たっている時（相手のオブジェクト）*/

public:
	// 当たり判定を取得する
	virtual const std::vector<std::unique_ptr<Collider>>& GetColliders() const = 0;

	// 衝突があった時
	virtual void OnCollisionEnter(IComponent* object) {};
	// 衝突している時
	virtual void OnCollisionStay(IComponent* object) {};
	// オブジェクトと離れたとき
	virtual void OnCollisionExit(IComponent* object) {};

	// 衝突があった時（トリガー）
	virtual void OnTriggerEnter(IComponent* object) {};
	// 衝突している時（トリガー）
	virtual void OnTriggerStay(IComponent* object) {};
	// オブジェクトと離れたとき（トリガー）
	virtual void OnTriggerExit(IComponent* object) {};
};

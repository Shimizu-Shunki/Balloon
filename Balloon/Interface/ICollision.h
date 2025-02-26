#pragma once
#include "Interface/IObject.h"

class IObject;

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
	// 衝突があった時
	virtual void OnCollisionEnter(IObject* object) = 0;
	// 衝突している時
	virtual void OnCollisionStay(IObject* object) = 0;
	// オブジェクトと離れたとき
	virtual void OnCollisionExit(IObject* object) = 0;

	// 衝突があった時（トリガー）
	virtual void OnTriggerEnter(IObject* object) = 0;
	// 衝突している時（トリガー）
	virtual void OnTriggerStay(IObject* object) = 0;
	// オブジェクトと離れたとき（トリガー）
	virtual void OnTriggerExit(IObject* object) = 0;
};

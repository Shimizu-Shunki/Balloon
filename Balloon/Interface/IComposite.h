// ============================================
// 
// ファイル名: IComposite.h
// 概要: 複数オブジェクトの構成・分離を定義する（インターフェース）
// 
// 製作者 : 清水駿希
// 
// ============================================
#pragma once
#include "Interface/IObject.h"
#include <SimpleMath.h>


class IComposite : public IObject
{
public:
	// オブジェクトを追加する
	virtual void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) = 0;
	// オブジェクトを削除する
	virtual void Detach(std::unique_ptr<IObject> turretPart)  = 0;
};


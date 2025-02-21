#pragma once
#ifndef ICOMPOSITE_DEFINED
#define ICOMPOSITE_DEFINED
#include "Interface/IObject.h"
#include <SimpleMath.h>


class IComposite : public IObject
{
public:
	// �C�����i��ǉ�����
	virtual void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) = 0;
	// �C�����i���폜����
	virtual void Detach(std::unique_ptr<IObject> turretPart)  = 0;
};

#endif		// ICOMPOSITE_DEFINED

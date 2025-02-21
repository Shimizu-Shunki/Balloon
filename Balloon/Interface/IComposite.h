#pragma once
#ifndef ICOMPOSITE_DEFINED
#define ICOMPOSITE_DEFINED
#include "Interface/IObject.h"
#include <SimpleMath.h>


class IComposite : public IObject
{
public:
	// –C“ƒ•”•i‚ğ’Ç‰Á‚·‚é
	virtual void Attach(std::unique_ptr<IObject> object, IObject::ObjectID objectId,
		DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero,
		DirectX::SimpleMath::Quaternion rotation = DirectX::SimpleMath::Quaternion::Identity,
		DirectX::SimpleMath::Vector3 scale = DirectX::SimpleMath::Vector3::One
	) = 0;
	// –C“ƒ•”•i‚ğíœ‚·‚é
	virtual void Detach(std::unique_ptr<IObject> turretPart)  = 0;
};

#endif		// ICOMPOSITE_DEFINED

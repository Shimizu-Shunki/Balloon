#pragma once
#ifndef ICOMPOSITE_DEFINED
#define ICOMPOSITE_DEFINED
#include "Interface/IObject.h"

class IComposite : public IObject
{
public:
	// �C�����i��ǉ�����
	virtual void Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId) = 0;
	// �C�����i���폜����
	virtual void Detach(std::unique_ptr<IObject> turretPart)  = 0;
};

#endif		// ICOMPOSITE_DEFINED

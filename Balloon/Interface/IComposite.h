#pragma once
#ifndef ICOMPOSITE_DEFINED
#define ICOMPOSITE_DEFINED
#include "Interface/IObject.h"

class IComposite : public IObject
{
public:
	// –C“ƒ•”•i‚ğ’Ç‰Á‚·‚é
	virtual void Attach(std::unique_ptr<IObject> turretParts, IObject::ObjectID objectId) = 0;
	// –C“ƒ•”•i‚ğíœ‚·‚é
	virtual void Detach(std::unique_ptr<IObject> turretPart)  = 0;
};

#endif		// ICOMPOSITE_DEFINED

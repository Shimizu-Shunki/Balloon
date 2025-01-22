#pragma once
#ifndef ICOMPOSITE_DEFINED
#define ICOMPOSITE_DEFINED
#include "Interface/IComponent.h"

class IComposite : public IComponent
{
public:
	// –C“ƒ•”•i‚ğ’Ç‰Á‚·‚é
	virtual void Attach(std::unique_ptr<IComponent> turretParts) = 0;
	// –C“ƒ•”•i‚ğíœ‚·‚é
	virtual void Detach(std::unique_ptr<IComponent> turretPart)  = 0;
};

#endif		// ICOMPOSITE_DEFINED

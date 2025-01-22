#pragma once
#ifndef ICOMPOSITE_DEFINED
#define ICOMPOSITE_DEFINED
#include "Interface/IComponent.h"

class IComposite : public IComponent
{
public:
	// �C�����i��ǉ�����
	virtual void Attach(std::unique_ptr<IComponent> turretParts) = 0;
	// �C�����i���폜����
	virtual void Detach(std::unique_ptr<IComponent> turretPart)  = 0;
};

#endif		// ICOMPOSITE_DEFINED

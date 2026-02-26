#ifndef STATUSEFFECTS_H
#define STATUSEFFECTS_H

#include "Entities.h"
#include <string>
#include <iostream>

namespace status
{
	class StatusEffect
	{
	public:
		std::string Name;
		int CurrentStacks;
		int MaxStacks;
		virtual void UpdateStatusEffect(entities::Entity entityIn) { return; };
	};
}

#endif
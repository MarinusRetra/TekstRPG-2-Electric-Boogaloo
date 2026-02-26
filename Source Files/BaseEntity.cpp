#include "Header Files/BaseEntity.h"
#include "Header Files/StatusEffects.h"
#include <iostream>
#include <random>
#include <ctime>

namespace base_entity
{
	template<typename Effect>
	void BaseEntity::RollGetStatusEffect(Effect statusEffectIn, double statusEffectChanceIn)
	{
		double val = (double)rand() / RAND_MAX;

		if (val < statusEffectChanceIn)
		{
			for each(status::StatusEffect CurrentStatusEffect in StatusEffectsVulnerable)
			{
				if (CurrentStatusEffect.Name == statusEffectIn.Name)
				{
					CurrentStatusEffect.CurrentStacks++;
					return;
				}
			}
		}
	}

	template<typename Effect>
	Effect BaseEntity::GetVulnerableStatusEffect(std::string nameIn)
	{
		for each(status::StatusEffect CurrentStatusEffect in StatusEffectsVulnerable)
		{
			if (CurrentStatusEffect.Name == nameIn)
			{
				return CurrentStatusEffect;
			}
		}
	}
	

	/// <summary>
	/// Keeps a list of every status this entity can get.
	/// </summary>
	status::StatusEffect StatusEffectsVulnerable[MAX_STATUS_EFFECTS];
}
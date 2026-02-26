#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <string>

namespace base_entity
{
	const int MAX_STATUS_EFFECTS = 10;

	class BaseEntity
	{
	public:
		virtual void TakeDamage(int damageIn)
		{
			Health -= damageIn;
		}
		template<typename Effect>
		void RollGetStatusEffect(Effect statusEffectIn, double statusEffectChanceIn);

		template<typename Effect>
		Effect GetVulnerableStatusEffect(std::string nameIn);

		std::string Name = "";
		int Health = 0;
		int Attack = 0;
		int MAttack = 0;
		int Agility = 0;
		int Defense = 0;
		int MDefense = 0;
		int MaxHealth = 0;
	};
}

#endif
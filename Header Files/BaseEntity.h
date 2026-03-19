#ifndef BASEENTITY_H
#define BASEENTITY_H

#include <string>
#include <cstdint>
#include <random>
#include <ctime>

namespace base_entity
{

	class BaseEntity
	{

	public:
		static const int MAX_STATUS_EFFECTS = 10;

		BaseEntity(std::string _nameIn, int _attackIn, int _mAttackIn, int _agilityIn, int _defenseIn, int _mDefenseIn, int _maxHealtIn);
		~BaseEntity(); // Might put the drop loot functionality here.
		virtual void TakeDamage(int damageIn)
		{
			if (damageIn > Health)
			{
				Health = 0;
			}
			else
			{
				Health -= damageIn;
			}
		}
		template<typename Effect>
		void RollGetStatusEffect(Effect statusEffectIn, double statusEffectChanceIn);

		template<typename Effect>
		Effect GetVulnerableStatusEffect(std::string nameIn);

		std::string Name;     // 1
		int   Health;		  
		int   Attack;		  // 2
		int   MAttack;	      // 3
		int   Agility;	      // 4
		int   Defense;	      // 5
		int   MDefense;	      // 6
		int   MaxHealth;	  // 7
	};
}

#endif
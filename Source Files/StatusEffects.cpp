#include "Header Files/StatusEffects.h"

namespace status
{
	/// <summary>
	/// Every stack of poison deals 5 percent of the target's MaxHealth every time it updates.
	/// </summary>
	class Poison : public StatusEffect
	{
	public:
		void UpdateStatusEffect(entities::Entity entityIn) override
		{
			entityIn.TakeDamage(entityIn.MaxHealth / 100 * (5 * CurrentStacks));
			std::cout << entityIn.Name + "Took " << entityIn.MaxHealth / 100 * (5 * CurrentStacks) + "Poison damage!" << std::endl;
		}
	};
}
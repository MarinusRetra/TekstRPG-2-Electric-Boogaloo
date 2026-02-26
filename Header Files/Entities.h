#ifndef ENTITY_H
#define ENTITY_H
#include "BaseEntity.h"
#include <REXSpeeder.h>


/// <summary>
/// This namespace includes OverWorldEntity, CombatEntity, InteractableEntities.
/// </summary>
namespace entities
{
	class Entity : public base_entity::BaseEntity
	{

	};

	class OverWorldEntity : public Entity
	{
	public:
		//OverWorldEntity();
		//~OverWorldEntity();

		//CombatEntity CombatEntity;
		int PositionX;
		int PositionY;
		xp::RexTile Character; // Might need to change to an unint32 later.
		xp::RexTile CurrentFacingTile;
	};

	class CombatEntity : public Entity
	{

	};

	class InteractableEntity
	{

	};





}
#endif
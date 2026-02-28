#ifndef ENTITY_H
#define ENTITY_H
#include "BaseEntity.h"
#include <REXSpeeder.h>
#include <string>
#include <vector>
#include <utility>

/// <summary>
/// This namespace includes OverWorldEntity, CombatEntity, InteractableEntities.
/// </summary>
namespace entities
{
	class Entity : public base_entity::BaseEntity
	{
	public:
		Entity(xp::RexTile _characterIn, std::string _nameIn, int _attackIn, int _mAttackIn, int _agilityIn, int _defenseIn, int _mDefenseIn, int _maxHealtIn);

		std::vector<std::pair<int, int>> SpawnPositions = { {0,0} };

		int PositionX = 0;
		int PositionY = 0;

		xp::RexTile CurrentFacingTile = { 0, 0, 0, 0, 255, 0, 255 }; // TODO: Change this later to use my tile class instead for interactions and such. 
		xp::RexTile Character = { 30, 255, 255, 255, 255, 255, 255 };
	};

	class OverWorldEntity : public Entity
	{
	public:
		//OverWorldEntity();
		//~OverWorldEntity();

		//CombatEntity CombatEntity;
	};

	class CombatEntity : public Entity
	{

	};

	class InteractableEntity
	{

	};





}
#endif
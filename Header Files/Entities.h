#ifndef ENTITY_H
#define ENTITY_H

#include "BaseEntity.h"
#include "EntitySprites.h"

#include <string>
#include <vector>
#include <utility>
#include <REXSpeeder.h>

/// <summary>
/// This namespace includes OverWorldEntity, CombatEntity, InteractableEntities.
/// </summary>
namespace entities
{

	class Entity : public base_entity::BaseEntity
	{
	public:
		Entity(xp::RexTile _characterIn, std::string _nameIn, int _attackIn, int _mAttackIn, int _agilityIn, int _defenseIn, int _mDefenseIn, int _maxHealtIn, sprites::EntityCharacters _spriteDataIn, int _spawnPosXIn,int _spawnPosYIn);

		game_utility::Vector2<int> CurrentFacingTile = { SpawnPosition.X, SpawnPosition.Y};

		sprites::EntityCharacters SpriteData;

		game_utility::Vector2<int> CurrentPosition = {0,0};
		game_utility::Vector2<int> PreviousPosition = {0,0};
		game_utility::Vector2<int> SpawnPosition = {0,0};
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
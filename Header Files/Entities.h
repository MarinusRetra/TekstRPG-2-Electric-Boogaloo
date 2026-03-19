#ifndef ENTITY_H
#define ENTITY_H

#include "BaseEntity.h"
#include "EntitySprites.h"
#include "REXSpeeder.h"

#include <string>
#include <vector>
#include <cstdint>

/// <summary>
/// This namespace includes OverWorldEntity, CombatEntity, uint8_teractableEntities.
/// </summary>
namespace entities
{
	class Entity : public base_entity::BaseEntity
	{
	public:     
		Entity(std::string _nameIn, int _attackIn, int _mAttackIn, int _agilityIn, int _defenseIn, int _mDefenseIn, int _maxHealtIn, sprites::EntityCharacters _spriteDataIn, int _spawnPosXIn, int _spawnPosYIn);
		//TODO: Update these to the new coordinate system.
		sprites::EntityCharacters SpriteData;
		game_utility::Vector2<int> SpawnPosition = { 0,0 }; 
		game_utility::Vector2<int> PreviousPosition = { 0,0 };
		game_utility::Vector2<int> CurrentPosition = { 0,0 };
		game_utility::Vector2<int> CurrentFacingTile = { 0,0 };

		virtual void Update() {};
		virtual void interact() {};
	};
}
#endif
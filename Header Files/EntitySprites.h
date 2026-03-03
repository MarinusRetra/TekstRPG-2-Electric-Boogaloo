#ifndef ENTITYSPRITES_H
#define ENTITYSPRITES_H

#include "GameUtility.h"
#include <REXSpeeder.h>
#include <string>
#include <map>

namespace sprites
{
	struct EntityCharacters
	{
		xp::RexTile* CombatCharacter;
		xp::RexTile* OverworldCharacterDown;
		xp::RexTile* OverWorldCharacterRight;
		xp::RexTile* OverWorldCharacterLeft;
		xp::RexTile* OverWorldCharacterUp;

		std::map<game_utility::Vector2<int>, xp::RexTile*> CharacterSprites;

		EntityCharacters(xp::RexTile* combat, xp::RexTile* down, xp::RexTile* right, xp::RexTile* left, xp::RexTile* up);
	};

	extern xp::RexImage CharacterSheet;

	extern EntityCharacters TemplatePlayer;

}
#endif
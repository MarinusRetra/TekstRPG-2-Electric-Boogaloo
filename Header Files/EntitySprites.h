#ifndef ENTITYSPRITES_H
#define ENTITYSPRITES_H

#include "GameUtility.h"
#include <REXSpeeder.h>
#include <BearLibTerminal.h>
#include <string>
#include <map>

struct CharacterSprite
{
	uint32_t sprite;
	color_t color;

	CharacterSprite(xp::RexTile _tileIn)
	{
		sprite = game_utility::ConvertTileToTileIndex(_tileIn);
		color = color_from_argb(255, _tileIn.fore_red, _tileIn.fore_green, _tileIn.fore_blue);
	}

	CharacterSprite()
	{
		sprite = 0;
		color = 0;
	}
};

namespace sprites
{
	struct EntityCharacters
	{
		CharacterSprite CombatCharacter;
		CharacterSprite OverworldCharacterDown;
		CharacterSprite OverWorldCharacterRight;
		CharacterSprite OverWorldCharacterLeft;
		CharacterSprite OverWorldCharacterUp;

	    std::map<game_utility::Vector2<int8_t>, CharacterSprite> CharacterSprites;

		EntityCharacters(CharacterSprite combat, CharacterSprite down, CharacterSprite right, CharacterSprite left, CharacterSprite up);
	};

	extern xp::RexImage CharacterSheet;

	extern EntityCharacters TemplatePlayer;

}
#endif
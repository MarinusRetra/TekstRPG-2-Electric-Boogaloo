#include "Header Files/EntitySprites.h"

namespace sprites
{
	xp::RexImage CharacterSheet = xp::RexImage("Maps/CharacterSheet.xp");

	EntityCharacters TemplatePlayer
	{
		CharacterSprite(*CharacterSheet.getTile(0, 0, 0)), //CombatCharacter
		CharacterSprite(*CharacterSheet.getTile(0, 0, 0)), //CharacterDown
		CharacterSprite(*CharacterSheet.getTile(0, 1, 0)), //CharacterRight
		CharacterSprite(*CharacterSheet.getTile(0, 2, 0)), //Characterleft
		CharacterSprite(*CharacterSheet.getTile(0, 3, 0)), //CharacterUp
	};

	//-1 is Left
	//+1 is Right
	//-1 is Up
	//+1 is Down
	
	EntityCharacters::EntityCharacters(CharacterSprite combat, CharacterSprite down, CharacterSprite right, CharacterSprite left, CharacterSprite up) : CombatCharacter(combat), OverworldCharacterDown(down), OverWorldCharacterRight(right), OverWorldCharacterLeft(left), OverWorldCharacterUp(up)
	{
		CharacterSprites[{0,  1}] = OverworldCharacterDown;
		CharacterSprites[{-1, 0}] = OverWorldCharacterLeft;
		CharacterSprites[{1,  0 }] = OverWorldCharacterRight;
		CharacterSprites[{0,  -1}] = OverWorldCharacterUp;
	}

}
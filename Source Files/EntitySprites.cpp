#include "Header Files/EntitySprites.h"

namespace sprites
{
	xp::RexImage CharacterSheet = xp::RexImage("Maps/CharacterSheet.xp");


	EntityCharacters TemplatePlayer
	{
		CharacterSheet.getTile(0, 0, 0), //CombatCharacter
		CharacterSheet.getTile(0, 0, 0), //CharacterDown
		CharacterSheet.getTile(0, 1, 0), //CharacterRight
		CharacterSheet.getTile(0, 2, 0), //Characterleft
		CharacterSheet.getTile(0, 3, 0), //CharacterUp
	};

	EntityCharacters::EntityCharacters(xp::RexTile* combat, xp::RexTile* down, xp::RexTile* right, xp::RexTile* left, xp::RexTile* up) : CombatCharacter(combat), OverworldCharacterDown(down), OverWorldCharacterRight(right), OverWorldCharacterLeft(left), OverWorldCharacterUp(up)
	{
		CharacterSprites[{0, 1}] = OverworldCharacterDown;
		CharacterSprites[{-1, 0}] = OverWorldCharacterLeft;
		CharacterSprites[{1, 0}] = OverWorldCharacterRight;
		CharacterSprites[{0, -1}] = OverWorldCharacterUp;
	}
	//-1 is Left
	//+1 is Right
	
	//-1 is Up
	//+1 is Down
}
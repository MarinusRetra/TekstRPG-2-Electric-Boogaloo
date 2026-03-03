#include "Header Files/Entities.h"

namespace entities
{
	Entity::Entity(xp::RexTile _characterIn, std::string _nameIn, int _attackIn, int _mAttackIn, int _agilityIn, int _defenseIn, int _mDefenseIn, int _maxHealtIn, sprites::EntityCharacters _spriteDataIn, int _spawnPosXIn, int _spawnPosYIn) : BaseEntity(_nameIn, _attackIn, _mAttackIn, _agilityIn, _defenseIn, _mDefenseIn, _maxHealtIn), SpriteData(_spriteDataIn)
	{
		SpawnPosition.X = _spawnPosXIn;
		SpawnPosition.Y = _spawnPosYIn;
	}
}
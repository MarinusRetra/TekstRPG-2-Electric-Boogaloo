#include "Header Files/Entities.h"


namespace entities
{
	Entity::Entity(xp::RexTile _characterIn, std::string _nameIn, int _attackIn, int _mAttackIn, int _agilityIn, int _defenseIn, int _mDefenseIn, int _maxHealtIn) : BaseEntity(_nameIn, _attackIn, _mAttackIn, _agilityIn, _defenseIn, _mDefenseIn, _maxHealtIn)
	{
		PositionX = SpawnPositions[0].first;
		PositionY = SpawnPositions[0].second;
	}
}
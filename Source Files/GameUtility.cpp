#include "Header Files/GameUtility.h"

namespace game_utility
{
	/// <summary>
	/// Packs 4 uint8 from a RexTile into one uint32 sot that it matches the way .xp files store characters. 
	/// </summary>
	/// <param name="tile"></param>
	/// <returns></returns>
	uint32_t ConvertTileToTileIndex(xp::RexTile tile)
	{
		return static_cast<uint32_t>(tile.character) | // The first 8 bits of the uint32 becomes the tile charachter 0-7
			(static_cast<uint32_t>(tile.__padding[0]) << 8) | // 8-15
			(static_cast<uint32_t>(tile.__padding[1]) << 16) | // 16-23
			(static_cast<uint32_t>(tile.__padding[2]) << 24); //24 - 31
	}
}
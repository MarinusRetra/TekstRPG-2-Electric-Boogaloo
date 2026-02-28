#include "Header Files/GameUtility.h"

namespace game_utility
{
	/// <summary>
	/// Converts a RexTile to a format compatible with my 16x352 font sheet.
	/// </summary>
	/// <param name="tile"></param>
	/// <returns></returns>
	uint32_t ConvertTileToUint32(xp::RexTile tile)
	{
		//TODO: Figure out what exactly is happening here a bit better.
		return static_cast<uint32_t>(tile.character) |
			(static_cast<uint32_t>(tile.__padding[0]) << 8) |
			(static_cast<uint32_t>(tile.__padding[1]) << 16) |
			(static_cast<uint32_t>(tile.__padding[2]) << 24);
	}

}
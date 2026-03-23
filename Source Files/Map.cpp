#include "Header Files/Map.h"
#include <chrono>

namespace map_data
{
	Map::Map(xp::RexImage& mapIn)
	{
		auto start = std::chrono::steady_clock::now();
		
		MapWidth = mapIn.getWidth()-1;
		MapHeight = mapIn.getHeight()-1;

		for (int y = 0; y < MapHeight; ++y)
		{
			for (int x = 0; x < MapWidth; ++x)
			{
				uint16_t pos = game_utility::EncodePos(x, y);

				xp::RexTile tileBackGround = *mapIn.getTile(0, x, y);
				xp::RexTile tileCollision = *mapIn.getTile(1, x, y);
				//xp::RexTile tileInteractable = *mapIn.getTile(2, x, y);
				//xp::RexTile tileEntity = *mapIn.getTile(3, x, y);
				//xp::RexTile tileForeground = *mapIn.getTile(4, x, y);
				
				if (!xp::isTransparent(&tileBackGround))
				{
					MapTileBackground tileBG { game_utility::ConvertTileToTileIndex(tileBackGround), color_from_argb(255, tileBackGround.fore_red, tileBackGround.fore_green, tileBackGround.fore_blue) };
					DangerousInsert<MapTileBackground>(MapTileBack, pos, tileBG);
				}

				if (!xp::isTransparent(&tileCollision))
				{
					DangerousInsert<bool>(Collisions, pos, true);
				}

				//if (!xp::isTransparent(&tileInteractable))
				//{
				//	//TODO: Add interactables and define what each interactable does somewhere, like a prefab.
				//
				//	//Interactable interactObj;
				//	//DangerousInsert<Interactable>(MapTileBack, pos, interactObj);
				//}
				//
				//if (!xp::isTransparent(&tileEntity))
				//{
				//	//TODO: Add entities and define each entity somewhere clear so you can use them as prefabs.
				//
				//	//entities::Entity entity ;
				//	//DangerousInsert<MapTileBackground>(MapTileBack, pos, tileBG);
				//}
				//
				//if (!xp::isTransparent(&tileForeground))
				//{
				//	MapTileForeGround tileFG{ game_utility::ConvertTileToTileIndex(tileForeground), color_from_argb(255, tileForeground.fore_red, tileForeground.fore_green, tileForeground.fore_blue) };
				//	DangerousInsert<MapTileForeGround>(MapTileFore, pos, tileFG);
				//}

			}
		}
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		std::cout << "Map load time: " << duration << " microseconds\n";
	}
}
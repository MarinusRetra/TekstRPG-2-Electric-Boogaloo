#ifndef MAP_H
#define MAP_H

#include <string>

namespace world
{
	struct Map
	{
		int level;
		int Height;
		int Width;
		std::string color;
		std::string MapLayout;
		//OverwordlEnemy possibleEnemies[];
		//Interactable possibleInteractables[];
	};

	const int NUM_LAYERS = 10;

	class World
	{
	public:
		Map MapLayers[NUM_LAYERS];
		/// <summary>
		/// This will generate a map object for every layer ingame.
		/// </summary>
		void GenerateMapLayers();
	};
	extern World CurrentWorldInstance;
}


#endif
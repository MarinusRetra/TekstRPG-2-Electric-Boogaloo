#include "Header Files/Map.h"

namespace world
{

	World CurrentWorldInstance;

	void World::GenerateMapLayers()
	{
		for (int i = 0; i < NUM_LAYERS; i++)
		{
			// Set the maps for everything
		}
	}

	//0. Design a couple rooms
	//1. Make a set of rooms
	//2. Generate those rooms together in one string without them overlapping
	//3. Every room will have a door point which will be used as startpoint and target point for the pathfinding.
	//4. Connect these rooms together via A* pathfinding (without diagonals)
	//5. Now you have a map
	//6. Populate the map with interactables, npc's and enemies.
	//7. Player movement.
}


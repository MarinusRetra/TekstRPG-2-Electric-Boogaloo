#ifndef MAP_H
#define MAP_H

#include "BearLibTerminal.h"
#include "Entities.h"
#include "GameUtility.h"
#include "REXSpeeder.h"
#include <vector>

namespace map_data
{	
	// These will appear under the player.
	struct MapTileBackground
	{
		uint32_t sprite;
		color_t color;
	};

	//Two structs with the same data types in them is just for clarity nothing else.

	// These will appear over the player.
	struct MapTileForeGround
	{
		uint32_t sprite;
		color_t color;
	};

	struct Interactable
	{
		virtual void Update() {};
		virtual void Interact() {};
	};

	// Stores and organizes map data by reading out an .xp file when the program starts.
	struct Map
	{
		uint8_t MapWidth;
		uint8_t MapHeight;

		std::vector<std::pair<uint16_t, MapTileBackground>> MapTileBack;
		std::vector<std::pair<uint16_t, bool>> Collisions;
		std::vector<std::pair<uint16_t, Interactable>> Interactables;
		std::vector<std::pair<uint16_t, entities::Entity>> Entities;
		std::vector<std::pair<uint16_t, MapTileForeGround>> MapTileFore;
		
		// Returns the first position that is the same size as _posIn or higher.
		template<typename T>
		static typename std::vector<std::pair<uint16_t, T>>::iterator LowerBound(std::vector<std::pair<uint16_t, T>>& _layerIn, uint16_t _posIn)
		{
			return std::lower_bound(_layerIn.begin(), _layerIn.end(), _posIn, [](const auto& a, uint16_t pos) {return a.first < pos;});
		}

		/// <summary>
		/// Returns a pointer to the tile you searched up from the layer you searched in.
		/// </summary>
		/// <param name="_layerIn">Layers as in: What vector of the map struct you are looking through.</param>
		template<typename T>
		static T* Find(std::vector<std::pair<uint16_t, T>>& _layerIn, uint16_t _posIn)
		{
			auto iterator = Map::LowerBound(_layerIn, _posIn);

			// Checks if iteration is inside the vector, then checks if a position that matches _posIn actually got stored if so return the tile at that position.
			return (iterator != _layerIn.end() && iterator->first == _posIn) ? &iterator->second : nullptr;
		}

		// Overwrites if it finds a key that already exists.
		template<typename T>
		static T& SafeInsert(std::vector<std::pair<uint16_t, T>>& _layerIn, uint16_t _posIn, T _tileIn) 
		{
			auto iterator = Map::LowerBound(_layerIn, _posIn);

		    // Overwrite the tile if _posIn already exists
			if (iterator != _layerIn.end() && iterator->first == _posIn) 
			{
				iterator->second = _tileIn;
				return iterator->second;
			}

			// Insert if there is nothing to be overwritten.
			return _layerIn.insert(iterator, { _posIn, _tileIn })->second;
		}

		// Will duplicate a key if it finds a key that already exists. (That's like, bad so only use it during map loading)
		template<typename T>
		static T& DangerousInsert(std::vector<std::pair<uint16_t, T>>& _layerIn, uint16_t _posIn, T _tileIn)
		{
			return _layerIn.insert(LowerBound(_layerIn, _posIn), { _posIn, _tileIn })->second;
		}

		Map(xp::RexImage& mapIn);
	};
}

#endif
#include "Header Files/ExplorationState.h"
#include "Header Files/GameUtility.h"
#include <BearLibTerminal.h>
#include <string>
#include <chrono>

using namespace context;

namespace states
{
    ExplorationState ExplorationStateInstance;
    game_utility::Vector2<int8_t> currentDirection;


    void ExplorationState::Enter(GameContext* p_gameContext)
    {
        terminal_set("input.filter = [w, a, s, d, up, left, right, down, return, escape, MOUSE_RIGHT]");
        PrintMap(p_gameContext, p_gameContext->CurrentMap);
        SpawnEntity(p_gameContext, p_gameContext->Player);
        terminal_refresh();
    }

    
    void ExplorationState::Update(GameContext* p_gameContext)
    {
        p_gameContext->CurrentPrintHeight = terminal_state(TK_HEIGHT);
        p_gameContext->CurrentPrintWidth = terminal_state(TK_WIDTH) - 10;

        p_gameContext->Key = terminal_read();
        p_gameContext->CheckGameClose();

        //-1 is Left
        //+1 is Right

        //-1 is Up
        //+1 is Down

        currentDirection.Y = ( (p_gameContext->Key == TK_UP || p_gameContext->Key == TK_W) ? -1 : (p_gameContext->Key == TK_DOWN || p_gameContext->Key == TK_S) ? 1 : 0);
        currentDirection.X = ( (p_gameContext->Key == TK_LEFT || p_gameContext->Key == TK_A) ? -1 : (p_gameContext->Key == TK_RIGHT || p_gameContext->Key == TK_D) ? 1 : 0);
        
        // For when input is something other than movement.
        if (currentDirection == game_utility::Vector2<int8_t> {0, 0})
        {
            return;
        }

        FaceDirection(p_gameContext->Player, currentDirection);

        //Checks if the faced tile is in the bounds of the map and if it is not a solid tile on the collision layer.
        if (p_gameContext->Player.CurrentFacingTile.IsInBounds({ 0,0 }, { static_cast<int8_t>(terminal_state(TK_WIDTH) - 1), static_cast<int8_t>(terminal_state(TK_HEIGHT) - 1) } )
    && (!p_gameContext->CurrentMap.Find(p_gameContext->CurrentMap.Collisions, game_utility::Vector2<int8_t>::GetPosFromVector(p_gameContext->Player.CurrentFacingTile))))
        {
            MovePlayer(p_gameContext, currentDirection);
            FaceDirection(p_gameContext->Player, currentDirection);
        }

        terminal_refresh();
    }
    
    void ExplorationState::Exit(GameContext* p_gameContext)
    {
        p_gameContext->SwapFontAndLayer(context::UI);
        terminal_clear();
        terminal_refresh();
    }

    void ExplorationState::PrintMap(GameContext* p_gameContext, map_data::Map& mapIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_VISUAL);
        auto start = std::chrono::steady_clock::now();

        color_t previousTileColor = {};
        
        // These are the tiles that render behind/under the player.
        for (auto& [pos, tile] : mapIn.MapTileBack)
        {
            color_t currentColor = tile.color;

            if (previousTileColor != currentColor)
            {
                terminal_color(currentColor);
                previousTileColor = currentColor;
            }

            terminal_put(game_utility::DecodePosX(pos), game_utility::DecodePosY(pos), 0xE000 + tile.sprite);
        }

       // These are the tiles that render in front/above of the player.
       for (auto& [pos, tile] : mapIn.MapTileFore)
       {
           color_t currentColor = tile.color;
       
           if (previousTileColor != currentColor)
           {
               terminal_color(currentColor);
               previousTileColor = currentColor;
           }
       
           terminal_put(game_utility::DecodePosX(pos), game_utility::DecodePosY(pos), 0xE000 + tile.sprite);
       }

        terminal_color(themes::CurrentTheme.TextColor);
        terminal_refresh();

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        std::cout << "Map render time: " << duration << " microseconds\n";
    }

    void ExplorationState::MovePlayer(GameContext* p_gameContext, game_utility::Vector2<int8_t> directionIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
       
        p_gameContext->Player.PreviousPosition = p_gameContext->Player.CurrentPosition;
        p_gameContext->Player.CurrentPosition += directionIn;

        if (p_gameContext->Player.CurrentPosition != p_gameContext->Player.PreviousPosition)
        {
            terminal_clear_area(p_gameContext->Player.PreviousPosition.X, p_gameContext->Player.PreviousPosition.Y, 1, 1);
        }
    }

    void ExplorationState::FaceDirection(entities::Entity& entityIn, game_utility::Vector2<int8_t> directionIn)
    {
        auto newSprite = entityIn.SpriteData.CharacterSprites.find(directionIn);
        
        if (newSprite != entityIn.SpriteData.CharacterSprites.end())
        {
            terminal_color(newSprite->second.color);
            terminal_put(entityIn.CurrentPosition.X, entityIn.CurrentPosition.Y, 0xE000 + newSprite->second.sprite);
            entityIn.CurrentFacingTile = entityIn.CurrentPosition + directionIn;
        }
    }

    /// <summary>
    /// This one spawns an entity at the entity's own spawnlocation.
    /// </summary>
    void ExplorationState::SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
       
        terminal_color(entityIn.SpriteData.OverworldCharacterDown.color);
        
        entityIn.CurrentPosition = entityIn.SpawnPosition;
        
        terminal_put(entityIn.SpawnPosition.X, entityIn.SpawnPosition.Y, 0xE000 + p_gameContext->Player.SpriteData.OverworldCharacterDown.sprite);
    }

    /// <summary>
    /// This one spawns an entity at a given location.
    /// </summary>
    void ExplorationState::SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn, int spawnPosXIn, int spawnPosYIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
        terminal_color(entityIn.SpriteData.OverworldCharacterDown.color);

        entityIn.CurrentPosition.X = spawnPosXIn;
        entityIn.CurrentPosition.Y = spawnPosYIn;


        terminal_put(spawnPosXIn, spawnPosYIn, 0xE000 + p_gameContext->Player.SpriteData.OverworldCharacterDown.sprite);
    }
}

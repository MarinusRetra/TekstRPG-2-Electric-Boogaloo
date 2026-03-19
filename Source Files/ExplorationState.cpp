#include "Header Files/ExplorationState.h"
#include "Header Files/GameUtility.h"

#include <BearLibTerminal.h>
#include <string>
using namespace context;

namespace states
{
    ExplorationState ExplorationStateInstance;
    game_utility::Vector2<int> currentDirection;


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
        if (currentDirection == game_utility::Vector2<int>{0, 0})
        {
            return;
        }

        FaceDirection(p_gameContext->Player, currentDirection);

        //Checks if the faced tile is in the bounds of the map and if it is not a solid tile on the collision layer.
        if (p_gameContext->Player.CurrentFacingTile.IsInBounds({ 0,0 }, { terminal_state(TK_WIDTH)-1, terminal_state(TK_HEIGHT)-1 })
            && (xp::isTransparent(p_gameContext->CurrentMap.getTile(1, p_gameContext->Player.CurrentFacingTile.X, p_gameContext->Player.CurrentFacingTile.Y))))
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

    //TODO: Move this to the map_data namespace and print it there using the new map struct.
    void ExplorationState::PrintMap(GameContext* p_gameContext, xp::RexImage& mapIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_VISUAL);

        xp::RexTile firstTile = *mapIn.getTile(0, 0, 0);
        color_t previousTileFore = color_from_argb(255, firstTile.fore_red, firstTile.fore_green, firstTile.fore_blue);
        terminal_color(previousTileFore);

        for (int y = 0; y < mapIn.getHeight(); ++y)
        {
            for (int x = 0; x < mapIn.getWidth(); ++x)
            {
                xp::RexTile tile = *mapIn.getTile(0, x, y);

                color_t currentColor = color_from_argb(255, tile.fore_red, tile.fore_green, tile.fore_blue);
                if (previousTileFore != currentColor)
                {
                    terminal_color(currentColor);
                    previousTileFore = currentColor;
                }
                
                terminal_put(x, y, 0xE000 + game_utility::ConvertTileToTileIndex(tile));
            }
        }

        terminal_color(themes::CurrentTheme.TextColor);
        terminal_refresh();
    }

    void ExplorationState::MovePlayer(GameContext* p_gameContext, game_utility::Vector2<int> directionIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
       
        p_gameContext->Player.PreviousPosition = p_gameContext->Player.CurrentPosition;
        p_gameContext->Player.CurrentPosition += directionIn;

        if (p_gameContext->Player.CurrentPosition != p_gameContext->Player.PreviousPosition)
        {
            terminal_clear_area(p_gameContext->Player.PreviousPosition.X, p_gameContext->Player.PreviousPosition.Y, 1, 1);
        }
    }

    void ExplorationState::FaceDirection(entities::Entity& entityIn, game_utility::Vector2<int> directionIn)
    {
        auto newSprite = entityIn.SpriteData.CharacterSprites.find(directionIn);
        
        if (newSprite != entityIn.SpriteData.CharacterSprites.end())
        {
            terminal_color(color_from_argb(255, newSprite->second->fore_red, newSprite->second->fore_green, newSprite->second->fore_blue));
            terminal_put(entityIn.CurrentPosition.X, entityIn.CurrentPosition.Y, 0xE000 + game_utility::ConvertTileToTileIndex(*newSprite->second));
            entityIn.CurrentFacingTile = entityIn.CurrentPosition + directionIn;
        }
    }


    /// <summary>
    /// This one spawns an entity at the entity's own spawnlocation.
    /// </summary>
    void ExplorationState::SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
        terminal_color(color_from_argb(255, entityIn.SpriteData.OverworldCharacterDown->fore_red, entityIn.SpriteData.OverworldCharacterDown->fore_green, entityIn.SpriteData.OverworldCharacterDown->fore_blue));
       
        entityIn.CurrentPosition = entityIn.SpawnPosition;

        terminal_put(entityIn.SpawnPosition.X, entityIn.SpawnPosition.Y, 0xE000 + game_utility::ConvertTileToTileIndex(*p_gameContext->Player.SpriteData.CombatCharacter));
    }

    /// <summary>
    /// This one spawns an entity at a given location.
    /// </summary>
    void ExplorationState::SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn, int spawnPosXIn, int spawnPosYIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
        terminal_color(color_from_argb(255, entityIn.SpriteData.OverworldCharacterDown->fore_red, entityIn.SpriteData.OverworldCharacterDown->fore_green, entityIn.SpriteData.OverworldCharacterDown->fore_blue));

        terminal_put(spawnPosXIn, spawnPosYIn, 0xE000 + game_utility::ConvertTileToTileIndex(*p_gameContext->Player.SpriteData.CombatCharacter));
    }
}

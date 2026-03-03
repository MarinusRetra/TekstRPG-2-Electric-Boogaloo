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
        terminal_set("input.filter = [W,A,S,D, up, left, right, down, return, escape, MOUSE_RIGHT]");
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
        
        if (currentDirection == game_utility::Vector2<int>{0, 0})
        {
            return;
        }

        MovePlayer(p_gameContext, currentDirection);

        terminal_refresh();
    }
    
    void ExplorationState::Exit(GameContext* p_gameContext)
    {
        p_gameContext->SwapFontAndLayer(context::UI);
        terminal_clear();
        terminal_refresh();
    }

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

                uint32_t tileIndex = game_utility::ConvertTileToUint32(tile);

                terminal_put(x, y, 0xE000 + tileIndex);
            }
        }

        terminal_color(themes::CurrentTheme.TextColor);
        terminal_refresh();
    }


    void ExplorationState::MovePlayer(GameContext* p_gameContext, game_utility::Vector2<int> directionIn)
    {
        //Make the player sprite face the same direction as the player input.
        auto newSprite = p_gameContext->Player.SpriteData.CharacterSprites.find(directionIn);
        if (newSprite != p_gameContext->Player.SpriteData.CharacterSprites.end())
        {
          terminal_put(p_gameContext->Player.CurrentPosition.X, p_gameContext->Player.CurrentPosition.Y, 0xE000 + game_utility::ConvertTileToUint32(*newSprite->second));
        }

        int newX = p_gameContext->Player.CurrentPosition.X + directionIn.X;
        int newY = p_gameContext->Player.CurrentPosition.Y + directionIn.Y;

        if (newX < 0 || newX >= terminal_state(TK_WIDTH))
        {
            return;
        }
        else if (newY < 0 || newY >= terminal_state(TK_HEIGHT))
        {
            return;
        }
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
        terminal_color(color_from_argb(255, newSprite->second->fore_red, newSprite->second->fore_green, newSprite->second->fore_blue));
        
        p_gameContext->Player.PreviousPosition = p_gameContext->Player.CurrentPosition;
        p_gameContext->Player.CurrentPosition += directionIn;

        //Make the player sprite face the same direction as the player input.
        if (newSprite != p_gameContext->Player.SpriteData.CharacterSprites.end())
        {
            terminal_put(p_gameContext->Player.CurrentPosition.X, p_gameContext->Player.CurrentPosition.Y, 0xE000 + game_utility::ConvertTileToUint32(*newSprite->second));
            terminal_clear_area(p_gameContext->Player.PreviousPosition.X, p_gameContext->Player.PreviousPosition.Y, 1, 1);
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

        terminal_put(entityIn.SpawnPosition.X, entityIn.SpawnPosition.Y, 0xE000 + game_utility::ConvertTileToUint32(*p_gameContext->Player.SpriteData.CombatCharacter));
    }

    /// <summary>
    /// This one spawns an entity at a given location.
    /// </summary>
    void ExplorationState::SpawnEntity(GameContext* p_gameContext, entities::Entity& entityIn, int spawnPosXIn, int spawnPosYIn)
    {
        p_gameContext->SwapFontAndLayer(context::MAP_INTERACTABLES);
        terminal_color(color_from_argb(255, entityIn.SpriteData.OverworldCharacterDown->fore_red, entityIn.SpriteData.OverworldCharacterDown->fore_green, entityIn.SpriteData.OverworldCharacterDown->fore_blue));

        terminal_put(spawnPosXIn, spawnPosYIn, 0xE000 + game_utility::ConvertTileToUint32(*p_gameContext->Player.SpriteData.CombatCharacter));
    }




}

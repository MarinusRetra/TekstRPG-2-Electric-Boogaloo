#include "Header Files/ExplorationState.h"
#include <BearLibTerminal.h>
#include <string>

#include <vector>
#include <fstream>
#include <iostream>

using namespace context;

namespace states
{
    ExplorationState ExplorationStateInstance;

    void ExplorationState::Enter(GameContext* p_gameContext)
    {
        PrintMap(p_gameContext, p_gameContext->currentMap);

        terminal_refresh();

    }
    
    void ExplorationState::Update(GameContext* p_gameContext)
    {
       // terminal_clear();

        p_gameContext->Key = terminal_read();
        p_gameContext->CheckGameClose();

        p_gameContext->CurrentPrintHeight = terminal_state(TK_HEIGHT);
        p_gameContext->CurrentPrintWidth = terminal_state(TK_WIDTH) - 10;

        terminal_refresh();
    }
    
    void ExplorationState::Exit(GameContext* p_gameContext)
    {
        terminal_layer(0); //TODO: Make proper swapfont functions.
        terminal_set("font: Fonts/cp437_16x16.png, size=16x16, codepage=437");
        terminal_clear();
        terminal_refresh();
    }

    void ExplorationState::PrintMap(GameContext* p_gameContext, xp::RexImage& mapIn)//TODO: Clean this function up a bit.
    {
        terminal_clear();
        terminal_layer(1);
        terminal_set("font: Fonts/Monochrome_ReReRePacked.png, size=16x16, layout=16x352, codepage=Fonts/Monochrome_ReReRePacked_codepage.txt");

        static std::vector<int> glyphMap;
        if (glyphMap.empty())
        {
            std::ifstream codepageFile("Fonts/Monochrome_ReReRePacked_codepage.txt");
            std::string line;
            while (std::getline(codepageFile, line)) {
                if (!line.empty()) {
                    if (line.rfind("U+", 0) == 0)
                    {
                        line = line.substr(2);
                    }
                    int codepoint = std::stoi(line, nullptr, 16);
                    glyphMap.push_back(codepoint);
                }
            }
        }

        //for (int i = 0; i < 80; i++)
        //{
        //    terminal_put(i, 10, glyphMap[i]);
        //}
        //for (int i = 256; i < 336; i++)
        //{
        //    terminal_put(i-256, 12, glyphMap[i]);
        //}
        //terminal_refresh();

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

                uint32_t tileIndex = // The reximage struct was not made for fonts larger than 16x32 so i had to change it.
                    static_cast<uint32_t>(tile.character) |
                    (static_cast<uint32_t>(tile.__padding[0]) << 8) |
                    (static_cast<uint32_t>(tile.__padding[1]) << 16) |
                    (static_cast<uint32_t>(tile.__padding[2]) << 24);

                if (tileIndex < glyphMap.size())
                {
                    terminal_put(x, y, glyphMap[tileIndex]);
                }
            }
        }

        terminal_color(themes::CurrentTheme.TextColor);
        terminal_refresh();
    }


    // TODO: later add offset.
    //int cameraX;
    //int cameraY;

    //terminal_put(x - cameraX, y - cameraY, character);
}

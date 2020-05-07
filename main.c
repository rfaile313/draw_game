#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/r_types.h"
#include "src/logic.h"

#include "src/animation.c"
#include "src/resources.c"
#include "src/bools.c"
#include "src/tile.c"

#include "src/stateTitle.c"
#include "src/stateLevel.c"
#include "src/stateCore.c"

// --- Program entry point
int main(void)
{
    // Initialization
    //----------------------------------------------------------------------------
    const u16 screenWidth = GAME_SCREEN_WIDTH;
    const u16 screenHeight = GAME_SCREEN_HEIGHT;

    f32 enemyShootTime = 0.0f;
    f32 enemyDifficulty = 1.5f;
    
    //removed raylib output unless there's a warning -- h/t skytrias!
    SetTraceLogLevel(LOG_WARNING);
    //init window - must come before texture, loading calls (OpenGL context required)
    InitWindow(screenWidth, screenHeight, GAME_NAME);

    // Initialize audio device (required for sound)
    InitAudioDevice();
    
    //load resources
    fxInitial = LoadSound(soundInitial);
    fxDraw    = LoadSound(soundDraw);
    fxShoot   = LoadSound(soundShoot);
    fxLose    = LoadSound(soundLose);      
    
    charTexture = LoadTexture(charTexturePath); //128/4 x 256/8
    tileTexture = LoadTexture(tileTexturePath);

    alagard = LoadFont(fontAlagard);

    //-->end resource load


    //default values
    modifyTile(&player, 0.0f, 0.0f, 200.0f, 300.0f, PRSW, PRSH,  PRDW, PRDH);
    
    modifyTile(&enemy1, 120.0f, 60.0f, 600.0f, 300.0f, -PRSW, PRSH,  PRDW, PRDH);

    //set the starting state
    currentState = TITLE;

    //Set game to run at 60 frames-per-second
    SetTargetFPS(FPS);
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update---------------->
        switch(currentState)
        {
            case TITLE:
            {
                updateTitleScreen();
                if(titleScreenFinished() == 1) //don't need the "1" with one option but will have more
                {
                    initLevel();
                    currentState = LEVEL;
                    //Note: Change Game state
                    //Note: Unload title assets if any
                }
            }break;
            case LEVEL:
            {
                updateLevelScreen();

                if (levelScreenFinished()){
                    initCore();
                    currentState = CORE;
                }

            }break;
            case CORE:
            {
                updateCore();
            }break;
            case SHOOT:
            {

            }break;
            case WIN:
            {

            }break;
            case LOSE:
            {

            }break;
            case END:
            {

            }break;
            default: break;
        }
        //------------->Update

        //Draw---------->
        BeginDrawing();
        
        //required
        ClearBackground(BLACK);
        
        switch(currentState)
        {
            case TITLE:
            {
                drawTitleScreen();
            }break;
            case LEVEL:
            {
                drawLevelScreen();
            }break;
            case CORE:
            {
                drawCoreScreen();
            }break;
            case SHOOT:
            {

            }break;
            case WIN:
            {

            }break;
            case LOSE:
            {

            }break;
            case END:
            {

            }break;
            default: break;
        }
        
        //-end draw
        EndDrawing();
        //-------------->Draw
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(charTexture);
    UnloadTexture(tileTexture);
    UnloadFont(alagard);
    UnloadSound(fxInitial);
    UnloadSound(fxDraw);
    UnloadSound(fxShoot);
    UnloadSound(fxLose);
    CloseAudioDevice(); 
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}

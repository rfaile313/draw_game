//only external dependency
#include <raylib.h>
//headers
#include "src/r_types.h" 
#include "src/logic.h"
//unity
#include "src/animation.c"
#include "src/resources.c"
#include "src/stateTitle.c"
#include "src/stateLevel.c"
#include "src/stateCore.c"

// --- Program entry point
int main(void)
{
    // Initialization------>
    const u16 screenWidth = GAME_SCREEN_WIDTH;
    const u16 screenHeight = GAME_SCREEN_HEIGHT;
    
    //removed raylib output unless there's a warning -- h/t skytrias!
    SetTraceLogLevel(LOG_WARNING);
    //init window - must come before texture, loading calls (OpenGL context required)
    InitWindow(screenWidth, screenHeight, GAME_NAME);
    //this should only reset on new game or if called directly
    modifyTile(&xAnim, 0.0f, 0.0f, 140.0f, 250.0f, 64.0f, 64.0f, 192.0f, 192.0f);
    // Initialize audio device (required for sound)
    InitAudioDevice();
    
    //load resources--->
    fxBullet  = LoadSound(soundBullet);
    fxDraw    = LoadSound(soundDraw);
    fxError   = LoadSound(soundError);
    fxInitial = LoadSound(soundInitial);
    fxLose    = LoadSound(soundLose);
    fxLoseWdl = LoadSound(soundLoseWdl);
    fxOrgan   = LoadSound(soundOrgan); 
    fxShoot   = LoadSound(soundShoot);
    fxWin     = LoadSound(soundWin);
         
    charTexture = LoadTexture(charTexturePath); //128/4 x 256/8
    tileTexture = LoadTexture(tileTexturePath);
    enemy1IdleTexture = LoadTexture(enemy1IdleTexturePath);
    xAnimationTexture = LoadTexture(xAnimationTexturePath);

    alagard = LoadFont(fontAlagard);
    //-->end resource load

    //set the starting state
    currentState = TITLE;

    //Set game to run at 60 frames-per-second
    SetTargetFPS(FPS);
    //---> end initialization------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update---------------->
        switch(currentState)
        {
            case TITLE:
            {
                updateTitleScreen();
                if(titleScreenFinished() == 1) //1 = next screen
                {
                    choice = 0; //resets titleScreenFinished()
                    initLevel(); //function in stateTitle.c: resets variables from logic.h
                    currentState = LEVEL; 
                }
   
            }break;
            case LEVEL:
            {
                if (earlystatus == warning)
                {
                    initLevel();
                    earlystatus = restart;      
                }
                if (bRestart)
                {
                    initLevel();
                    bRestart = false;
                }

                updateLevelScreen();
                if (levelScreenFinished() == 1)
                {
                    nextScreen = 0; //resets levelScreenFinished()
                    initCore();
                    currentState = CORE;
                }

            }break;
            case CORE: 
            {
                updateCore();
                if(finishCore() == 1)
                {
                    finishstate = 0;
                    currentState = TITLE;
                }
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
        
        //EndDrawing() (Required)
        EndDrawing();
        //-------------->Draw
    }
    
    // De-Initialization
    // Unload Resources 
    UnloadTexture(charTexture);
    UnloadTexture(tileTexture);
    UnloadTexture(enemy1IdleTexture);
    UnloadSound(fxInitial);
    UnloadSound(fxDraw);
    UnloadSound(fxShoot);
    UnloadSound(fxLose);
    UnloadSound(fxOrgan);
    UnloadSound(fxLoseWdl);
    UnloadSound(fxError);
    UnloadSound(fxBullet);
    UnloadSound(fxWin);
    UnloadFont(alagard);
    // Close audio
    CloseAudioDevice(); 
    // Close window and OpenGL context
    CloseWindow();        
    
    return 0;
}

//only external dependency
#include <raylib.h> 
//headers
#include "src/r_types.h" 
#include "src/logic.h"
//unity
#include "src/animation.c"
#include "src/resources.c"
#include "src/tile.c"
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

    // Initialize audio device (required for sound)
    InitAudioDevice();
    
    //load resources
    fxBullet  = LoadSound(soundBullet);
    fxDraw    = LoadSound(soundDraw);
    fxError   = LoadSound(soundError);
    fxInitial = LoadSound(soundInitial);
    fxLose    = LoadSound(soundLose);
    fxOrgan   = LoadSound(soundOrgan); 
    fxShoot   = LoadSound(soundShoot);
         
    
    charTexture = LoadTexture(charTexturePath); //128/4 x 256/8
    tileTexture = LoadTexture(tileTexturePath);
    enemy1IdleTexture = LoadTexture(enemy1IdleTexturePath);

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
                if(titleScreenFinished() == 1) //don't need the "1" with one option but will have more
                {
                    choice = 0; //resets titleScreenFinished()
                    initLevel(); //function in stateTitle.c: resets variables from logic.h
                    currentState = LEVEL; 
                }
            }break;
            case LEVEL:
            {
                updateLevelScreen();

                if (levelScreenFinished() == 1){
                    nextScreen = 0; //resets levelScreenFinished()
                    initCore();
                    currentState = CORE;
                }

            }break;
            case CORE: 
            {
                updateCore();
                if(finishCore() == 1){
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
    UnloadSound(fxInitial);
    UnloadSound(fxDraw);
    UnloadSound(fxShoot);
    UnloadSound(fxLose);
    UnloadFont(alagard);
    // Close audio
    CloseAudioDevice(); 
    // Close window and OpenGL context
    CloseWindow();        
    
    return 0;
}

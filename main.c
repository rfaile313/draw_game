#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "src/r_types.h"
#include "src/logic.h"

#include "src/animation.c"
#include "src/resources.c"
#include "src/bools.c"
#include "src/tile.c"

// --- Program entry point
int main(void)
{
    // Initialization
    //----------------------------------------------------------------------------
    const u16 screenWidth = 960;
    const u16 screenHeight = 572;
    
    const f32 PRSW = 20.0f; //20px RECTANGLE SOURCE WIDTH
    const f32 PRSH = 20.0f; //20px RECTANGLE SOURCE HEIGHT
    
    const f32 PRDW = 100.0f; //100px RECTANGLE DEST WIDTH
    const f32 PRDH = 100.0f; //100px RECTANGLE DEST HEIGHT

    f32 enemyShootTime = 0.0f;
    f32 enemyDifficulty = 1.5f;
    
    //removed raylib output unless there's a warning -- h/t skytrias!
    SetTraceLogLevel(LOG_WARNING);
    //init window - must come before texture, loading calls (OpenGL context required)
    InitWindow(screenWidth, screenHeight, GAME_NAME);

    // Initialize audio device (required for sound)
    InitAudioDevice();
    
    //load resources
    Sound fxInitial = LoadSound(soundInitial);
    Sound fxDraw    = LoadSound(soundDraw);
    Sound fxShoot   = LoadSound(soundShoot);
    Sound fxLose    = LoadSound(soundLose);      
    
    Texture2D charTexture = LoadTexture(charTexturePath); //128/4 x 256/8
    Texture2D tileTexture = LoadTexture(tileTexturePath);

    Font alagard = LoadFont(fontAlagard);

    //-->end resource load

    //init player and set to default tile  (20x20 px rects) (160x100)
    Tile player = {0};
    //init first enemy and set to default tile  (20x20 px rects) (160x100) negative source width to flip X
    Tile enemy1 = {0};

    //default values
    modifyTile(&player, 0.0f, 0.0f, 200.0f, 300.0f, PRSW, PRSH,  PRDW, PRDH);
    
    modifyTile(&enemy1, 120.0f, 60.0f, 600.0f, 300.0f, -PRSW, PRSH,  PRDW, PRDH);
    
    //TODO: refactor these with enum
    bool bDRAW = false;
    bool bENEMYSHOOTANDWIN = false;
    bool bPLAYERSHOOTANDWIN = false;
    
    //NOTE: maybe decrease time from level to draw as difficulty rises?
    int check = GetRandomValue(3,6);
    
    //Set game to run at 60 frames-per-second
    SetTargetFPS(FPS);
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update---------------->
        //player anim/control
        frameCounter++;
        frameCounter1++;
        //stores seconds from time initWindow is called/ f32 value
        seconds = GetTime();
        
        //initialsound
        playSoundOnce(fxInitial, &initSfxPlayed);

        //default anim
        if(!bDRAW)animation(0, &player, 0, &enemy1);

        //draw
        if(bDRAW)
        {
            enemyShootTime += GetFrameTime();

            animation(1, &player, 1, &enemy1);
            playSoundOnce(fxDraw, &drawSfxPlayed);

            if (enemyShootTime >= 1.5f){
                enemyShootTime = 0;
                playSoundOnce(fxShoot, &shootSfxPlayed);
                bDRAW = false;
                animation(1, &player, 2, &enemy1); //TODO: animate player die
                bENEMYSHOOTANDWIN = true;
            }

            /*
            if (IsKeyPressed(KEY_SPACE))
            {
            
            }
            */
        }
        
        if(checkAgainst(seconds, check)) bDRAW = true;
        
        //------------->Update
        //--------------------------
        //Draw---------->
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
        DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);
        

        
        //Display Level, Prior to shoot.
        if(!bDRAW){

        DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
        
        DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);

            //TODO: size and spacing are f32s, should fix.
            // 60/x == 2 every 30 frames     60/x == 4 every 15 frames
            if(frameCounter1 >= (60/4) )
            {
                DrawTextEx(alagard, LEVEL_1, posLevel, alagard.baseSize * 2, 1, WHITE);
                
                if(frameCounter1  >= (60/2))
                {
                    frameCounter1 = 0;
                }
                
            }
        }
        
        //Draw! 
        if(bDRAW){
            DrawTextEx(alagard, GAME_NAME, posDraw, alagard.baseSize * 2, 1, WHITE);
            DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
            DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
        }
        
        //Shoot

        //Win

        //Lose
        if(bENEMYSHOOTANDWIN){
            DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
            DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
        }

        
        DrawText(TextFormat("%02.02f Seconds", seconds), 50, 50, 40, LIME);
        //%1.02f for two digit places i.e. 1.02 seconds
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

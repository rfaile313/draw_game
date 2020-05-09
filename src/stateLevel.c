#include <raylib.h>
#include "r_types.h"
#include "logic.h"

void initLevel(void){
    //initialize and reset variables

    //player initial poses
    modifyTile(&player, 0.0f, 0.0f, 200.0f, 300.0f, PRSW, PRSH,  PRDW, PRDH);
    modifyTile(&enemy1, 120.0f, 60.0f, 600.0f, 300.0f, -PRSW, PRSH,  PRDW, PRDH);
    modifyTile(&enemy1idle, 0.0f, 0.0f, 600.0f, 300.0f, -PRDW, PRDW,  PRDW, PRDW);

    //default values
    stateLevelCounter = 0;
    nextScreen = 0;
    timePassed = GetTime();
    check = GetRandomValue(3,6);
    PlaySound(fxInitial);

    //animation.c variables set to 0
    animationCounter = 0;
    enemystate = shoot;
    playerstate = reset;

}


void updateLevelScreen(void){
    stateLevelCounter++;
   
    //TODO: size and spacing are f32s, should fix (WHAT????????????????)
    // 60/x == 2 every 30 frames     60/x == 4 every 15 frames
    animation(0, &player, 0, &enemy1);

    if (GetTime() - timePassed >= check) { 
        nextScreen = 1; 
    } 

}

void drawLevelScreen(void){

    //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
    DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);

    // You can use this code when you are ready to weild its power (ty anata)
    // DrawTextEx(alagard, LEVEL_1, posLevel, alagard.baseSize * 2, 1, Fade( WHITE, (((int)(GetTime() * 10) >> 2  ) % 100) & 1 ? 255 : 0 ));
    // Refactor might be better as (GetTime() * 100)  / 32 ) % 2)
    // or (int)GetTime() % 4 >= 4 / 2 ? 255 : 0 -- h/t vortfu
    
    //flashing text
    if(stateLevelCounter >= (FPS/4) )
    {  
        //TODO: will need to change "Level 1" to show multiple levels
        DrawTextEx(alagard, LEVEL_1, posLevel, alagard.baseSize * 2, 1, WHITE);

        if(stateLevelCounter >= (FPS/2))
        {
            stateLevelCounter = 0;
        }

    }//---> flashing text


    DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
    DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
    //if use enemy1idletexture //DrawTexturePro(enemy1IdleTexture, enemy1idle.source, enemy1idle.dest, origin, rotation, WHITE);

}

int levelScreenFinished(void){
    return nextScreen;
}
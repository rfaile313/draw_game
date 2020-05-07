#include <raylib.h>
#include "r_types.h"
#include "logic.h"
#include <stdio.h>

u8 nextScreen = 0;
u16 check;
u32 stateLevelCounter = 0;

f64 timePassed;

void initLevel(void){
    //initialize and reset variables
    stateLevelCounter = 0;
    timePassed = GetTime();
    check = GetRandomValue(3,6);
    PlaySound(fxInitial);
}

//actual drawing declaration
void drawLevelText(void){
    DrawTextEx(alagard, LEVEL_1, posLevel, alagard.baseSize * 2, 1, WHITE);
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
    
    //flashing text
    if(stateLevelCounter >= (FPS/4) )
    {  
        drawLevelText();

        if(stateLevelCounter >= (FPS/2))
        {
            stateLevelCounter = 0;
        }

    }//---> flashing text


    DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
    DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);

}

int levelScreenFinished(void){
    return nextScreen;
}
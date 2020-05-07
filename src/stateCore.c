#include <raylib.h>
#include "r_types.h"
#include "logic.h"

u8 stateCoreFinish = 0;
u32 stateCoreCounter = 0;
f64 stateCoreSeconds = 0;

void initCore(void){
    PlaySound(fxDraw);
    stateCoreCounter = 0;
    stateCoreSeconds = GetTime ();
}

void updateCore(void){
// the enemy a certain time to shoot based on difficulty
// the player has to shoot before they get shot
// but not before you draw your weapon

    animation(1, &player, 1, &enemy1);

    //enemy win condition
    if (GetTime() - stateCoreSeconds >= ENEMY_DIFFICULTY){
        //enemy wins
    }

    //if you press space and the enemy hasn't won that means you've won
    if(IsKeyPressed(KEY_SPACE)){
        //enemy lose, play animations, change state
    }


}

void drawCoreScreen(void){

    //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
    DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);

    DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
    DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
}

int finishCore(void){
    return stateCoreFinish;
}


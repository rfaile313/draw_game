#include <raylib.h>
#include "r_types.h"
#include "logic.h"

enum CoreGameplay{
draw = 0,
win,
lose,
finish
};

enum FinishState{
nothing = 0,
gototitle,
gotonextscreen
};

enum CoreGameplay coregameplay;
enum FinishState finishstate;

void initCore(void){
    PlaySound(fxDraw);
    coregameplay = draw;
    finishstate = nothing;
    stateCoreSeconds = GetTime ();
}

void updateCore(void){
// the enemy a certain time to shoot based on difficulty
// the player has to shoot before they get shot
// but not before you draw your weapon
   
   if(coregameplay == draw)animation(1, &player, 1, &enemy1);

    //enemy win condition
    if (GetTime() - stateCoreSeconds >= ENEMY_DIFFICULTY){
        if(coregameplay == draw){
            PlaySound(fxShoot);
        }
        coregameplay = lose;
  
        animation(4, &player, 3, &enemy1);

        if (GetTime() - stateCoreSeconds >= (ENEMY_DIFFICULTY + 2) ) {
        //wait 2 seconds ^, then

        finishstate = gototitle;

        }

    }

    //if you press space and the enemy hasn't won that means you've won
    if(IsKeyPressed(KEY_SPACE) && coregameplay != lose){
        if(coregameplay == draw)PlaySound(fxShoot);
        coregameplay = win;
        //enemy lose, play animations, change state
        if(coregameplay == win)
            {
                animation(3, &player, 4, &enemy1);
                if( ( (GetTime() - stateCoreSeconds) + ENEMY_DIFFICULTY) >= ( ( (GetTime() - stateCoreSeconds) + ENEMY_DIFFICULTY) + 1)  )
                {
                    printf("Enemy wins\n");
                }
            }
    }

}

void drawCoreScreen(void){

    //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
    DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);

    DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
    DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);

    DrawTextEx(alagard, GAME_NAME, posDraw, alagard.baseSize * 2, 1, WHITE);
}

int finishCore(void){
    return finishstate;
}


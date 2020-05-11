#include <raylib.h>
#include "r_types.h"
#include "logic.h"

enum EarlyStatus{
    ok = 0,
    warning,
    restart,
    pleasewait,
    losethegame,
    losethegame1
};

enum EarlyStatus earlystatus;

void initLevel(void)
{
    //initialize and reset variables
	
	earlystatus = ok; // Note(rif): does this need to come before the tile mod below?

    //player initial poses
    modifyTile(&player, 0.0f, 0.0f, 200.0f, 300.0f, TWENTY, TWENTY,  ONE_HUNDRED, ONE_HUNDRED);
    modifyTile(&enemy1, 120.0f, 60.0f, 600.0f, 300.0f, -TWENTY, TWENTY,  ONE_HUNDRED, ONE_HUNDRED);
    modifyTile(&enemy1idle, 0.0f, 0.0f, 600.0f, 300.0f, -ONE_HUNDRED, ONE_HUNDRED,  ONE_HUNDRED, ONE_HUNDRED);

    //default values
    stateLevelCounter = 0;
    nextScreen = 0;
    errorCount = 0;
    bWait = false;

    timePassed = GetTime();
    check = GetRandomValue(3,6);
    PlaySound(fxInitial);

    //animation.c variables set to 0
    animationCounter = 0;
    animation1Counter= 0;
    fastestAnimationCounter=0;
    enemystate = shoot;
    playerstate = reset;
}


void updateLevelScreen(void)
{
    stateLevelCounter++;

    //TODO: change condition
    animation(0, &player, 0, &enemy1); //default animation

    if(earlystatus==pleasewait)
    {
        animation1(1, &xAnim);
    }
    //if fault
    if(IsKeyPressed(KEY_SPACE))
    { //if pressed at all here its a fault, if already fault, it's a lose.
        if(earlystatus == ok)
        {
            PlaySound(fxError);
            earlystatus = pleasewait;
            bWait = true;
            timePassed = GetTime();
        }
        if(earlystatus == restart) //game over
        {   
            PlaySound(fxError);
            
            earlystatus = losethegame;
            bWait = true;
            timePassed = GetTime();
        }
    }
    
    if (earlystatus == pleasewait)
        {
            if(GetTime() - timePassed >= 4) 
            {
            earlystatus = warning; //restarts in main.c
            }
        }

    if (earlystatus == losethegame)
        {
            if(GetTime() - timePassed >= 1) 
            {
                PlaySound(fxLose);
                earlystatus=losethegame1;
            }
        }

   if (earlystatus == losethegame1)
    {
        if(GetTime() - timePassed >= 4) 
            {
				earlystatus = ok; //reset earlystatus 
                modifyTile(&xAnim, 0.0f, 0.0f, 140.0f, 250.0f, 64.0f, 64.0f, 192.0f, 192.0f); //reset X tile
				choice = 0; //reset title choice
                currentState = TITLE;
            }
    }


    //advance to core if they get here amount of time before draw, random every time
    if ( GetTime() - timePassed >= check && !bWait) { 
	//reset X tile
	earlystatus=ok;
    modifyTile(&xAnim, 0.0f, 0.0f, 140.0f, 250.0f, 64.0f, 64.0f, 192.0f, 192.0f); //reset X tile 
	nextScreen = 1; 
    } 

}//update

void drawLevelScreen(void)
{

    //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
    DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);

    DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
    DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
    //if use enemy1idletexture //DrawTexturePro(enemy1IdleTexture, enemy1idle.source, enemy1idle.dest, origin, rotation, WHITE);

    if(earlystatus != ok)
    {
        DrawTexturePro(xAnimationTexture, xAnim.source, xAnim.dest, origin, rotation, WHITE);
 
    }

    // You can use this code when you are ready to weild its power (ty anata)
    // DrawTextEx(alagard, LEVEL_1, posLevel, alagard.baseSize * 2, 1, Fade( WHITE, (((int)(GetTime() * 10) >> 2  ) % 100) & 1 ? 255 : 0 ));
    // Refactor might be better as (GetTime() * 100)  / 32 ) % 2)
    // or (int)GetTime() % 4 >= 4 / 2 ? 255 : 0 -- h/t vortfu
    
        
    //flashing text, every 15 frames at 60/4
    if(!bWait)
    {
        if(stateLevelCounter >= (FPS/4) )
        {  

            DrawTextEx(alagard, FormatText("Level %i", currentLevel), posLevel, alagard.baseSize * 2, 1, WHITE);

            if(stateLevelCounter >= (FPS/2))
            {
                stateLevelCounter = 0;
            }

        }//---> flashing text
    }

    
    if(earlystatus == pleasewait || earlystatus == losethegame || earlystatus == losethegame1)
    {
        if(stateLevelCounter >= (FPS/4) )
        {  

            if(earlystatus == pleasewait)DrawTextEx(alagard, "TOO SOON!", posTooSoon, alagard.baseSize * 2, 1, WHITE);
            if(earlystatus != pleasewait)DrawTextEx(alagard, "Two Faults = LOSE", posTwoFaults, alagard.baseSize * 2, 1, WHITE);

            if(stateLevelCounter >= (FPS/2))
            {
                stateLevelCounter = 0;
            }

        }//---> flashing text
        
        
    }
    
}//draw

int levelScreenFinished(void)
{
    return nextScreen;
}

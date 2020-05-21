#include <raylib.h>
#include "r_types.h"
#include "logic.h"
#include <stdio.h>

void updateOptionsScreen(void)
{	
	if(IsKeyPressed(KEY_UP))
	{
        arrowPosY -= 100;
        if(arrowPosY <= 200) arrowPosY = 200;
    }

	if(IsKeyPressed(KEY_DOWN))
	{
        arrowPosY += 100; // 200 back, 250 difficulty title, 300 difficulty, 350 sound title, 400 snd
        if(arrowPosY >= 400) arrowPosY = 400;
    }
	
	if(IsKeyPressed(KEY_LEFT))
	{
		if(arrowPosY == 300) //difficulty
		{
			PlaySound(fxToggle);
			if(gamedifficulty == difficultyNormal)
			{
				gamedifficulty = difficultyEasy;
				ENEMY_DIFFICULTY = DIFF_EASY;	
			}
			else if(gamedifficulty == difficultyEasy)
			{
				gamedifficulty = difficultyHard;
				ENEMY_DIFFICULTY = DIFF_HARD;	
			}
			else if(gamedifficulty == difficultyHard)
			{
				gamedifficulty = difficultyNormal;
				ENEMY_DIFFICULTY = DIFF_EASY;	
			}
			
		}
		else if(arrowPosY == 400) //sound
		{
			PlaySound(fxToggle);
			if(gameSound)
			{
				gameSound = false;
				SetMasterVolume(0);
			}
			else if(!gameSound)
			{
				gameSound = true;
				SetMasterVolume(1);
			}
		}
	}

	if(IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_SPACE))
	{
		if(arrowPosY == 300) //difficulty
		{
			PlaySound(fxToggle);
			if(gamedifficulty == difficultyNormal)
			{
				gamedifficulty = difficultyHard;
				ENEMY_DIFFICULTY = DIFF_HARD;	
			}
			else if(gamedifficulty == difficultyHard)
			{
				gamedifficulty = difficultyEasy;
				ENEMY_DIFFICULTY = DIFF_EASY;
			}
			else if(gamedifficulty == difficultyEasy)
			{
				gamedifficulty = difficultyNormal;
				ENEMY_DIFFICULTY = DIFF_NORMAL;
			}
		}
		else if(arrowPosY == 400) //sound
		{
			PlaySound(fxToggle);
			if(gameSound)
			{
				gameSound = false;
				SetMasterVolume(0);
			}
			else if(!gameSound)
			{
				gameSound = true;
				SetMasterVolume(1);
			}	
		}
	}

    if(IsKeyPressed(KEY_SPACE))
	{
        //TODO: add fancy animations
        if (arrowPosY == 200) 
		{
			//set arrow back to play
			arrowPosX = 250;
			arrowPosY = 300;
			choice = 0; //back  
		}   
    }

}//-->updateOptionsScreen()

void drawOptionsScreen(void)
{
	DrawText(fontOptionsScrn, (backPosX - 60), (backPosY - 110), 100, WHITE);

	DrawText(fontBack,       (backPosX + 30), backPosY, backSize, WHITE);
	DrawText(fontDifficulty, backPosX, (backPosY + 50), backSize, WHITE);
	DrawText(fontSound,      (backPosX + 15), (backPosY + 150), backSize, WHITE);	

	//draw different difficulty
	
	if(gamedifficulty == difficultyEasy)   DrawText(fontEasy,   (backPosX + 20), (backPosY + 100), backSize, WHITE);
	if(gamedifficulty == difficultyNormal) DrawText(fontNormal, (backPosX + 15), (backPosY + 100), backSize, WHITE);
	if(gamedifficulty == difficultyHard)   DrawText(fontHard,   (backPosX + 20), (backPosY + 100), backSize, WHITE);

	//draw different sound
	
	if(gameSound)  DrawText(fontOn,  (backPosX + 30), (backPosY + 200), backSize, WHITE);
	if(!gameSound) DrawText(fontOff, (backPosX + 30), (backPosY + 200), backSize, WHITE);

	DrawText(fontArrow, arrowPosX, arrowPosY, arrowSize, WHITE);
	DrawText(fontTest, testPosX, testPosY, testSize, WHITE);        
}



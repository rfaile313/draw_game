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

void updateCore(void)
{
	// the enemy a certain time to shoot based on difficulty
	// the player has to shoot before they get shot
	// but not before you draw your weapon

	if(coregameplay == draw)animation(1, &player, 1, &enemy1);

	//enemy win condition
	if (GetTime() - stateCoreSeconds >= ENEMY_DIFFICULTY && coregameplay != win)
	{
		if(coregameplay == draw)
		{
			PlaySound(fxShoot);
			PlaySound(fxLoseWdl); //has 1s delay
			//explicitly change bullet starting position, flip source width to flip x axis
			modifyTile(&bullet, 0.0f, 0.0f, 575.0f, 340.0f, -32.0f, 32.0f, 32.0f, 32.0f);	
			//reset time
			stateCoreSeconds = GetTime();
			coregameplay = lose;
		}
	}

	if(coregameplay == lose)
	{
		if(GetTime() - stateCoreSeconds < 0.15f) animation(1, &player, 3, &enemy1); //enemy shoot, player stays draw
		if(GetTime() - stateCoreSeconds > 0.15f) animation(4, &player, 6, &enemy1); //player die, enemy taunt
		animation1(3, &bullet); //bullet animation

		if (GetTime() - stateCoreSeconds >= 4 ) 
		{
			//wait 4 seconds ^, then
			//reset levels, difficulty
			currentLevel = 1;
			if(gamedifficulty == difficultyNormal)
			{
				ENEMY_DIFFICULTY = DIFF_NORMAL;	
			}
			else if(gamedifficulty == difficultyHard)
			{
				ENEMY_DIFFICULTY = DIFF_HARD;
			}
			else if(gamedifficulty == difficultyEasy)
			{
				ENEMY_DIFFICULTY = DIFF_EASY;
			}
			//reset
			finishstate = gototitle;
		}
	}


	//if you press space and the enemy hasn't won that means you've won
	if(IsKeyPressed(KEY_SPACE) && coregameplay != lose)
	{
		if(coregameplay == draw){
			//one time
			PlaySound(fxShoot);
			PlaySound(fxWin);
			//increment level
			currentLevel += 1;
			ENEMY_DIFFICULTY -= DIFFICULTY_MULTIPLIER;
			//set time
			stateCoreSeconds = GetTime();
			//change inner state
			coregameplay = win;
		}
		//enemy lose, play animations, change state
	}

	if (coregameplay == win)
	{

		if(GetTime() - stateCoreSeconds <= 0.25f) animation(2, &player, 1, &enemy1);
		if(GetTime() - stateCoreSeconds >= 0.25f) animation(3, &player, 4, &enemy1);
		animation1(2, &bullet);		

		if (GetTime() - stateCoreSeconds >= 4) 
		{
			bRestart = true;
			currentState = LEVEL;
		}
	}

}//updateCore 

void drawCoreScreen(void)
{
	//Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
	DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);

	DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
	DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);

	if(coregameplay == draw) DrawTextEx(alagard, GAME_NAME, posDraw, alagard.baseSize * 2, 1, WHITE);

	if(coregameplay == win) 
	{
		if(GetTime() - stateCoreSeconds <= 0.25f) DrawTexturePro(bulletTexture, bullet.source, bullet.dest, origin, rotation, WHITE);	
	}
	if(coregameplay == lose)
	{
		if(GetTime() - stateCoreSeconds <= 0.25f) DrawTexturePro(bulletTexture, bullet.source, bullet.dest, origin, rotation, WHITE);
	}
}

int finishCore(void)
{
	return finishstate;
}


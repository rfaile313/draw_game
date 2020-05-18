#include <raylib.h>
#include "r_types.h"
#include "logic.h"

const  u16 titlePosX = 280;
const  u16 titlePosY = 150;
const  u16 titleSize  = 100;

static u16 playPosX = 310;
static u16 playPosY = 300;
static u16 playSize  = 50;

static u16 optionsPosX = 310;
static u16 optionsPosY = 350;
static u16 optionsSize = 50;

static u16 arrowPosX = 250;
static u16 arrowPosY = 300;
static u16 arrowSize = 50;

static u16 testPosX  = 180;
static u16 testPosY  = 550;
static u16 testSize  = 20; 

const_str fontPlay    = "Play";
const_str fontOptions = "Options";
const_str fontArrow   = "->";
const_str fontTest    = "(C)Rudy Faile 2020 - test build, not ready for production.";

enum selection {
none,
options,
play
};

enum selection choice = 0;

void updateTitleScreen(void)
{
    
	if(IsKeyPressed(KEY_DOWN))
	{
        arrowPosY += 50;
        if(arrowPosY >= 350)arrowPosY = 350;
    }
    if(IsKeyPressed(KEY_UP))
	{
        arrowPosY -= 50;
        if(arrowPosY <= 300) arrowPosY = 300;
    }
    if(IsKeyPressed(KEY_SPACE))
	{
        //TODO: add fancy animations
        if (arrowPosY == 300) choice = 2; //play
        else if (arrowPosY == 350) choice = 1; //options
        else choice = 0;
    }
}

void drawTitleScreen(void)
{
    DrawText(GAME_NAME, titlePosX, titlePosY, titleSize, WHITE);
    DrawText(fontPlay, playPosX, playPosY, playSize, WHITE);
    DrawText(fontOptions, optionsPosX, optionsPosY, optionsSize, WHITE);
    DrawText(fontArrow, arrowPosX, arrowPosY, arrowSize, WHITE);
	DrawText(fontTest, testPosX, testPosY, testSize, WHITE);        
}

int titleScreenFinished(void)
{
    return choice;
}

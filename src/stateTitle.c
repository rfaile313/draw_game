#include <raylib.h>
#include "r_types.h"
#include "logic.h"

static u16 titlePosX = 310;
static u16 titlePosY = 150;
static u16 titleSize  = 100;

static u16 playPosX = 310;
static u16 playPosY = 300;
static u16 playSize  = 50;

static u16 optionsPosX = 310;
static u16 optionsPosY = 350;
static u16 optionsSize = 50;

static u16 arrowPosX = 250;
static u16 arrowPosY = 300;
static u16 arrowSize  = 50;

const_str fontPlay    = "Play";
const_str fontOptions = "Options";
const_str fontArrow   = "->";

enum selection {
none,
play,
options,
};

enum selection choice = 0;

void updateTitleScreen(void){
    //TODO: add options
    if(IsKeyPressed(KEY_DOWN)){
        arrowPosY += 50;
        if(arrowPosY >= 350)arrowPosY = 350;
    }
    if(IsKeyPressed(KEY_UP)){
        arrowPosY -= 50;
        if(arrowPosY <= 300) arrowPosY = 300;
    }
    if(IsKeyPressed(KEY_SPACE)){
        //TODO: add fancy animations
        if (arrowPosY == 300) choice = 1;
        else if (arrowPosY == 350) choice = 2;
        else choice = 0;
    }
}

void drawTitleScreen(void){
    DrawText(GAME_NAME, titlePosX, titlePosY, titleSize, WHITE);
    DrawText(fontPlay, playPosX, playPosY, playSize, WHITE);
    DrawText(fontOptions, optionsPosX, optionsPosY, optionsSize, WHITE);
    DrawText(fontArrow, arrowPosX, arrowPosY, arrowSize, WHITE);         
}

int titleScreenFinished(void){
    return choice;
}
#ifndef LOGIC_H
#define LOGIC_H

#include <raylib.h>
#include "r_types.h"

// Types and structure def
// ----------------------
// Controls Game State
typedef enum GameState {
TITLE = 0,
LEVEL,
CORE,
SHOOT,
WIN,
LOSE,
END
}GameState;

GameState currentState;

typedef struct Tile{
    Rectangle source;
    Rectangle dest;
}Tile;

//init player and set to default tile  (20x20 px rects) (160x100)
Tile player = {0};
//init first enemy and set to default tile  (20x20 px rects) (160x100) negative source width to flip X
Tile enemy1 = {0};

//---->types and structure def 

// Global variables------>
const_str GAME_NAME = "DRAW!";
const_str LEVEL_1 = "Level 1";

const u16 GAME_SCREEN_WIDTH  = 960;
const u16 GAME_SCREEN_HEIGHT = 572;

const u32 FPS = 60;
const u32 BASESPEED = 4; //60 FPS, every x count (4==15)

const f32 PRSW = 20.0f; //20px RECTANGLE SOURCE WIDTH
const f32 PRSH = 20.0f; //20px RECTANGLE SOURCE HEIGHT

const f32 PRDW = 100.0f; //100px RECTANGLE DEST WIDTH
const f32 PRDH = 100.0f; //100px RECTANGLE DEST HEIGHT

const f32 ENEMY_DIFFICULTY = 1.05f;
const f32 DIFFICULTY_MULTIPLIER = 1.05f;

//TODO: NEED TO REFACTOR THESE -- SHITTY

f64 seconds = 0;
u16 i;

Vector2 origin = {0,0};
Vector2 playerPos = {100,100};
f32 rotation = 0.0f;

//level x text positioning
Vector2 posLevel = {300, 225};
//draw! text positioning
Vector2 posDraw =  {325, 225};

bool initSfxPlayed  = false;
bool drawSfxPlayed  = false;
bool shootSfxPlayed = false;
bool loseSfxPlayed  = false;
//--->end global variables

//resources----->
//load resources
Sound fxInitial;
Sound fxDraw;
Sound fxShoot;
Sound fxLose;     

Texture2D charTexture;
Texture2D tileTexture;

Font alagard;

//--->resources

//tile.c function defs
void modifyTile(Tile *individual_tile, f32 sX, f32 sY, f32 dX, f32 dY,
				f32 srcW, f32 srcH, f32 destW, f32 destH);

//animation.c function defs
void animation(int state,  Tile *animation,
               int eState, Tile *eAnimation);

//bools.c function defs
void changeBool(bool *change, int set);
bool checkAgainst(f64 scnds, int checkAgainst);
void playSoundOnce(Sound snd, bool *change);

//stateTitle.c function defs
void updateTitleScreen(void);
void drawTitleScreen(void);
int titleScreenFinished(void);

//stateCore.c function defs 
void initCore(void);
void updateCore(void);
void drawCoreScreen(void);
int finishCore(void);

#endif // LOGIC_H
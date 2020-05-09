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
//init first enemy idle (comes from different sheet)
Tile enemy1idle = {0};

//---->types and structure def 

// Global variables------>
u16 currentLevel = 1;

const_str GAME_NAME = "DRAW!";

const u16 GAME_SCREEN_WIDTH  = 960;
const u16 GAME_SCREEN_HEIGHT = 572;

const u32 FPS = 60;
const u32 BASESPEED = 4; //60 FPS, every x count (4==15)

const f32 TWENTY = 20.0f; //20.0f Float
const f32 ONE_HUNDRED = 100.0f; //100.0f Float


f32 ENEMY_DIFFICULTY = 1.05f;
f32 DIFFICULTY_MULTIPLIER = 1.05f;

// Spare counter variable
u16 i;

//stateLevel.c initLevel() variables
u16 nextScreen;
u16 check;
u32 stateLevelCounter;
f64 timePassed;

//animation.c variables (also get reset in initLevel)
u32 animationCounter;
u32 fastestAnimationCounter;

enum AnimationState{
reset = 0,
shoot,
stand,
dieframe1,
dieframe2,
taunt1,
taunt2,
spingun
};
enum AnimationState enemystate;
enum AnimationState playerstate;
//--->end animation.c variables

//stateCore.c variables
f64 stateCoreSeconds;

//required DrawTexturePro() variables
Vector2 origin = {0,0};
f32 rotation = 0.0f;
//-->DrawTexturePro()

//"Level X" Text Positioning on Screen
Vector2 posLevel = {300, 225};
//"Draw!" Text Positioning on Screen
Vector2 posDraw =  {325, 225};
//--->end global variables

//resources----->
Sound fxBullet;
Sound fxDraw;
Sound fxError;
Sound fxInitial;
Sound fxLose;
Sound fxLoseWdl;
Sound fxOrgan;
Sound fxShoot;
Sound fxWin;

Texture2D charTexture;
Texture2D tileTexture;
Texture2D enemy1IdleTexture;

Font alagard;
//--->resources

//tile.c function defs
void modifyTile(Tile *individual_tile, f32 sX, f32 sY, f32 dX, f32 dY,
				f32 srcW, f32 srcH, f32 destW, f32 destH);

//animation.c function defs
void animation(int state,  Tile *animation,
               int eState, Tile *eAnimation);

//stateTitle.c function defs
void updateTitleScreen(void);
void drawTitleScreen(void);
int titleScreenFinished(void);

//stateLevel.c function defs
void initLevel(void);
void updateLevelScreen(void);
void drawLevelScreen(void);
int levelScreenFinished(void);

//stateCore.c function defs 
void initCore(void);
void updateCore(void);
void drawCoreScreen(void);
int finishCore(void);

#endif // LOGIC_H
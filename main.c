#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "r_types.h"

#define FPS 60
#define BASESPEED 4 // //60 FPS, every x count (4==15)

u32 frameCounter = 0;
u16 i;
u8  dCounter = 0;
u8  eCounter = 0;
f64 seconds = 0;

typedef struct Tile{
    Rectangle source;
    Rectangle dest;
}Tile;

Vector2 origin = {0,0};
Vector2 playerPos = {100,100};
float rotation = 0.0f;



void modifyTile(Tile *individual_tile, float sX, float sY, float dX, float dY,
				float srcW, float srcH, float destW, float destH)
// Modify tile struct values directly
{
    individual_tile->source.x = sX;
    individual_tile->source.y = sY;
    individual_tile->source.width =  srcW;
    individual_tile->source.height = srcH;
    
    individual_tile->dest.x = dX;
    individual_tile->dest.y = dY;
    individual_tile->dest.width =  destW;
    individual_tile->dest.height = destH;
}


void animation(int state,  Tile *animation, 
               int eState, Tile *eAnimation){
    
    if(FPS/frameCounter == BASESPEED) //60 FPS, every x count (4==15)
    {  
        frameCounter = 0;
        if(state == 0) //idle
        {
            animation->source.y = 0;
            animation->source.x += 20;
            if(animation->source.x >= 60) animation->source.x = 0;
        }
        if(state==1) //draw gun
        {
            animation->source.y = 40;
            animation->source.x += 20;
            if(animation->source.x >= 60) animation->source.x = 0;
        }
        if(state==2)//shoot gun
        {
        }
        if(state==3)//spin gun
        {
            animation->source.y = 60;
            animation->source.x -= 20;
            if(animation->source.x < 0) animation->source.x = 60;
        }
        if(state==4)
        {
            if(dCounter==0)
            {
                animation->source.y = 40;
                animation->source.x = 40;
                dCounter++;
                
            }
            //dieframe1
            else if (dCounter==1)
            {
                
                animation->source.y = 80;
                animation->source.x = 0;
                dCounter++;
                
            }
            //dieframe2
            else if (dCounter==2)
            {
                animation->source.y = 80;
                animation->source.x = 20;
                
            }
            
        }
        
        //enemy animations
        if (eState == 0) //spin gun enemy idle
        {
            eAnimation->source.y = 60;
            eAnimation->source.x -= 20;
            if(eAnimation->source.x < 80) eAnimation->source.x = 120;
        }
        
        if (eState == 1) //something else using eCounter
        {
            if (eCounter == 0)
            {
                eAnimation->source.x = 80;
                eAnimation->source.y = 0;
                eCounter++;
            }
            else if (eCounter == 1)
            {
                eAnimation->source.x = 80;
                eAnimation->source.y = 20;
                eCounter = 0;
            }
            
        }
    }
}

/*
void modifyBool(float currentSeconds, int checkAgainst, bool bool){
    if (currentSeconds >= checkAgainst) bool = true;
}
*/


//note change = !change for swap without int: h/t anata :) 
void changeBool(bool *change, int set){
	bool *tmp = change;
	if (!set) *tmp = false;
	if ( set) *tmp = true;
}

bool checkAgainst(double scnds, int checkAgainst){
    if ((int)scnds >= checkAgainst) return true;
    else return false;
}

int main(void)
{
    // Initialization
    //----------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 572;
    
    const float PRSW = 20.0f; //20px RECTANGLE SOURCE WIDTH
    const float PRSH = 20.0f; //20px RECTANGLE SOURCE HEIGHT
    
    const float PRDW = 100.0f; //100px RECTANGLE DEST WIDTH
    const float PRDH = 100.0f; //100px RECTANGLE DEST HEIGHT
    
    //removed raylib output unless there's a warning -- h/t skytrias!
    SetTraceLogLevel(LOG_WARNING);
    //Init window
    InitWindow(screenWidth, screenHeight, "Draw!");
    //init comes before texture, loading calls (OpenGL context required)
    Texture2D charTexture = LoadTexture("C:\\raylib\\draw_game\\assets\\cowboyspenzilla\\characters.png"); //128/4 x 256/8
    Texture2D tileTexture = LoadTexture("C:\\raylib\\draw_game\\assets\\cowboyspenzilla\\background.png");
    Font alagard = LoadFont("C:\\raylib\\draw_game\\assets\\spritefont\\custom_alagard.png");
    Vector2 fLevelInfo = {300, 225};
    const char fDRAW[6] = "DRAW!";
    char level1[10] = "Level 1";
    
    bool bDRAW = false;

    //format: all floats -- source x, y, w, h // dest x, y, w, h
    //init player and set to default tile  (20x20 px rects) (160x100)
    Tile player = {0};
    //init first enemy and set to default tile  (20x20 px rects) (160x100) negative source width to flip X
    Tile enemy1 = {0};
    
    modifyTile(&player, 0.0f, 0.0f, 200.0f, 300.0f, PRSW, PRSH,  PRDW, PRDH);

    modifyTile(&enemy1, 120.0f, 60.0f, 600.0f, 300.0f, -PRSW, PRSH,  PRDW, PRDH);

    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update---------------->
        //player anim/control
        frameCounter++;

        //stores seconds from time initWindow is called/ float value
        seconds = GetTime(); 
    
        //default anim
        animation(0, &player, 0, &enemy1);
        
        if(checkAgainst(seconds, 6)) bDRAW = true;

        //------------->Update
        //--------------------------
        //Draw---------->
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
        DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);
        
        DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
        
        DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
        
        if(!bDRAW){
            if( (int)seconds % 2 == 0){
                //TODO: size and spacing are floats, should fix. 
                DrawTextEx(alagard, level1, fLevelInfo, alagard.baseSize * 2, 1, WHITE);
            }
        }    
        
        DrawText(TextFormat("%02.02f Seconds", seconds), 50, 50, 40, LIME);
        //%1.02f for two digit places i.e. 1.02 seconds
        //-end draw
        EndDrawing();
        //-------------->Draw
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(charTexture);
    UnloadTexture(tileTexture);
    UnloadFont(alagard);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}

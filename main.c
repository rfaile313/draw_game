#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "r_types.h"

#define FPS 60
#define BASESPEED 4 // //60 FPS, every x count (4==15)

u32 frameCounter = 0;
u32 frameCounter1 = 0;
u8  dCounter = 0;
u8  eCounter = 0;
f64 seconds = 0;
u16 i;

typedef struct Tile{
    Rectangle source;
    Rectangle dest;
}Tile;

Vector2 origin = {0,0};
Vector2 playerPos = {100,100};
f32 rotation = 0.0f;


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
            animation->source.x = 0;
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
        
        if (eState == 1) //point gun
        {
            eAnimation->source.x = 80;
            eAnimation->source.y = 40;
            
        }
        if(eState == 2) //something else using eCounter
        {
            if (eCounter == 0)
            {
                eAnimation->source.x = 80;
                eAnimation->source.y = 40;
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


//note change = !change for swap without int: h/t anata :)
void changeBool(bool *change, int set){
	bool *tmp = change;
	if (!set) *tmp = false;
	if ( set) *tmp = true;
}

bool checkAgainst(double scnds, int checkAgainst){
    if (scnds >= (double)checkAgainst) return true;
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
    //TODO: change to relative paths and detect change in OS
    Texture2D charTexture = LoadTexture("C:\\raylib\\draw_game\\assets\\cowboyspenzilla\\characters.png"); //128/4 x 256/8
    
    Texture2D tileTexture = LoadTexture("C:\\raylib\\draw_game\\assets\\cowboyspenzilla\\background.png");
    
    Font alagard = LoadFont("C:\\raylib\\draw_game\\assets\\spritefont\\custom_alagard.png");
    
    Vector2 posLevel = {300, 225};
    Vector2 posDraw =  {325, 225};
    
    const char tDRAW[6] = "DRAW!";
    
    char tLevel1[10] = "Level 1";
    
    bool bDRAW = false;
    
    //format: all floats -- source x, y, w, h // dest x, y, w, h
    //init player and set to default tile  (20x20 px rects) (160x100)
    Tile player = {0};
    //init first enemy and set to default tile  (20x20 px rects) (160x100) negative source width to flip X
    Tile enemy1 = {0};
    
    modifyTile(&player, 0.0f, 0.0f, 200.0f, 300.0f, PRSW, PRSH,  PRDW, PRDH);
    
    modifyTile(&enemy1, 120.0f, 60.0f, 600.0f, 300.0f, -PRSW, PRSH,  PRDW, PRDH);
    
    //NOTE: maybe decrease time from level to draw as difficulty rises?
    int check = GetRandomValue(3,6);
    
    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //Update---------------->
        //player anim/control
        frameCounter++;
        frameCounter1++;
        //stores seconds from time initWindow is called/ float value
        seconds = GetTime();
        
        //default anim
        if(!bDRAW)animation(0, &player, 0, &enemy1);
        if(bDRAW)animation(1, &player, 1, &enemy1);
        
        if(checkAgainst(seconds, check)) bDRAW = true;
        
        //------------->Update
        //--------------------------
        //Draw---------->
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
        DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);
        

        
        //Flash Level
        if(!bDRAW){

        DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
        
        DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);

            //TODO: size and spacing are floats, should fix.
            // 60/x == 2 every 30 frames     60/x == 4 every 15 frames
            if(frameCounter1 >= (60/4) )
            {
                DrawTextEx(alagard, tLevel1, posLevel, alagard.baseSize * 2, 1, WHITE);
                
                if(frameCounter1  >= (60/2))
                {
                    frameCounter1 = 0;
                }
                
            }
        }
        
        //Draw! Text
        if(bDRAW){
            DrawTextEx(alagard, tDRAW, posDraw, alagard.baseSize * 2, 1, WHITE);
            DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
            DrawTexturePro(charTexture, enemy1.source, enemy1.dest, origin, rotation, WHITE);
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

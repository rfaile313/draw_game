#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "r_types.h"

#define FPS 60

// NOTE: mark concept: home, ctrl+space, end, ctrl+c, move ctrl+v
// TODO: set up a smart struct or function to parse tiles.png
// TODO: set up placeholder player animation with timedelta?
// TODO: set up debugger

u32 frameCounter = 0;
u16 i;
u8  dCounter = 0;

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


void playerAnimation(int state, Tile *animation){
    
    if(FPS/frameCounter == 3) //every 20th count
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
        
    }
}




int main(void)
{
    // Initialization
    //----------------------------------------------------------------------------
    const int screenWidth = 960;
    const int screenHeight = 572;
    
    const float PRSW = 20.0f; //PLAYER RECTANGLE SOURCE WIDTH
    const float PRSH = 20.0f; //PLAYER RECTANGLE SOURCE HEIGHT
    
    const float PRDW = 100.0f;
    const float PRDH = 100.0f;
    
    InitWindow(screenWidth, screenHeight, "Draw!");
    //init comes before texture calls
    Texture2D charTexture = LoadTexture("assets/cowboyspenzilla/characters.png"); //128/4 x 256/8
    Texture2D tileTexture = LoadTexture("assets/cowboyspenzilla/background.png");
    
    //Image skyGradient = GenImageGradientV(screenWidth, screenHeight, SKYBLUE, LIGHTGRAY);
    //Texture2D skyTexture = LoadTextureFromImage(
    
    //init player and set to default tile  (20x20 px rects) (160x100)
    Tile player = {.source.x=0.0f, .source.y=0.0f, .source.width=PRSW, .source.height=PRSH,
        .dest.x=200.0f, .dest.y=300.0f, .dest.width=PRDW, .dest.height=PRDH};
    
    //NOTE:(rudy) maybe don't need this?
    /*
    Tile pIdle2 =  {0};
    Tile pIdle3 =  {0};
    Tile pStand =  {0};
    Tile pShoot1 = {0};
    Tile pShoot2 = {0};
    Tile pShoot3 = {0};
    Tile pSpin1 =  {0};
    Tile pSpin2 =  {0};
    Tile pSpin3 =  {0};
    Tile pdie1 =   {0};
    Tile pdie2 =   {0};
    */
    
    //assign
    
    //format: all floats -- source x, y, w, h // dest x, y, w, h
    
    
    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //
        
        //player anim/control
        frameCounter++;
        
        //default anim
        playerAnimation(0, &player);
        
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        //DrawTexture(skyTexture,0,0,WHITE);
        
        //TODO: When all the tiles are built just loop through for the draw
        //DrawTexturePro(tileTexture, bg.source, bg.dest, origin, rotation, WHITE);
        //player
        
        //Background: Texture / 0,0 / 0,0 / 4x scale / WHITE
        DrawTextureEx(tileTexture, origin, rotation, 4.0f, WHITE);
        
        DrawTexturePro(charTexture, player.source, player.dest, origin, rotation, WHITE);
        
        //-end draw
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(charTexture);
    UnloadTexture(tileTexture);
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    
    return 0;
}

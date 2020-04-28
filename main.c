#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "r_types.h"

#define FPS 60

//NOTE: mark concept: home, ctrl+space, end, ctrl+c, move ctrl+v
//TODO: set up a smart struct or function to parse tiles.png
//TODO: set up placeholder player animation with timedelta?
//TODO: timing system/debug text
//TODO: generate art, remove placeholder animations

s32 frameCounter = 0;
s16 i;

struct Tile{
    Rectangle source;
    Rectangle dest;
};


Vector2 origin = {0,0};
Vector2 playerPos = {100,100};

float rotation = 0.0f;

//TODO: get this off the heap
struct Tile *Tile_create(float sX, float sY, float dX, float dY,
                         float srcW, float srcH, float destW, float destH)
{
    struct Tile *individual_tile = malloc(sizeof(struct Tile));
    
    individual_tile->source.x = sX;
    individual_tile->source.y = sY;
    individual_tile->source.width =  srcW;
    individual_tile->source.height = srcH;
    
    individual_tile->dest.x = dX;
    individual_tile->dest.y = dY;
    individual_tile->dest.width =  destW;
    individual_tile->dest.height = destH;
    
    return individual_tile;
}

void Destroy_tile(struct Tile *individual_tile){
    free(individual_tile);
}

void playerAnimation(int state, struct Tile *animation){
    
    if(FPS/frameCounter == 3)
    {
        frameCounter = 0;
        if(state == 0) //idle
        {
            animation->source.x += 32;
            animation->source.y = 0;
            if(animation->source.x >= 128) animation->source.x = 0;
        }
        if(state==1) //draw gun
        {
            animation->source.y = 32;
            animation->source.x += 32;
            if(animation->source.x >= 96) animation->source.x = 0;
        }
        if(state==2)//shoot gun
        {
        }
        if(state==3)//put gun away
        {
        }
        if(state==4)//die
        {
        }
    }
}



int main(void)
{
    // Initialization
    //----------------------------------------------------------------------------
    const int screenWidth = 700;
    const int screenHeight = 500;
    
    InitWindow(screenWidth, screenHeight, "Draw!");
    //init comes before texture calls
    Texture2D charTexture = LoadTexture("assets/cowboysdara/cowboys.png"); //128/4 x 256/8
    Texture2D tileTexture = LoadTexture("assets/tiles.png");
    
    Image skyGradient = GenImageGradientV(screenWidth, screenHeight, SKYBLUE, LIGHTGRAY);
    Texture2D skyTexture = LoadTextureFromImage(skyGradient);
    
    
    //tileset
    struct Tile *bg1 = Tile_create(192.0f,528.0f, //initial src
                                   192.0f, 300.0f, //initial dest
                                   96.0f, 192.0f, //srcw, srch
                                   112.0f, 224.0f); //destw/desth
    
    struct Tile *bg2 = Tile_create(192.0f,528.0f, //initial src
                                   384.0f,300.0f, //initial dest
                                   96.0f, 192.0f, //srcw, srch
                                   112.0f, 224.0f); //destw/desth
    
    //player idle
    struct Tile *player = Tile_create(0.0f, 0.0f, //0,0 initialsrc
                                      192.0f, 268.0f, // initial dest
                                      32.0f, 32.0f,  // src w/h
                                      96.0f, 96.0f); // dest w/h
    
    
    //
    
    SetTargetFPS(FPS);               // Set our game to run at 60 frames-per-second
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        //
        
        //player anim/control
        frameCounter++;
        
        //default anim
        playerAnimation(0, player);
        
        
        BeginDrawing();
        
        ClearBackground(BLACK);
        
        DrawTexture(skyTexture,0,0,WHITE);
        
        //TODO: When all the tiles are built just loop through for the draw
        DrawTexturePro(tileTexture, bg1->source, bg1->dest, origin, rotation, WHITE);
        DrawTexturePro(tileTexture, bg2->source, bg2->dest, origin, rotation, WHITE);
        //player
        
        DrawTexturePro(charTexture, player->source , player->dest, origin, rotation, WHITE);
        
        //-end draw
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(charTexture);
    UnloadTexture(tileTexture);
    Destroy_tile(player);
    Destroy_tile(bg1);
    Destroy_tile(bg2);
    CloseWindow();        // Close window and OpenGL context
    
    //--------------------------------------------------------------------------------------
    
    return 0;
}
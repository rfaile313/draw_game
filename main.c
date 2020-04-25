#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

//NOTE: mark concept: home, ctrl+space, end, ctrl+c, move ctrl+v
//TODO: set up a smart struct or function to parse tiles.png
//TODO: set up placeholder player animation with timedelta?
//TODO: timing system/debug text
//TODO: generate art, remove placeholder animations

//const int sourceSize = 32;
//const int destSize = 96;

int i;

struct Tile{
    Rectangle source;
    Rectangle dest;
};

Vector2 origin = {0,0};
float rotation = 0.0f;

struct Tile *Tile_create(float sX, float sY, float dX, float dY)
{
    struct Tile *individual_tile = malloc(sizeof(struct Tile));
    
    individual_tile->source.x = sX;
    individual_tile->source.y = sY;
    individual_tile->source.width =  32.0f;
    individual_tile->source.height = 32.0f;
    
    individual_tile->dest.x = dX;
    individual_tile->dest.y = dY;
    individual_tile->dest.width =  96.0f;
    individual_tile->dest.height = 96.0f;
    
    return individual_tile;
}

void Destroy_tile(struct Tile *individual_tile){
    free(individual_tile);
}

int main(void)
{
    // Initialization
    //----------------------------------------------------------------------------
    //screen size
    const int screenWidth = 800;
    const int screenHeight = 650;
    
    InitWindow(screenWidth, screenHeight, "Draw!");
    // NOTE:(rudy) Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D charTexture = LoadTexture("assets/chars.png");
    Texture2D tileTexture = LoadTexture("assets/tiles.png");
    
    //TODO: need a better way to do this
    //bottom left sand tile blst
    struct Tile *blst = Tile_create(192.0f,588.0f, //192, 588 src
                                    96.0f, 300.0f); //96, 300 dest
    //bottom middle sand tile
    //TODO: make more for platform wideness
    struct Tile *bmst = Tile_create(224.0f,588.0f, //224, 588
                                    192.0f, 300.0f); //192, 300 dest
    
    //bottom right sand tile
    struct Tile *brst = Tile_create(256.0f,588.0f, //256, 588
                                    288.0f, 300.0f); //288, 300 dest
	
    Vector2 playerPos = {200.0f, 200.0f};
    Rectangle pCurrentFrame = {128.0f, 0.0f, (float)charTexture.width/32,
                                           (float)charTexture.height/16};

    int frameCounter = 0;
    int frameSpeed = 4;
	
    
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //---> end initialization-----------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------    
        //player anim/control
        
        frameCounter++;
        if (frameCounter >= (60/frameSpeed)){
            frameCounter = 0;
            pCurrentFrame.x += 16;
            if (pCurrentFrame.x > 352) pCurrentFrame.x = 256;
    
        }
        
        
        // end update--------------------------------------------------------------
        
        // Draw
        //-------------------------------------------------------------------------
        
		BeginDrawing();
        
        ClearBackground(BLACK);
        
        //TODO: When all the tiles are built just loop through for the draw
        DrawTexturePro(tileTexture, blst->source, blst->dest, origin, rotation, WHITE);
        DrawTexturePro(tileTexture, bmst->source, bmst->dest, origin, rotation, WHITE);
        DrawTexturePro(tileTexture, brst->source, brst->dest, origin, rotation, WHITE);

        DrawTextureRec(charTexture, pCurrentFrame, playerPos, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    
    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(charTexture);
    UnloadTexture(tileTexture);
    Destroy_tile(blst);
    CloseWindow();        // Close window and OpenGL context
    
    //--------------------------------------------------------------------------------------
    
    return 0;
}

// only external dependency
#include <raylib.h>
// headers
#include "src/r_types.h" 
#include "src/logic.h"
// unity build 
#include "src/animation.c"
#include "src/resources.c"
#include "src/stateTitle.c"
#include "src/stateOptions.c"
#include "src/stateLevel.c"
#include "src/stateCore.c"

// uncomment the below line to compile for web
//#define PLATFORM_WEB

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif
// --- Program entry point
int main(void)
{
	// Initialization------>
	const u16 screenWidth = GAME_SCREEN_WIDTH;
	const u16 screenHeight = GAME_SCREEN_HEIGHT;

	//removed raylib output unless there's a warning -- h/t skytrias!
	SetTraceLogLevel(LOG_WARNING);
	//init window - must come before texture, loading calls (OpenGL context required)
	InitWindow(screenWidth, screenHeight, GAME_NAME);
	//set window icon
	Image icon = LoadImage("Resources/icon/windowicon.png");
	SetWindowIcon(icon);
	//this should only reset on new game or if called directly
	modifyTile(&xAnim, 0.0f, 0.0f, 140.0f, 250.0f, 64.0f, 64.0f, 192.0f, 192.0f);
	// Initialize audio device (required for sound)
	InitAudioDevice();

	//load resources--->
	fxBullet  = LoadSound(soundBullet);
	fxDraw    = LoadSound(soundDraw);
	fxError   = LoadSound(soundError);
	fxInitial = LoadSound(soundInitial);
	fxLose    = LoadSound(soundLose);
	fxLoseWdl = LoadSound(soundLoseWdl);
	fxOrgan   = LoadSound(soundOrgan); 
	fxShoot   = LoadSound(soundShoot);
	fxWin     = LoadSound(soundWin);
	fxToggle  = LoadSound(soundToggle);	

	charTexture = LoadTexture(charTexturePath); //128/4 x 256/8
	tileTexture = LoadTexture(tileTexturePath);
	enemy1IdleTexture = LoadTexture(enemy1IdleTexturePath);
	xAnimationTexture = LoadTexture(xAnimationTexturePath);
	bulletTexture = LoadTexture(bulletTexturePath);	

	alagard = LoadFont(fontAlagard);
	//-->end resource load

	// Default difficulty is Normal unless set otherwise
	ENEMY_DIFFICULTY = DIFF_NORMAL;

	//set the starting state
	currentState = TITLE;
	
	//High Score
	bestScore = LoadStorageValue(STORAGE_POSITION_HISCORE);
	bestTime = LoadStorageValue(STORAGE_POSITION_BESTSPEED);
			
	
	//Set game to run at 60 frames-per-second
	SetTargetFPS(FPS);
	//---> end initialization------
	
	// Main game loop

	

	#if defined(PLATFORM_WEB)
	// Web, Obvs
	    emscripten_set_main_loop(UpdateDrawFrame, 0, 1);

	#else
	// Win/Linux/MacOS
		while (!WindowShouldClose())    // Detect window close button or ESC key
		{
			UpdateDrawFrame();
		}
	#endif
	

	// De-Initialization
	// Unload Resources
	UnloadImage(icon); 
	UnloadTexture(charTexture);
	UnloadTexture(tileTexture);
	UnloadTexture(enemy1IdleTexture);
	UnloadTexture(xAnimationTexture);
	UnloadTexture(bulletTexture);
	UnloadSound(fxInitial);
	UnloadSound(fxDraw);
	UnloadSound(fxShoot);
	UnloadSound(fxLose);
	UnloadSound(fxOrgan);
	UnloadSound(fxLoseWdl);
	UnloadSound(fxError);
	UnloadSound(fxBullet);
	UnloadSound(fxWin);
	UnloadFont(alagard);
	// Close audio
	CloseAudioDevice(); 
	// Close window and OpenGL context
	CloseWindow();        

	return 0;

}

void UpdateDrawFrame(void)
	{
		//Update---------------->
		switch(currentState)
		{
			case TITLE:
				{
					updateTitleScreen();

					if(titleScreenFinished() == 1) //1 = options
					{
						arrowPosX = 250; //set arrow to 'back' on options screen
						arrowPosY = 200; // ""
						currentState = OPTIONS;	
					}
					if(titleScreenFinished() == 2) //2 = next screen
					{
						choice = 0; //resets titleScreenFinished()
						initLevel(); //function in stateTitle.c: resets variables from logic.h
						currentState = LEVEL; 
					}

				}break;
			case OPTIONS:
				{
					updateOptionsScreen();

					if(titleScreenFinished() == 0)
					{
						currentState = TITLE;
					}

				}break;
			case LEVEL:
				{
					if (earlystatus == warning)
					{
						initLevel();
						earlystatus = restart;      
					}
					if (bRestart)
					{
						initLevel();
						bRestart = false;
					}

					updateLevelScreen();
					if (levelScreenFinished() == 1)
					{
						nextScreen = 0; //resets levelScreenFinished()
						initCore();
						currentState = CORE;
					}

				}break;
			case CORE: 
				{
					updateCore();
					if(finishCore() == 1)
					{
						finishstate = 0;
						currentState = TITLE;
					}
				}break;
			default: break;
		}//switch 
		//------------->Update

		//Draw---------->
		BeginDrawing();

		//required
		ClearBackground(BLACK);

		switch(currentState)
		{
			case TITLE:
				{
					drawTitleScreen();
				}break;
			case OPTIONS:
				{
					drawOptionsScreen();				
				}break;
			case LEVEL:
				{
					drawLevelScreen();
				}break;
			case CORE:
				{
					drawCoreScreen();
				}break;
			default: break;
		}

		//EndDrawing() (Required)
		EndDrawing();
		//-------------->Draw

	} //-->UpdateDrawFrame

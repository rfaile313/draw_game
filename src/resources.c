#include "logic.h"
#include "r_types.h"
#include <raylib.h>

//TODO add unix paths

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

    const_str charTexturePath = "C:\\raylib\\draw_game\\assets\\cowboyspenzilla\\characters.png"; //128/4 x 256/8
    const_str tileTexturePath = "C:\\raylib\\draw_game\\assets\\cowboyspenzilla\\background.png";

    
    const_str soundInitial = "C:\\raylib\\draw_game\\assets\\sound\\initial.ogg";
    const_str soundDraw    = "C:\\raylib\\draw_game\\assets\\sound\\draw.ogg";
    const_str soundShoot   = "C:\\raylib\\draw_game\\assets\\sound\\shoot.ogg";
    const_str soundLose    = "C:\\raylib\\draw_game\\assets\\sound\\lose.ogg";

    const_str fontAlagard  ="C:\\raylib\\draw_game\\assets\\spritefont\\custom_alagard.png";

#elif __APPLE__
	//not sure what this is V
	// #include <TargetConditionals.h>
	
    const_str charTexturePath = "/Users/RFaile/gamedev/draw_game/assets/cowboyspenzilla/characters.png";
    const_str tileTexturePath = "/Users/RFaile/gamedev/draw_game/assets/cowboyspenzilla/background.png";

    const_str soundInitial = "/Users/RFaile/gamedev/draw_game/assets/sound/initial.ogg";
    const_str soundDraw    = "/Users/RFaile/gamedev/draw_game/assets/sound/raw.ogg";
    const_str soundShoot   = "/Users/RFaile/gamedev/draw_game/assets/sound/shoot.ogg";
    const_str soundLose    = "/Users/RFaile/gamedev/draw_game/assets/sound/lose.ogg";

    const_str fontAlagard  ="/Users/RFaile/gamedev/draw_game/assets/spritefont/custom_alagard.png";

    #if TARGET_IPHONE_SIMULATOR
         // iOS Simulator
    #elif TARGET_OS_IPHONE
        // iOS device
    #elif TARGET_OS_MAC
        // Other kinds of Mac OS
    #else
    
	#endif
#elif __linux__
    // linux
#elif __unix__ // all unices not caught above
    // Unix
#elif defined(_POSIX_VERSION)
    // POSIX
#else
#   error "Unknown compiler"
#endif

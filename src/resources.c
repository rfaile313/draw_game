#include "logic.h"
#include "r_types.h"

//not sure I need variations on unity build...
//think i can just define straight up

const_str charTexturePath = "Resources/cowboyspenzilla/characters.png"; //128/4 x 256/8
const_str tileTexturePath = "Resources/cowboyspenzilla/background.png";

const_str enemy1IdleTexturePath = "Resources/cowboyspenzilla/enemy1idle.png";
const_str xAnimationTexturePath = "Resources/rudy/xanimation.png";
const_str bulletTexturePath = "Resources/rudy/bullet.png";

const_str soundBullet  = "Resources/sound/bullet.ogg";
const_str soundDraw    = "Resources/sound/draw.ogg";
const_str soundError   = "Resources/sound/error.ogg";
const_str soundInitial = "Resources/sound/initial.ogg";
const_str soundLose    = "Resources/sound/lose.ogg";
const_str soundLoseWdl = "Resources/sound/losewithdelay.ogg";
const_str soundOrgan   = "Resources/sound/organ.ogg";
const_str soundShoot   = "Resources/sound/shoot.ogg";
const_str soundWin     = "Resources/sound/win.ogg";
const_str soundToggle  = "Resources/sound/togglesound.ogg";	

const_str fontAlagard  = "Resources/spritefont/custom_alagard.png";

/*
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)

const_str charTexturePath = "Resources/cowboyspenzilla/characters.png"; //128/4 x 256/8
const_str tileTexturePath = "Resources/cowboyspenzilla/background.png";

const_str enemy1IdleTexturePath = "Resources/cowboyspenzilla/enemy1idle.png";
const_str xAnimationTexturePath = "Resources/rudy/xanimation.png";
const_str bulletTexturePath = "Resources/rudy/bullet.png";

const_str soundBullet  = "Resources/sound/bullet.ogg";
const_str soundDraw    = "Resources/sound/draw.ogg";
const_str soundError   = "Resources/sound/error.ogg";
const_str soundInitial = "Resources/sound/initial.ogg";
const_str soundLose    = "Resources/sound/lose.ogg";
const_str soundLoseWdl = "Resources/sound/losewithdelay.ogg";
const_str soundOrgan   = "Resources/sound/organ.ogg";
const_str soundShoot   = "Resources/sound/shoot.ogg";
const_str soundWin     = "Resources/sound/win.ogg";
const_str soundToggle  = "Resources/sound/togglesound.ogg";	

const_str fontAlagard  = "Resources/spritefont/custom_alagard.png";

#elif __APPLE__
//not sure what this is V
// #include <TargetConditionals.h>

const_str charTexturePath = "../Resources/cowboyspenzilla/characters.png"; //128/4 x 256/8
const_str tileTexturePath = "../Resources/cowboyspenzilla/background.png";

const_str enemy1IdleTexturePath = "../Resources/cowboyspenzilla/enemy1idle.png";
const_str xAnimationTexturePath = "../Resources/rudy/xanimation.png";
const_str bulletTexturePath = "../Resources/rudy/bullet.png";

const_str soundBullet  = "../Resources/sound/bullet.ogg";
const_str soundDraw    = "../Resources/sound/draw.ogg";
const_str soundError   = "../Resources/sound/error.ogg";
const_str soundInitial = "../Resources/sound/initial.ogg";
const_str soundLose    = "../Resources/sound/lose.ogg";
const_str soundLoseWdl = "../Resources/sound/losewithdelay.ogg";
const_str soundOrgan   = "../Resources/sound/organ.ogg";
const_str soundShoot   = "../Resources/sound/shoot.ogg";
const_str soundWin     = "../Resources/sound/win.ogg";
const_str soundToggle  = "../Resources/sound/togglesound.ogg";	

const_str fontAlagard  = "../Resources/spritefont/custom_alagard.png";

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

*/

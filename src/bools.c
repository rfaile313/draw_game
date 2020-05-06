#include "logic.h"
#include "r_types.h"

//note change = !change for swap without int: h/t anata :)
//TODO: function to set all bools to default values
//actually probably get rid of this bullshit ^^

void changeBool(bool *change, int set){
	bool *tmp = change;
	if (!set) *tmp = false;
	if ( set) *tmp = true;
}

bool checkAgainst(f64 scnds, int checkAgainst){
    if (scnds >= (f64)checkAgainst) return true;
    else return false;
}

void playSoundOnce(Sound snd, bool *change){
    bool *tmp = change;
    if (!*tmp){
    PlaySound(snd);
    *tmp = true;
    }
}


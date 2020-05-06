#include "logic.h"
#include "r_types.h"

//todo: probably should refactor this shitty ass function

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
        if (eState == 2){ //shoot gun
            eAnimation->source.y = 40;
            eAnimation->source.x += 20;
            if (eAnimation->source.x >= 100) eAnimation->source.x = 100; 
        }
        if (eState == 3) //something else using eCounter
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
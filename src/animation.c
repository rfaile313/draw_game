#include "logic.h"
#include "r_types.h"

//todo: probably should refactor this shitty ass function!!

void animation(int state,  Tile *animation,
               int eState, Tile *eAnimation)
{
    animationCounter++;
    fastestAnimationCounter++;

    if(FPS/animationCounter == 4) //60 FPS, every x count (4==15)
    {
        animationCounter = 0;
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

        if(state==3)//player spin gun
        {
            animation->source.y = 60;
            animation->source.x -= 20;
            if(animation->source.x < 0) animation->source.x = 60;
        }
        if(state==4)//death
        {
            if(playerstate==reset)
            {
                animation->source.y = 40;
                animation->source.x = 40;
                playerstate=dieframe1;
                
            }
            //dieframe1
            else if (playerstate==dieframe1)
            {
                
                animation->source.y = 80;
                animation->source.x = 0;
                playerstate=dieframe2;
                
            }
            //dieframe2
            else if (playerstate==dieframe2)
            {
                animation->source.y = 80;
                animation->source.x = 20;
            }
            
        }
        
        //enemy animations
        if (eState == 0) //spin gun enemy
        {
            eAnimation->source.y = 60;
            eAnimation->source.x -= 20;
            if(eAnimation->source.x < 80) eAnimation->source.x = 120;
        }
        
        if (eState == 1) //point gun enemy
        {
            eAnimation->source.x = 80;
            eAnimation->source.y = 40;
            
        }
        if (eState == 2){ //draw gun enemy
            eAnimation->source.y = 40;
            eAnimation->source.x += 20;
            if (eAnimation->source.x >= 100) eAnimation->source.x = 100; 
        }
        if (eState == 3){ //shoot gun enemy
            if(enemystate == shoot)
            {
            eAnimation->source.y = 40;
            eAnimation->source.x += 20;
                if (eAnimation->source.x >= 120)
                {
                    enemystate = taunt1;
                    eAnimation->source.x = 80;
                    eAnimation->source.y = 0; 
                }
            }
           
        }

        if (eState == 5) //new idle
        {
            eAnimation->source.y = 0;
            eAnimation->source.x += 100;
            if(eAnimation->source.x >= 2000) eAnimation->source.x = 0;
        }
        if (eState == 6) //taunt enemy
        {
            if(enemystate == taunt1)
            {
            enemystate = taunt2;
            eAnimation->source.y = 0;
            eAnimation->source.x = 80;
            }
            else if (enemystate == taunt2)
            {
            enemystate = taunt1;
            eAnimation->source.y = 20;
            eAnimation->source.x = 80;
            }
           
        }
       
    } //--->if(FPS/animationCounter == 4)

    if(FPS/fastestAnimationCounter == 15) //60 FPS, every 4 count
    {
        fastestAnimationCounter = 0;
        if (eState == 4) //die enemy
        { 
            if(enemystate != dieframe1){
            eAnimation->source.y = 80;
            eAnimation->dest.x += 20;
            }
            if (eAnimation->dest.x >= 700 )
            {
            enemystate = dieframe1;
            eAnimation->source.x += 20;
            if (eAnimation->source.x >= 100) eAnimation->source.x = 100;
            }
        }
        
        if(state==2)//shoot gun, then spin?
        {
            if (playerstate != spingun){
            animation->source.y = 40;
            animation->source.x += 20;
            if(animation->source.x >= 40) playerstate = spingun;
            }
            if (playerstate == spingun)
            {
            animation->source.y = 60;
            animation->source.x -= 20;
            if(animation->source.x < 0) animation->source.x = 60;   
            }
        }
    }//fastestAnimationCounter

}//animation parent function
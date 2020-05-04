#include <stdio.h>
#include <stdlib.h>

float float_rand( float min, float max )
{
    float scale = rand() / (float) RAND_MAX; /* [0, 1.0] */
    return min + scale * ( max - min );      /* [min, max] */
}

int main(void){
int i;

for(i=0;i<100;i++){
printf("Random float = %f \n", float_rand(float_rand(1.0f,1.5f), float_rand(2.5f, 3.0f)));
}

return 0;
}

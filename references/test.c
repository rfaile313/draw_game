#include <stdio.h>

typedef struct Rectangle{
float x;
float y;
float width;
float height;
}Rectangle;

typedef struct Tile{
Rectangle source;
Rectangle dest;
}Tile;

int main(void){
	
	Tile player = {.source.x = 1.0f, .source.y = 2.0f, .source.width = 3.0f, .source.height = 4.0f,
.dest.x = 5.0f, .dest.y = 6.0f, .dest.width = 7.0f, .dest.height = 8.0f};

	printf("%f",player.source.x);
	printf("test complete");
	return 0;
}

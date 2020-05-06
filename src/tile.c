#include "logic.h"
#include "r_types.h"

void modifyTile(Tile *individual_tile, f32 sX, f32 sY, f32 dX, f32 dY,
				f32 srcW, f32 srcH, f32 destW, f32 destH)
// Modify tile struct values directly
{
    individual_tile->source.x = sX;
    individual_tile->source.y = sY;
    individual_tile->source.width =  srcW;
    individual_tile->source.height = srcH;
    
    individual_tile->dest.x = dX;
    individual_tile->dest.y = dY;
    individual_tile->dest.width =  destW;
    individual_tile->dest.height = destH;
}

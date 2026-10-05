#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridObject {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[5];
    s8 cellsX;
    s8 cellsY;
    s8 cellsZ;
} GridObject;

int BuildFieldObjectCellGrid(GridObject *object, VecFx32 *cells)
{
    VecFx32 origin;
    VecFx32 cursor;
    int y;
    int z;
    int x;
    int count;

    origin.x = object->position.x - ((object->cellsX * 0x1800) >> 1) + 0xc00;
    origin.z = object->position.z - ((object->cellsZ * 0x1800) >> 1) + 0xc00;
    origin.y = object->position.y;
    cursor = origin;
    count = 0;
    for (z = 0; z < object->cellsZ; z++) {
        cursor.y = origin.y;
        for (y = 0; y < object->cellsY; y++) {
            cursor.x = origin.x;
            for (x = 0; x < object->cellsX; x++) {
                cells[count] = cursor;
                cursor.x += 0x1800;
                count++;
            }
            cursor.y += 0x1800;
        }
        cursor.z += 0x1800;
    }
    return count;
}

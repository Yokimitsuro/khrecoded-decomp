#include "nitro/types.h"

typedef struct ShapeVertex {
    s32 x;
    s32 y;
    s32 z;
} ShapeVertex;

typedef struct CollisionShape {
    u8 pad_00[0x12];
    u16 vertexCount;
    u8 pad_14[0x3c];
    ShapeVertex vertices[1];
} CollisionShape;

typedef struct HeightBounds {
    u8 pad_00[4];
    s32 min;
    u8 pad_08[8];
    s32 max;
} HeightBounds;

BOOL OverlapsHeightRange(CollisionShape *shape, HeightBounds *bounds) {
    s32 high = shape->vertices[0].y;
    s32 low;
    u8 i = 1;
    u8 count = shape->vertexCount;
    low = high;

    for (; i < count; i++) {
        s32 y = shape->vertices[i].y;
        if (high < y) {
            high = y;
        } else if (low > y) {
            low = y;
        }
    }
    if (bounds->max > high || bounds->min < low) {
        return FALSE;
    } else {
        return TRUE;
    }
}

#include "nitro/types.h"

typedef struct ScreenPoint {
    int x;
    int y;
} ScreenPoint;

u32 GetScreenQuadrantFlags(ScreenPoint *point) {
    u32 flags = 0;

    if (point->x < 0x80) {
        flags |= 1;
    } else {
        flags |= 6;
    }
    if (point->y < 0x80) {
        flags |= 8;
    }
    return flags;
}

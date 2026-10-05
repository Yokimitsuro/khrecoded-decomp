#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x2a];
    s16 counter;
} MovieContext;

extern MovieContext *data_ov035_020bc500;
extern int ReadSessionPackedBits(int bitOffset, int bitCount);
extern int GetMovieCounterLimit(int which);
extern void StoreMovieCounter(int which, int value);

int LoadMovieCounter(int which)
{
    int value;

    if (which == 0) {
        value = data_ov035_020bc500->counter;
    } else {
        value = ReadSessionPackedBits(which == 1 ? 0x3703 : 0x3713, 0x10);
    }
    if (GetMovieCounterLimit(which) < value) {
        value = GetMovieCounterLimit(which);
        StoreMovieCounter(which, value);
    }
    return value;
}
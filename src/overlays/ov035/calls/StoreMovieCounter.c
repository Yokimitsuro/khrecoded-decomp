#include "nitro/types.h"

typedef struct MovieContext {
    u8 pad_00[0x2a];
    s16 counter;
} MovieContext;

extern MovieContext *data_ov035_020bc500;
extern int GetMovieCounterLimit(int which);
extern void WriteSessionPackedBits(int bitIndex, int bitCount, int value);

void StoreMovieCounter(int which, int value)
{
    if (GetMovieCounterLimit(which) < value) {
        value = GetMovieCounterLimit(which);
    }
    if (which == 0) {
        data_ov035_020bc500->counter = value;
    } else {
        WriteSessionPackedBits(which == 1 ? 0x3703 : 0x3713, 0x10, value);
    }
}
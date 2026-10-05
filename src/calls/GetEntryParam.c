#include "nitro/types.h"

typedef struct ParamEntry {
    int value;
    int extra[2];
} ParamEntry;

extern ParamEntry data_02060f1c[];

int GetEntryParam(u32 index)
{
    int result;
    u32 slot;

    if (index >= 49) {
        result = -1;
    } else {
        slot = index + 1;
        result = data_02060f1c[slot].value;
    }
    return result;
}

#include "nitro/types.h"

typedef struct FieldCounters {
    u8 pad_00[0x68];
    int values[3];
} FieldCounters;

typedef struct FieldState {
    u8 pad_0000[0x2740];
    FieldCounters counters;
} FieldState;

extern FieldState *data_ov001_020a0480;

void ClearFieldCounters(void)
{
    FieldCounters *counters = &data_ov001_020a0480->counters;
    int i;

    for (i = 0; i < 3; i++) {
        counters->values[i] = 0;
    }
}

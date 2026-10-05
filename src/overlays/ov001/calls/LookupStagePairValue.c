#include "nitro/types.h"

typedef struct {
    u16 key;
    u16 value;
} Pair;

typedef struct {
    u8 pad_00[8];
    Pair pairs[0x40];
    u8 count;
} StageData;

extern StageData *data_ov001_020a0490;

int LookupStagePairValue(u32 key) {
    StageData *data = data_ov001_020a0490;
    int i = 0;
    while (i < data->count) {
        if (key == data->pairs[i].key) {
            if (data->pairs[i].value != 0) {
                return data->pairs[i].value;
            }
            return -1;
        }
        i++;
    }
    return -1;
}

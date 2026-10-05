#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 pad_02[2];
    u8 count;
    u8 maxCount;
    u8 pad_06[6];
} StackSlot;

typedef struct {
    s16 id;
    u8 pad_02[2];
    u8 count;
} StackRequest;

extern StackSlot data_020608e0[8];

static inline int ClampCount(int value, int maxValue)
{
    if (value > maxValue) {
        return maxValue;
    }
    if (value < 0) {
        value = 0;
    }
    return value;
}

int AddToStackSlot(const StackRequest *request)
{
    int slot = -1;
    int i;

    for (i = 0; i < 8; i++) {
        if (request->id == data_020608e0[i].id) {
            data_020608e0[i].count += request->count;
            slot = i;
            break;
        }
        if (data_020608e0[i].id == -1 && slot == -1) {
            slot = i;
        }
    }
    if (i == 8 && slot >= 0) {
        data_020608e0[slot].id = request->id;
        data_020608e0[slot].count = ClampCount(request->count + data_020608e0[slot].count, data_020608e0[slot].maxCount);
    }
    return slot;
}

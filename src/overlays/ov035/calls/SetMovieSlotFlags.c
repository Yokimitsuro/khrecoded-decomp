#include "nitro/types.h"

typedef struct MovieSlot {
    u8 unk_00;
    u8 flags;
    u8 pad_02[2];
} MovieSlot;

typedef struct MovieScene {
    u8 pad_000[0x10a];
    s8 slotCount;
    u8 pad_10b;
    MovieSlot *slots;
} MovieScene;

extern MovieScene *data_ov035_020bc504;

void SetMovieSlotFlags(int index, u8 flags)
{
    MovieScene *scene = data_ov035_020bc504;
    int i = 0;
    int end;

    if (index >= 0) {
        i = index;
    }
    if (index < 0) {
        end = scene->slotCount;
    } else {
        end = index + 1;
    }
    for (; i < end; i++) {
        scene->slots[i].flags = flags;
    }
}
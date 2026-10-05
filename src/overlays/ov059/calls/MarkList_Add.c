#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Mark {
    fx32 time;
    s32 kind;
    VecFx32 position;
} Mark;

typedef struct MarkList {
    u8 pad_000[0x40];
    Mark *marks;
    u8 pad_044[0x354 - 0x44];
    u8 clock[1];
} MarkList;

extern fx32 func_0202f4cc(void *player, int arg);

void MarkList_Add(MarkList *list, s32 markKind, VecFx32 *position) {
    int i;

    if (markKind == 3) {
        fx32 now = func_0202f4cc(list->clock, 0);
        int nearby = 0;
        Mark *marks = list->marks;
        for (i = 0; i < 10; i++) {
            Mark *mark = &marks[i];
            if (now - mark->time >= 0xb000 && mark->kind == 3) {
                fx32 dy = position->y - mark->position.y;
                fx32 dx = position->x - mark->position.x;
                if ((fx32)(((s64)dx * dx + (s64)dy * dy) >> 12) < 0x400) {
                    if (++nearby >= 3) {
                        return;
                    }
                }
            }
        }
    }
    for (i = 0; i < 10; i++) {
        if (list->marks[i].time == -1) {
            list->marks[i].time = 0;
            list->marks[i].kind = markKind;
            list->marks[i].position = *position;
            return;
        }
    }
}

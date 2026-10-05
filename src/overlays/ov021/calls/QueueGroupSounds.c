#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    int seqArcNo;
} SoundItem;

typedef struct {
    SoundItem **items;
    int count;
} SoundGroup;

extern void QueueSoundCommandForArc(int seqArcNo);

void QueueGroupSounds(SoundGroup *group) {
    int i;

    for (i = 0; i < group->count; i++) {
        SoundItem *item = group->items[i];

        if (item != NULL && item->seqArcNo >= 0) {
            QueueSoundCommandForArc(item->seqArcNo);
        }
    }
}

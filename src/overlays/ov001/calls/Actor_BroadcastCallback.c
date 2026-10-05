#include "nitro/types.h"

typedef struct ActorWithCallback {
    u8 pad_000[0x10ec];
    void (*callback)(void *self, int arg);
} ActorWithCallback;

extern int func_ov001_0206dc38(void);
extern ActorWithCallback *GetBoundedEntryField(int index);
extern void FinishEnemyRecovery(void);

u32 Actor_BroadcastCallback(void)
{
    int index;
    int count;
    ActorWithCallback *actor;

    index = 1;
    count = func_ov001_0206dc38();
    if (1 < count) {
        do {
            actor = GetBoundedEntryField(index);
            FinishEnemyRecovery();
            actor->callback(actor, 1);
            index = index + 1;
            count = func_ov001_0206dc38();
        } while (index < count);
    }
    return 1;
}

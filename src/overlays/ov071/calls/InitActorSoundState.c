#include "nitro/types.h"

typedef struct ByteSlots {
    u32 slot0 : 8;
    u32 slot1 : 8;
    u32 slot2 : 8;
    u32 slot3 : 8;
} ByteSlots;

typedef struct ActorSoundState {
    u8 pad00[0x70];
    int field70;
    u8 pad74[4];
    int field78;
    u8 pad7c[4];
    ByteSlots soundSlots;
    u8 pad84[4];
    ByteSlots slots88;
    ByteSlots slots8c;
} ActorSoundState;

extern u32 GetBoundedEntryField(int index);
extern void func_ov071_020d838c(void);

int InitActorSoundState(int self, ActorSoundState *actor, int *outSize)
{
    u64 *flags = (u64 *)(GetBoundedEntryField(*(int *)(self + 0x14)) + 0x9ac);

    *flags |= 0x40;
    *outSize = 0x18;
    *flags |= 0x20000000;
    actor->field70 = 0;
    actor->field78 = 0;
    actor->soundSlots.slot0 = 0xff;
    actor->soundSlots.slot1 = 0xff;
    actor->soundSlots.slot2 = 0xff;
    actor->soundSlots.slot3 = 0xff;
    actor->slots88.slot2 = 0;
    actor->slots88.slot1 = 0;
    actor->slots88.slot3 = 0;
    actor->slots8c.slot0 = 0;
    actor->slots8c.slot1 = 0;
    return (int)func_ov071_020d838c;
}

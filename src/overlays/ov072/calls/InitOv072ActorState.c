#include "nitro/types.h"

typedef struct {
    u32 slot0 : 8;
    u32 slot1 : 8;
    u32 slot2 : 6;
    u32 flagA : 1;
    u32 flagB : 1;
    u32 slot3 : 8;
} SoundSlots;

typedef struct {
    u32 byte0 : 8;
    u32 byte1 : 8;
    u32 byte2 : 8;
    u32 byte3 : 8;
} ByteSlots;

typedef struct {
    u8 pad_00[0x68];
    int field68;
    u8 pad_6c[0x18];
    SoundSlots sounds;
    ByteSlots counters;
} ActorState;

extern u32 GetBoundedEntryField(int index);
extern u8 func_ov001_02068084(void);
extern int func_ov001_02067ed4(void);
extern void func_ov072_020d8548(void);

int InitOv072ActorState(int self, ActorState *actor, int *outSize)
{
    u64 *flags = (u64 *)(GetBoundedEntryField(*(int *)(self + 0x14)) + 0x9ac);

    *flags |= 0x40;
    *outSize = 0x18;
    *flags |= 0x20000000;
    actor->field68 = 0;
    actor->sounds.slot0 = 0xff;
    actor->sounds.slot1 = 0xff;
    actor->sounds.slot2 = 0x3f;
    actor->sounds.slot3 = 0;
    actor->counters.byte0 = 0;
    actor->counters.byte1 = 0;
    actor->counters.byte2 = 0;
    actor->counters.byte3 = 0;
    actor->sounds.flagA = 0;
    actor->sounds.flagB = 1;
    if (func_ov001_02068084() == 2 && func_ov001_02067ed4() == 1) {
        actor->sounds.flagB = 0;
    }
    return (int)func_ov072_020d8548;
}

#include "nitro/types.h"

typedef struct AnimBlendSet {
    u8 data[0x104];
} AnimBlendSet;

typedef struct AnimFileIds {
    u32 ids[4];
} AnimFileIds;

typedef struct Actor {
    u8 pad_0000[0x1700];
    AnimBlendSet *animBank;
} Actor;

extern const AnimFileIds data_ov059_020cfe8c;
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern u32 func_ov001_0206dba0(int kind);
extern u8 *SND_RegisterSeq(u32 fileId, int kind);
extern void *func_0202c4a0(u32 fileId, int kind);
extern void func_0202edb0(AnimBlendSet *set, u8 *record, void *block, int flag);
extern void func_ov059_020c8b9c(void *state);

void Actor_LoadJointBlendSets(Actor *actor, void *animReset) {
    AnimFileIds files;
    void *block;
    u8 *record;
    u32 fileId;
    int i;

    actor->animBank = NNSi_FndAllocFromDefaultHeap(sizeof(AnimBlendSet) * 4);
    i = 0;
    files = data_ov059_020cfe8c;
    for (; i < 4; i++) {
        fileId = files.ids[i];
        block = NULL;
        record = SND_RegisterSeq(
            0x80000000 | (((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7) | (fileId & 0x1ff), 8);
        if (*(u16 *)(record + 2) == 0) {
            block = func_0202c4a0(
                0x80000000 | (((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7) | ((fileId + 1) & 0x1ff), 0x11);
        }
        func_0202edb0(&actor->animBank[i], record, block, 8);
        if (block != NULL) {
            NNSi_FndFreeFromDefaultHeap(block);
        }
    }
    func_ov059_020c8b9c(animReset);
}

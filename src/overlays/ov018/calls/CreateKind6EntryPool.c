#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind6EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
    u8 pad_5b[0x79];
    int unk_d4;
    u8 pad_d8[0x100];
    int unk_1d8;
} Kind6EntryPool;

extern Kind6EntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void LoadKind6ObjectPhase(void);
extern void func_ov018_020a31b4(void);
extern void func_ov018_020a2234(void);
extern void func_ov018_020a2260(void);
extern void func_ov018_020a22bc(void);
extern void GetActorVelocity_020a2660(void);
extern void FieldObject_TryCollideWithVolume(void);
extern void GetRaisedTargetPosition(void);
extern void func_ov018_020a31b0(void);
extern void func_ov018_020a2220(void);
extern void func_ov018_020a269c(void);

Kind6EntryPool *CreateKind6EntryPool(int count)
{
    Kind6EntryPool *pool = CreateEntryPool(0x474, 0xbc, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = LoadKind6ObjectPhase;
    pool->callbacks[1] = func_ov018_020a31b4;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = func_ov018_020a2234;
    pool->callbacks[5] = func_ov018_020a2260;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov018_020a22bc;
    pool->callbacks[8] = GetActorVelocity_020a2660;
    pool->callbacks[9] = FieldObject_TryCollideWithVolume;
    pool->callbacks[10] = GetRaisedTargetPosition;
    pool->callbacks[3] = func_ov018_020a31b0;
    pool->callbacks[12] = func_ov018_020a2220;
    pool->callbacks[14] = func_ov018_020a269c;
    pool->kind = 6;
    pool->unk_d4 = 0;
    pool->unk_1d8 = 0;
    return pool;
}

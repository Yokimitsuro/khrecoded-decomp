#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind4EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
    u8 pad_5B[0x89];
    void *messageHead;
    u8 pad_E8[0xdc];
    void *pool0;
    void *pool1;
    void *pool2;
    void *pool3;
    void *pool4;
    u8 pad_1D8[0x14];
    void *pendingList;
} Kind4EntryPool;

extern Kind4EntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void ResetPoolDefaultParams(Kind4EntryPool *pool);
extern void LoadTriggerObjectPhase(void);
extern void LinkObjectChainTail(void);
extern void func_ov017_020a2e84(void);
extern void ReleaseFieldObjectResources(void);
extern void func_ov017_020a2f28(void);
extern void GetActorVelocity(void);
extern void CollideFieldObjectActor(void);
extern void GetOwnerRaisedPosition(void);
extern void func_ov017_020a3964(void);
extern void IsState1Or2(void);
extern void DrawFieldObjectEffects(void);

Kind4EntryPool *CreateKind4EntryPool(int count)
{
    Kind4EntryPool *pool = CreateEntryPool(0x1f0, 0x84, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = LoadTriggerObjectPhase;
    pool->callbacks[1] = LinkObjectChainTail;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = func_ov017_020a2e84;
    pool->callbacks[5] = ReleaseFieldObjectResources;
    pool->callbacks[6] = NULL;
    pool->callbacks[7] = func_ov017_020a2f28;
    pool->callbacks[8] = GetActorVelocity;
    pool->callbacks[9] = CollideFieldObjectActor;
    pool->callbacks[10] = GetOwnerRaisedPosition;
    pool->callbacks[3] = func_ov017_020a3964;
    pool->callbacks[12] = IsState1Or2;
    pool->callbacks[14] = DrawFieldObjectEffects;
    pool->kind = 4;
    ResetPoolDefaultParams(pool);
    pool->pool0 = NULL;
    pool->pool1 = NULL;
    pool->pool2 = NULL;
    pool->pool3 = NULL;
    pool->pool4 = NULL;
    pool->messageHead = NULL;
    pool->pendingList = NULL;
    return pool;
}

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef void (*PoolCallback)(void);

typedef struct Kind5EntryPool {
    PoolCallback callbacks[16];
    u8 pad_40[4];
    fx32 range;
    int active;
    VecFx32 extent;
    u8 mode;
    u8 pad_59;
    u8 kind;
    u8 pad_5b[5];
    int owner;
    s16 groupId;
    u8 pad_66[2];
    void *resource;
} Kind5EntryPool;

extern Kind5EntryPool *CreateEntryPool(int headerSize, int entrySize, int count);
extern void HandleLinkEvent(void);
extern void func_ov019_020a31c0(void);
extern void ReleaseOwnerResources(void);
extern void GetObjectPositionIfValid(void);
extern void func_ov019_020a2794(void);
extern void TryGetExtraDataHandle(void);
extern void TryCollideWithCollider(void);
extern void GetRaisedFocusPoint(void);
extern void ApplyDerivedIdState(void);
extern void IsDestroyed(void);
extern void SnapshotLinkStates(void);
extern void DrawActorModel(void);

Kind5EntryPool *CreateKind5EntryPool(int count, int unused, int owner)
{
    Kind5EntryPool *pool = CreateEntryPool(0x6c, 0x78, count);

    pool->active = 0;
    pool->mode = 3;
    pool->extent.x = 0x1800;
    pool->extent.y = 0x1800;
    pool->extent.z = 0x1800;
    pool->range = 0x3000;
    pool->callbacks[0] = HandleLinkEvent;
    pool->callbacks[1] = func_ov019_020a31c0;
    pool->callbacks[2] = NULL;
    pool->callbacks[4] = ReleaseOwnerResources;
    pool->callbacks[5] = NULL;
    pool->callbacks[6] = NULL;
    pool->callbacks[11] = GetObjectPositionIfValid;
    pool->callbacks[7] = func_ov019_020a2794;
    pool->callbacks[8] = TryGetExtraDataHandle;
    pool->callbacks[9] = TryCollideWithCollider;
    pool->callbacks[10] = GetRaisedFocusPoint;
    pool->callbacks[3] = ApplyDerivedIdState;
    pool->callbacks[12] = IsDestroyed;
    pool->callbacks[13] = SnapshotLinkStates;
    pool->callbacks[14] = DrawActorModel;
    pool->kind = 5;
    pool->owner = owner;
    pool->groupId = -1;
    pool->resource = NULL;
    return pool;
}

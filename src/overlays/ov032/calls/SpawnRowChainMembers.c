#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ChainWork {
    s16 state;
    u8 pad_02[2];
    s16 prevActor;
    s16 nextActor;
    u32 flags;
    u8 pad_0C[0x18];
    VecFx32 velocity;
    u8 pad_30[4];
    MtxFx33 rotation;
} ChainWork;

typedef struct ChainObject {
    u8 pad_00[0x33];
    u8 actorId;
    u8 pad_34[4];
    VecFx32 position;
} ChainObject;

typedef struct ChainRow {
    u32 firstMember : 9;
    u32 unk_00_9 : 9;
    u32 behavior : 5;
    u32 unk_00_23 : 9;
    u32 mode : 4;
    u32 unk_04_4 : 12;
    u32 spawnedCount : 8;
    u32 unk_04_24 : 8;
    u8 pad_08[4];
    u16 memberCount : 8;
    u16 unk_0C_8 : 8;
    u8 pad_0E[2];
    u16 spawnTimer;
    u8 pad_12[0x1ce];
} ChainRow;

typedef struct ChainWorld {
    u8 pad_00[0xcc];
    ChainRow *rows;
} ChainWorld;

extern const VecFx32 data_0205344c;
extern const MtxFx33 data_02053458;

extern s32 func_ov032_020bbc38(ChainWorld *world, s32 rowIndex);
extern ChainWork *func_ov032_020bbc98(ChainObject *object);
extern ChainObject *func_ov001_02086384(ChainWorld *world, int index);
extern BOOL IsNodeFlagBitClear(ChainObject *object);
extern void func_ov032_020bc208(ChainObject *object, int behavior);
extern void ResetUnitToBasePosition(ChainObject *object);
extern void func_ov016_020a6974(ChainObject *object, void (*callback)(ChainObject *self));
extern void SetFieldUnitPosition(ChainObject *object, const VecFx32 *position);
extern void func_ov032_020bbd80(ChainObject *object, const VecFx32 *velocity);
extern void UnlinkGroupMember(ChainObject *self);

void SpawnRowChainMembers(ChainWorld *world, s32 rowIndex, ChainObject *origin)
{
    ChainRow *row = &world->rows[rowIndex];
    ChainWork *work;
    u16 prevActor;
    ChainObject *tail;
    ChainObject *next;
    ChainWork *childWork;
    int i;

    if (row->spawnTimer < func_ov032_020bbc38(world, rowIndex)) {
        return;
    }
    work = func_ov032_020bbc98(origin);
    prevActor = origin->actorId;
    tail = origin;
    do {
        if (work->nextActor != -1) {
            next = func_ov001_02086384(world, work->nextActor);
        } else {
            next = NULL;
        }
        if (next != NULL) {
            prevActor = next->actorId;
            work = func_ov032_020bbc98(next);
            tail = next;
        }
    } while (next != NULL);

    for (i = 0; i < row->memberCount; i++) {
        next = func_ov001_02086384(world, row->firstMember + i);
        if (!IsNodeFlagBitClear(next)) {
            childWork = func_ov032_020bbc98(next);
            row->spawnedCount++;
            childWork->prevActor = prevActor;
            childWork->nextActor = -1;
            childWork->state = work->state;
            childWork->rotation = data_02053458;
            childWork->velocity = data_0205344c;
            childWork->flags |= 0x2000;
            func_ov032_020bc208(next, row->behavior);
            ResetUnitToBasePosition(next);
            func_ov016_020a6974(next, UnlinkGroupMember);
            if (row->mode != 3) {
                SetFieldUnitPosition(next, &origin->position);
            } else {
                SetFieldUnitPosition(next, &tail->position);
            }
            func_ov032_020bbd80(next, &data_0205344c);
            work->nextActor = next->actorId;
            prevActor = next->actorId;
            work = childWork;
            tail = next;
        }
    }
    row->spawnTimer = 0;
}

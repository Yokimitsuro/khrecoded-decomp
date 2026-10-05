#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkedActor {
    u8 pad_00[0x10];
    u32 kind;
} LinkedActor;

typedef struct WallLinks {
    u8 pad_00[0x80];
    u8 actorIds[4];
} WallLinks;

typedef struct TriggerWall {
    WallLinks *links;
    int type;
    int unk_08;
} TriggerWall;

typedef struct TriggerWallSet {
    TriggerWall entries[16];
    VecFx32 normals[16];
    u8 count;
} TriggerWallSet;

typedef struct FieldPlayer FieldPlayer;

struct FieldPlayer {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x154];
    u32 (*getStatus)(FieldPlayer *player);
    u8 pad_220[0x04];
    VecFx32 *(*getPosition)(FieldPlayer *player);
    u8 pad_228[0x0c];
    u32 flags;
    u8 pad_238[0x10c];
    TriggerWallSet walls;
    u8 pad_4c8[0x4ec];
    u8 controllerIndex;
};

typedef struct TargetLock {
    LinkedActor *target;
    u64 lockTick;
    u32 lockedKind;
} TargetLock;

extern const s16 data_02053580[];

extern void *func_ov001_0206db78(u8 index);
extern BOOL func_ov021_020a7524(void *controller);
extern int func_ov021_020a7564(void *controller);
extern LinkedActor *GetWorldMeshNamedEntry(u8 actorId);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern BOOL func_ov001_020681e8(LinkedActor *actor, u32 kind);
extern u64 OS_GetTick(void);
extern VecFx32 *func_ov052_020ceb74(FieldPlayer *player);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void SpawnTrailEffect(TargetLock *lock, VecFx32 *pos, VecFx32 *normal);

BOOL UpdateTriggerWallContact(FieldPlayer *player, TargetLock *lock)
{
    int i;
    BOOL locked = FALSE;
    BOOL pushed = FALSE;
    TriggerWallSet *walls;
    void *controller;
    int angleIndex;
    int j;
    LinkedActor *actor;
    VecFx32 facing;
    VecFx32 normal;
    VecFx32 pos;

    if (lock->lockedKind != 0) {
        return FALSE;
    }
    if (!(player->flags & 2)) {
        return FALSE;
    }
    if (((player->getStatus != NULL) ? player->getStatus(player) : 0) & 4) {
        return FALSE;
    }
    controller = func_ov001_0206db78(player->controllerIndex);
    if (!func_ov021_020a7524(controller)) {
        return FALSE;
    }
    angleIndex = func_ov021_020a7564(controller) >> 4;
    facing.x = -data_02053580[angleIndex];
    facing.z = -data_02053580[(0x400 - angleIndex) & 0xfff];

    walls = &player->walls;
    for (i = 0; i < walls->count; i++) {
        TriggerWall *entry = &walls->entries[i];
        if (entry->type != 2) {
            continue;
        }
        for (j = 0; j < 4; j++) {
            actor = GetWorldMeshNamedEntry(entry->links->actorIds[j]);
            if (actor == NULL) {
                continue;
            }
            if (VEC_DotProduct(&walls->normals[i], &facing) > 0) {
                continue;
            }
            if (j == 0) {
                if (!func_ov001_020681e8(actor, 1)) {
                    continue;
                }
                if (lock->target == NULL) {
                    lock->target = actor;
                    lock->lockTick = OS_GetTick();
                    locked = TRUE;
                } else if (lock->target == actor) {
                    locked = TRUE;
                }
            } else {
                if (!func_ov001_020681e8(actor, 6)) {
                    continue;
                }
                normal = walls->normals[i];
                VEC_MultAdd(-0x900, &normal, func_ov052_020ceb74(player), &pos);
                pushed = TRUE;
            }
        }
    }

    if (locked) {
        if (OS_GetTick() >= lock->lockTick + 0xcc8d) {
            lock->lockedKind = lock->target->kind;
        }
    } else if (pushed) {
        VecFx32 *origin = (player->getPosition != NULL) ? player->getPosition(player) : &player->position;
        pos.y = origin->y;
        SpawnTrailEffect(lock, &pos, &normal);
    }
    return locked;
}

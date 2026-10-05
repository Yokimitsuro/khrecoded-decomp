#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0x14];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x10];
    s32 markerIndex;
} MarkerConfig;

typedef struct {
    u8 pad_00[0x14];
    VecFx32 target;
} SubModeView;

typedef struct {
    fx32 minX;
    fx32 maxX;
    fx32 maxY;
    fx32 minY;
} ViewBounds;

typedef struct {
    u8 pad_00[2];
    u16 lives;
} ActorStats;

typedef struct EscapeActor EscapeActor;
typedef void (*ActorCallback)(EscapeActor *actor, int value);

struct EscapeActor {
    u8 pad_000[0x1d4];
    ActorStats *stats;
    u8 pad_1d8[0x200 - 0x1d8];
    ActorCallback onEscape;
    u8 pad_204[0x210 - 0x204];
    ActorCallback onFlash;
    u8 pad_214[0x9ac - 0x214];
    u64 flags;
    u8 entryId;
    u8 pad_9b5[0xa00 - 0x9b5];
    VecFx32 homePos;
    u8 pad_a0c[0x10ec - 0xa0c];
    ActorCallback setState;
    u8 pad_10f0[0x1108 - 0x10f0];
    u8 hitState[4];
};

extern MarkerConfig gMarkerReset;
extern VecFx32 *func_ov052_020ceb74(EscapeActor *actor);
extern SubModeView *func_ov021_020af614(void);
extern ViewBounds *func_ov042_020bd5b0(void);
extern BOOL func_ov001_020645c8(int flagId);
extern void func_ov021_020ab85c(void *obj);
extern void ActorSlot_UnlinkByIndex(int index);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);
extern fx32 func_ov021_020a7670(EscapeActor *actor, fx32 value);
extern BOOL AddClampedHealth(EscapeActor *actor, int delta);
extern MarkerConfig data_ov030_020bd024;
extern void func_ov030_020bb488(MarkerConfig *config);
extern void func_ov001_02078800(int id);

BOOL CheckCarriedActorEscape(EscapeActor *actor)
{
    VecFx32 spawnPos;
    MarkerRequest request;
    VecFx32 *pos = func_ov052_020ceb74(actor);
    SubModeView *view = func_ov021_020af614();
    ViewBounds *bounds = func_ov042_020bd5b0();
    BOOL escaped;
    fx32 damage;

    escaped = FALSE;
    spawnPos = actor->homePos;
    if (actor->stats->lives == 0 || func_ov001_020645c8(0x3625)) {
        return FALSE;
    }
    if (pos->y <= view->target.y + bounds->minY - 0x3000 && !func_ov001_020645c8(0x3ee3)) {
        spawnPos.y = view->target.y + bounds->minY;
        escaped = TRUE;
    } else if (view->target.x + (bounds->maxX + 0x1800) < pos->x) {
        spawnPos.x = view->target.x + bounds->maxX;
        escaped = TRUE;
    } else if (view->target.x + (bounds->minX - 0x1800) > pos->x) {
        spawnPos.x = view->target.x + bounds->minX;
        escaped = TRUE;
    }
    if (escaped) {
        func_ov021_020ab85c(actor->hitState);
        ActorSlot_UnlinkByIndex(actor->entryId);
        ResetAnimationTrackState(&request);
        request.id = actor->entryId;
        request.unk_25 = 0;
        request.unk_24 = 0;
        request.prevIndex = data_ov030_020bd024.markerIndex;
        request.index = 0;
        request.pos = spawnPos;
        request.pos.z += 0x1000;
        func_ov021_020a8cc0(&request, func_ov001_0206db8c(6));
        damage = func_ov021_020a7670(actor, 0x14000);
        if (damage < 0x1000) {
            damage = 0x1000;
        }
        AddClampedHealth(actor, (s16)-(damage >> 12));
        if (actor->stats->lives == 0) {
            return escaped;
        }
        func_ov030_020bb488(&gMarkerReset);
        actor->flags |= 0x20000;
        actor->flags |= 0x40000;
        func_ov001_02078800(-1);
        if (actor->onEscape != NULL) {
            actor->onEscape(actor, 0);
        }
        if (actor->onFlash != NULL) {
            actor->onFlash(actor, 0xbffe);
        }
        actor->setState(actor, 0x1d);
    }
    return escaped;
}

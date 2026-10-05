#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[0x24];
    u8 unk_25;
    u8 pad_26[6];
} MarkerRequest;

typedef struct EntryInfo EntryInfo;
struct EntryInfo {
    u8 pad_000[0x94];
    u16 facing;
    u8 pad_096[0xbc - 0x96];
    VecFx32 position;
    u8 pad_0c8[0x1f0 - 0xc8];
    void (*onFire)(EntryInfo *info, int value, int a, int b);
};

typedef struct {
    u8 pad_000[0x3c];
    s8 entryIndex;
    u8 pad_03d[3];
    s8 flags;
    u8 pad_041[3];
    u16 animFlags;
    u8 pad_046[0xc0 - 0x46];
    u16 angle;
    u8 pad_0c2[0xe8 - 0xc2];
    VecFx32 position;
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
    u8 pad_100[0x150 - 0x100];
    u8 tracks[0x184 - 0x150];
    fx32 scale;
    s16 fireValue;
    u8 pad_18a[2];
    fx32 lift;
    s32 delay;
    fx32 radius;
    u8 pad_198[4];
    s32 timer;
    u8 pad_1a0[0x10];
    s32 subState : 16;
    s32 state : 16;
} BlastUnit;

typedef struct {
    MarkerRequest request;
    BlastUnit *owner;
} BlastContext;

extern EntryInfo *GetBoundedEntryField(int index);
extern void RebindAnimTracks_020aef84(u16 *anim, void *tracks, int blend);
extern BOOL StepEffectAnimation(BlastUnit *unit, fx32 step);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern void ForEachRecordInRadius(void *filter, void *visitor, VecFx32 *center, fx32 radius, void *userData);
extern void IsRecordAliveAndUnflagged(void);
extern void ApplyScaledPathHit(void);

void UpdateDelayedBlastEffect(BlastUnit *unit, fx32 step)
{
    VecFx32 center;
    BlastContext context;
    EntryInfo *info;
    u16 angle;
    u16 facing;
    void (*onFire)(EntryInfo *, int, int, int);
    int fireValue;

    info = GetBoundedEntryField(unit->entryIndex);
    switch (unit->state) {
    default:
        unit->state = 0;
        return;
    case 0:
        return;
    case 1:
        angle = info->facing - 0x8000;
        unit->position = info->position;
        facing = angle + 0x8000;
        unit->angle = facing;
        unit->animFlags |= 0x20;
        unit->scaleX = unit->scaleY = unit->scaleZ = unit->scale;
        RebindAnimTracks_020aef84(&unit->animFlags, unit->tracks, 0);
        unit->flags |= 1;
        unit->timer = 0;
        unit->subState = 1;
        unit->state = 2;
        fireValue = unit->fireValue;
        onFire = info->onFire;
        if (onFire != NULL) {
            onFire(info, fireValue, 0, 0);
        }
    case 2:
        if (StepEffectAnimation(unit, step)) {
            unit->state = 3;
        }
        break;
    case 3:
        unit->state = 4;
    case 4:
        unit->state = 0;
        break;
    }
    switch (unit->subState) {
    case 0:
        break;
    case 1:
        unit->timer += step;
        if (unit->timer >= unit->delay) {
            ResetAnimationTrackState(&context.request);
            context.request.id = unit->entryIndex;
            context.request.unk_25 = 0;
            context.owner = unit;
            center = unit->position;
            center.y += unit->lift;
            ForEachRecordInRadius(IsRecordAliveAndUnflagged, ApplyScaledPathHit, &center, unit->radius, &context);
            unit->subState = 0;
        }
        break;
    }
}

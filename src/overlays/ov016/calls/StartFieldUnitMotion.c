#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 animId;
    u16 nodeIndex;
    fx32 speed;
    fx32 frame;
    fx32 maxFrame;
} AnimTrack;

typedef struct {
    u8 pad_00[0x58];
    AnimTrack motionTrack;
    u8 pad_68[0xc0 - 0x68];
    u32 flags;
} FieldUnit;

extern int GetFieldUnitActionMotion(FieldUnit *unit);
extern void InitAnimTrack(FieldUnit *obj, AnimTrack *track, int nodeIndex, fx32 speed, int animId);

fx32 StartFieldUnitMotion(FieldUnit *unit, fx32 speed, int animId)
{
    if (!(unit->flags & 0x8000)) {
        InitAnimTrack(unit, &unit->motionTrack, GetFieldUnitActionMotion(unit), speed, animId);
        unit->flags |= 0x8000;
    }
    return unit->motionTrack.maxFrame;
}

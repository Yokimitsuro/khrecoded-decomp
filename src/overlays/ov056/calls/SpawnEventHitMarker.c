#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0xc];
    fx32 scaleX;
    fx32 scaleY;
    u8 unk_24;
    u8 style;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x5a];
    u8 isHeavy;
} SourceInfo;

typedef struct {
    u8 pad_00[4];
    SourceInfo *info;
} HitSource;

typedef struct {
    u32 flags;
    u8 pad_04[4];
    s32 kind;
    VecFx32 pos;
    HitSource *source;
} HitEvent;

typedef struct {
    s32 kind;
    u8 pad_04[0x70];
    s16 *groupId;
} MarkerOwner;

typedef struct {
    u8 pad_000[0xd4];
    VecFx32 position;
    u8 pad_0e0[0x150 - 0xe0];
    MarkerOwner *owner;
} HitUnit;

typedef struct {
    u8 pad_000[0xb58];
    s32 markerIndex;
} EntryInfo;

extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern EntryInfo *GetBoundedEntryField(int index);
extern int func_ov001_0206db8c(int kind);

void SpawnEventHitMarker(s32 *entryIndex, HitUnit *unit, HitEvent *event)
{
    MarkerRequest request;
    VecFx32 pos;
    MarkerOwner *owner = unit->owner;
    BOOL spawn = FALSE;
    EntryInfo *info;

    switch (event->kind) {
    case 3:
        if (event->source->info->isHeavy == 1) {
            spawn = TRUE;
        }
        break;
    case 2:
    case 4:
        spawn = TRUE;
        break;
    }
    if (!spawn) {
        return;
    }
    ResetAnimationTrackState(&request);
    request.id = *entryIndex;
    request.style = 0;
    request.unk_24 = 0;
    request.index = -1;
    request.prevIndex = request.index;
    pos = event->pos;
    if (owner->kind == 0x90) {
        info = GetBoundedEntryField(*entryIndex);
        request.prevIndex = info->markerIndex;
        request.index = 2;
        pos = unit->position;
    }
    request.pos = pos;
    if (event->flags & 0x20) {
        request.scaleX = 0x28000;
        request.scaleY = 0x20000;
        request.style = 3;
        func_ov021_020a8cc0(&request, func_ov001_0206db8c(5));
        return;
    }
    if (owner->groupId != NULL) {
        func_ov021_020a8cc0(&request, *owner->groupId);
    }
}

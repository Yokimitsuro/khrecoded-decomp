#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 offset;
    u8 pad_10[2];
    u16 angle;
    s32 color;
    void *anchor;
    u8 pad_1c[8];
    u8 unk_24;
    u8 mode;
    u16 flags;
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u8 pad_000[0x6cc];
    u8 anchor[0x768 - 0x6cc];
    s32 busy;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 markerId;
    u8 pad_9b5[0x9ec - 0x9b5];
    s32 color;
} AuraActor;

typedef struct {
    u8 pad_00[8];
    s32 prevIndex;
    u8 pad_0c[0x4c];
    s32 index;
    s32 startFrame;
    s32 endFrame;
    s32 style;
    u8 pad_68[0x14];
    s16 *groupId;
    u8 pad_80;
    s8 handle;
} AuraMarker;

extern s32 func_ov052_020ceb9c(AuraActor *actor);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern s8 func_ov021_020a8cc0(MarkerRequest *request, int groupId);

void SpawnTimedAuraMarker(AuraMarker *marker, AuraActor *actor, s32 frame)
{
    MarkerRequest request;

    if (marker->handle != -1 || actor->busy != 0 || frame >= marker->endFrame || frame < marker->startFrame) {
        return;
    }
    func_ov052_020ceb9c(actor);
    ResetAnimationTrackState(&request);
    request.id = actor->markerId;
    request.mode = 1;
    request.angle = 0x8000;
    request.color = actor->color;
    if (marker->index >= 0) {
        request.prevIndex = marker->prevIndex;
        request.index = marker->index;
    }
    switch (marker->style) {
    case 1:
        request.flags |= 1;
        request.offset.y = 0x800;
        break;
    case 2:
        request.flags |= 0x11;
        request.angle = 0x3fff;
        break;
    case 3:
        request.offset.x = 0;
        request.offset.y = 0x1666;
        request.offset.z = -0xb33;
        request.flags |= 8;
        request.angle = 0x3fff;
        break;
    case 4:
        request.mode = 2;
        request.angle = 0;
        request.unk_24 = 0;
        request.anchor = actor->anchor;
        break;
    }
    marker->handle = func_ov021_020a8cc0(&request, *marker->groupId);
}

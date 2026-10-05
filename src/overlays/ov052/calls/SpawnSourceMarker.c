#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 pos;
    u8 pad_10[0xc];
    fx32 radius;
    fx32 height;
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} MarkerRequest;

typedef struct {
    u32 flags;
    u8 pad4[8];
    VecFx32 pos;
} MarkerSource;

extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern int func_ov001_0206db8c(int index);

void SpawnSourceMarker(int entity, MarkerSource *source)
{
    MarkerRequest request;
    ResetAnimationTrackState(&request);
    if (*(s16 *)(entity + 0x1100) != -1 && (source->flags & 0x20)) {
        request.id = *(u8 *)(entity + 0x9b4);
        request.unk_25 = 0;
        request.unk_24 = 0;
        request.prevIndex = request.index = -1;
        request.pos = source->pos;
        request.radius = 0x28000;
        request.height = 0x20000;
        request.unk_25 = 3;
        func_ov021_020a8cc0(&request, func_ov001_0206db8c(5));
    }
}

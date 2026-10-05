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

typedef struct SceneActor SceneActor;
typedef VecFx32 *(*PositionGetter)(SceneActor *actor);

struct SceneActor {
    u8 pad_000[0xbc];
    VecFx32 pos;
    u8 pad_0c8[0x224 - 0xc8];
    PositionGetter getPosition;
    u8 pad_228[0x9ac - 0x228];
    u64 flags;
    u8 markerId;
    u8 pad_9b5[0x9c4 - 0x9b5];
    s32 markerSuppressed;
};

typedef struct {
    u8 pad_00[0x10];
    s32 markerIndex;
} MarkerConfig;

extern MarkerConfig gMarkerReset;
extern int func_ov001_0206db8c(int index);
extern BOOL IsGroupMemberActive(int groupId, int member);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);

void SpawnSceneMarker(SceneActor *actor)
{
    MarkerRequest request;
    VecFx32 *pos;
    int groupId;

    if (actor->markerSuppressed == 0) {
        groupId = func_ov001_0206db8c(6);
        if (IsGroupMemberActive(groupId, 0) == FALSE) {
            ResetAnimationTrackState(&request);
            request.id = actor->markerId;
            request.unk_25 = 0;
            request.unk_24 = 0;
            request.prevIndex = gMarkerReset.markerIndex;
            request.index = 0;
            if (actor->getPosition != NULL) {
                pos = actor->getPosition(actor);
            } else {
                pos = &actor->pos;
            }
            request.pos = *pos;
            request.pos.z += 0x1000;
            func_ov021_020a8cc0(&request, groupId);
        }
        actor->flags |= 0x40000;
    }
}

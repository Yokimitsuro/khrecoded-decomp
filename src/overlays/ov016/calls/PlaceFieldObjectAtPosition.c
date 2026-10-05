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
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[4];
    AnimTrack track;
} FieldObject;

extern void PlaceFieldObjectNode(FieldObject *obj, AnimTrack *track, VecFx32 *position);

void PlaceFieldObjectAtPosition(FieldObject *obj)
{
    PlaceFieldObjectNode(obj, &obj->track, &obj->position);
}

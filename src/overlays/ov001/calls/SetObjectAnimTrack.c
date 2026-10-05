#include "nitro/types.h"

typedef struct ObjectModel {
    u8 pad_00[0x14];
    s16 anim;
} ObjectModel;

typedef struct FieldObject {
    u8 pad_00[0xc];
    ObjectModel *model;
    u8 pad_10[0x3e];
    u16 flags;
    u8 pad_50[3];
    s8 animTrack;
} FieldObject;

extern void RebindAnimTracks(s16 *anim, int blendIndex, int frame);

void SetObjectAnimTrack(FieldObject *object, s8 track)
{
    object->animTrack = track;
    if (object->flags & 4) {
        RebindAnimTracks(&object->model->anim, object->animTrack, 0);
    }
}

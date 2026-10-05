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
    u8 pad_00[0x60];
    void *nodes[1];
} NodeTable;

typedef struct {
    u8 pad_00[4];
    NodeTable *table;
} FieldObject;

extern int GetMaximumAlternateFieldValue(unsigned int object);

void InitAnimTrack(FieldObject *obj, AnimTrack *track, int nodeIndex, fx32 speed, int animId)
{
    void *node = obj->table->nodes[nodeIndex];

    track->speed = speed;
    track->animId = animId;
    track->nodeIndex = nodeIndex;
    track->frame = 0;
    track->maxFrame = GetMaximumAlternateFieldValue((unsigned int)node);
}

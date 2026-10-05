#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 flags;
    u8 pad_02[0x7c - 0x02];
    u16 animId;
    u8 pad_7e[0xa4 - 0x7e];
    VecFx32 position;
    fx32 scaleX;
    fx32 scaleY;
    fx32 scaleZ;
} SceneNode;

typedef struct {
    u8 pad_00[0x60];
    SceneNode *nodes[1];
} NodeTable;

typedef struct {
    u8 pad_00[4];
    NodeTable *table;
} FieldObject;

typedef struct {
    u16 animId;
    u16 nodeIndex;
    fx32 scale;
    int frame;
} NodePose;

extern void RebindAnimTracks(SceneNode *node, int blendIndex, int frame);
extern void func_01ffb12c(SceneNode *node);

void PlaceFieldObjectNode(FieldObject *obj, NodePose *pose, VecFx32 *position)
{
    SceneNode *node = obj->table->nodes[pose->nodeIndex];

    node->position = *position;
    node->scaleZ = pose->scale;
    node->scaleY = node->scaleZ;
    node->scaleX = node->scaleY;
    node->animId = pose->animId;
    node->flags |= 0x20;
    RebindAnimTracks(node, 0, pose->frame);
    func_01ffb12c(node);
}

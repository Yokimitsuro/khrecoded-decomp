#include "nitro/types.h"

typedef struct {
    u8 data[0x88];
} GroupObject;

typedef struct {
    u8 pad_00[0x2];
    u8 objectCount;
    u8 pad_03[0x15];
    GroupObject *objects;
    u8 pad_1c[0x4];
} ObjectGroup;

typedef struct {
    u8 pad_00[0x56];
    u8 groupCount;
    u8 pad_57[0xd];
    ObjectGroup *groups;
} OverlayState;

typedef struct {
    u32 unk_00;
    int **trees;
} WorldState;

extern OverlayState *data_ov031_020bc820;
extern WorldState *GetActorRegistry(void);
extern void QuadTree_RemoveObject(int *tree, GroupObject *object);

void RemoveGroupObjectsFromTree(void)
{
    WorldState *world = GetActorRegistry();
    int group;
    int i;

    for (group = 1; group < data_ov031_020bc820->groupCount; group++) {
        for (i = 0; i < data_ov031_020bc820->groups[group].objectCount; i++) {
            QuadTree_RemoveObject(*world->trees, &data_ov031_020bc820->groups[group].objects[i]);
        }
    }
}

#include "nitro/types.h"

typedef struct ModelGroup {
    u8 pad00[0x4c];
    u16 modeBits : 2;
    u16 flagA : 1;
    u16 flagB : 1;
    u16 flagC : 1;
    u16 flagD : 1;
    u16 flagE : 1;
    u16 layerBits : 2;
    u16 padBits : 7;
    u8 pad4e[0x42];
} ModelGroup;

typedef struct {
    u8 pad00[0x68];
    int mode;
    ModelGroup *groups;
} GroupSet;

extern void StartEntryMotion(void *motion, GroupSet *set);
extern void ResetModelGroup(ModelGroup *group);
extern void UpdateFacingTowardTarget(int entity, BOOL useEntry);

void ActivateSlotModelGroup(int entity, int index)
{
    u32 hidden = *(u32 *)(entity + 0x234) & 4;
    GroupSet *set = *(GroupSet **)(entity + 0x1078);
    ModelGroup *group;
    int motion;
    *(u64 *)(entity + 0x9ac) |= 0x40;
    StartEntryMotion((void *)(entity + 0x1070), set);
    group = &set->groups[index];
    motion = *((u8 *)group + 2) + 0x2d;
    if (*(void (**)(int, int, int))(entity + 0x1f8) != NULL) {
        (*(void (**)(int, int, int))(entity + 0x1f8))(entity, motion, -1);
    }
    if (*(void (**)(int, int))(entity + 0x1fc) != NULL) {
        (*(void (**)(int, int))(entity + 0x1fc))(entity, 0);
    }
    ResetModelGroup(group);
    group->flagE = (u16)hidden;
    group->layerBits = 1;
    if (set->mode == 1) {
        group->layerBits = 2;
    }
    UpdateFacingTowardTarget(entity, TRUE);
}

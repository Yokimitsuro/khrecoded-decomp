#include "nitro/types.h"

typedef struct ModelGroup {
    u8 pad00[0x42];
    s16 modelCount;
    u8 *models;
    u8 pad48[4];
    u16 modeBits : 2;
    u16 flagA : 1;
    u16 flagB : 1;
    u16 flagC : 1;
    u16 flagD : 1;
    u16 flagE : 1;
    u16 layerBits : 2;
    u16 padBits : 7;
    s16 slotIds[4][8];
} ModelGroup;

extern void func_ov021_020aa128(void *model);

void ResetModelGroup(ModelGroup *group)
{
    int col;
    int row;

    row = 0;
    group->modeBits = 0;
    group->layerBits = 0;
    group->flagA = 0;
    group->flagB = 0;
    group->flagC = 0;
    group->flagD = 0;
    group->flagE = 0;
    for (; row < 4; row++) {
        for (col = 0; col < 8; col++) {
            group->slotIds[row][col] = -1;
        }
    }
    for (row = 0; row < group->modelCount; row++) {
        func_ov021_020aa128(group->models + row * 0x54);
    }
}

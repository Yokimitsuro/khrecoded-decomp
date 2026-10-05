#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    u16 savedValues[3];
    u8 pad_22[7];
    u8 slotSettings[6];
    u8 defaultStyle;
    u8 altStyle;
    u8 pad_31[0x24];
    s8 slotIndex;
    u8 pad_56[6];
    u8 altMask;
    u8 pad_5d[2];
    u8 lockedMask;
    u8 pad_60[0x14];
    s32 overrideActive;
} SceneContext;

typedef struct {
    u8 pad_00[0x44];
    u16 values[3];
    u8 pad_4a[2];
    u32 style;
} SceneState;

typedef struct {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

extern Ov032Globals data_ov032_020c0080;
extern void WriteSessionPackedBits(int bitOffset, u32 bitCount, u32 value);

void ApplySlotStyleToSession(void) {
    s32 index;
    SceneContext *context;
    u32 slotMask;

    for (index = 0; index < 3; index++) {
        data_ov032_020c0080.scene->values[index] = data_ov032_020c0080.context->savedValues[index];
    }
    context = data_ov032_020c0080.context;
    WriteSessionPackedBits(0x3800, 3, context->slotSettings[context->slotIndex]);
    context = data_ov032_020c0080.context;
    if (context->overrideActive != 0) {
        data_ov032_020c0080.scene->style = 3;
        data_ov032_020c0080.scene->values[2] = 0x3f;
    } else {
        slotMask = 1 << context->slotIndex;
        if (context->lockedMask & slotMask) {
            data_ov032_020c0080.scene->style = 2;
            data_ov032_020c0080.scene->values[2] = 0x3e;
        } else if (context->altMask & slotMask) {
            data_ov032_020c0080.scene->style = context->altStyle;
        } else {
            data_ov032_020c0080.scene->style = context->defaultStyle;
        }
    }
    WriteSessionPackedBits(0x3803, 3, data_ov032_020c0080.scene->style);
}

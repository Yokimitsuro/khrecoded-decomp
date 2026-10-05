#include "nitro/types.h"

typedef unsigned int UNDEF4;

typedef struct Actor {
    u8 pad_000[4];
    s32 field_004;
    u32 field_008;
    u32 field_00c;
    u8 pad_010[0xD08];
    int *dialogPtr;
    u8 pad_d1c[0x1D8];
    u32 flags;
    u8 pad_ef8[8];
    u32 kindField;
} Actor;

extern u32 func_ov001_02089a1c(UNDEF4 arg);
extern s32 func_0202f4cc(s32 arg0, s32 arg1);
extern s32 ActorSlot_GetField1C4ByIndex(s32 arg0);
extern s32 _s32_div_f(s32 arg0, s32 arg1);

void InitActorDialogTimer(Actor *actor, UNDEF4 param2)
{
    s32 width;
    s32 divisor;

    actor->flags = actor->flags | 0x80;
    actor->field_00c = 0;
    actor->field_008 = func_ov001_02089a1c(param2);
    width = func_0202f4cc(*actor->dialogPtr + 4, 0);
    divisor = ActorSlot_GetField1C4ByIndex(actor->kindField & 0xffff);
    width = _s32_div_f(width, divisor);
    actor->field_004 = width / 2;
}

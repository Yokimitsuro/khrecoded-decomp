#include "nitro/types.h"

extern u8 *data_ov001_020a0514;
extern void Obj_ReleaseIfSet(void *channel);
extern void func_01ff8ad8(const void *src, void *dst, u32 len);
extern void MI_CpuFill8(void *dst, s32 value, u32 size);
extern void CamAnim_Start(void *channel, u32 value);
extern void Obj_SetIndirectWord(void *channel, u32 value);
extern void Obj_SetWord54(void *channel, u32 value);
extern void Obj_SetWord58(void *channel, u32 value);

void ActorChannel_ConfigureAndPlay(u32 channelId, u32 param2, s32 resetMode)
{
    u8 *ctx;
    u32 state;
    u8 saveBuffer[56];

    ctx = data_ov001_020a0514;
    Obj_ReleaseIfSet(ctx + 0x140);
    if (resetMode == 0) {
        func_01ff8ad8(ctx, saveBuffer, 0x38);
        MI_CpuFill8(ctx + 0x38, 0, 0xa0);
        func_01ff8ad8(saveBuffer, ctx, 0x38);
        state = 1;
    } else {
        MI_CpuFill8(ctx + 0x140, 0, 0x5c);
        if (1 < *(s32 *)(ctx + 0x98) + 1U) goto skipState;
        state = 2;
    }
    *(u32 *)(ctx + 0x98) = state;
skipState:
    CamAnim_Start(ctx + 0x140,
                  (*(s32 *)(ctx + 0x1d4) + 0x8000U & 0xfffffc) << 7 | 0x80000000 |
                  channelId & 0x1ff);
    Obj_SetIndirectWord(ctx + 0x140, 0);
    Obj_SetWord54(ctx + 0x140, param2);
    Obj_SetWord58(ctx + 0x140, 0x1000);
    *(u32 *)(ctx + 0x9c) = 0xffffffff;
    *(s32 *)(ctx + 0x1e4) = resetMode;
}

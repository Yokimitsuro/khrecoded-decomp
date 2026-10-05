#include "nitro/types.h"

typedef unsigned int UNDEF4;

typedef struct SessionContext {
    u8 pad_000[0x230];
    u8 *field_230;
} SessionContext;

extern SessionContext *GetBoundedEntryField(s32 arg);
extern s32 func_ov001_02063a38(void);
extern void func_ov059_020cd2a0(SessionContext *context, UNDEF4 param1);
extern void CaptureSelectedJointMtx_01fffe28(SessionContext *context, UNDEF4 param1);
extern void MI_CpuCopy8(void *src, void *dst, u32 size);

void CopySessionResourceBuffer(UNDEF4 param1)
{
    SessionContext *context;
    s32 sessionMode;
    u8 *resource;

    context = GetBoundedEntryField(0);
    sessionMode = func_ov001_02063a38();
    if (sessionMode == 7) {
        func_ov059_020cd2a0(context, param1);
        resource = *(u8 **)(context->field_230 + 0xc4);
        if (resource != 0) {
            MI_CpuCopy8(*(void **)((u8 *)context + 0xae4), resource + 0x80, 0x30);
            return;
        }
    } else {
        CaptureSelectedJointMtx_01fffe28(context, param1);
        resource = *(u8 **)(context->field_230 + 0xc4);
        if (resource != 0) {
            MI_CpuCopy8(*(void **)((u8 *)context + 0xc78), resource + 0x80, 0x30);
        }
    }
}

#include "nitro/types.h"

extern void *func_ov001_0207b770(void);
extern int func_ov001_0207b764(void);
extern u16 *func_ov027_020ba300(void *messages, int index, u16 *buffer, int size, ...);
extern void CallVirtualHandlerSlot1(void *object, int arg);
extern u32 GetFieldFont2(void);
extern void func_02001620(void *context, u32 x, u32 y, u32 color, u32 flags, u16 *text, u32 font, int maxWidth);
extern void Text_UploadTileBuffer(void *context);

void DrawRemainingCountText(u8 *screen, int count)
{
    u16 buffer[64];

    if (*(int *)(screen + 0x66d8) != 0) {
        if (count >= 4) {
            func_ov027_020ba300(func_ov001_0207b770(), 1, buffer, 0x40, func_ov001_0207b764());
        } else {
            func_ov027_020ba300(func_ov001_0207b770(), 0, buffer, 0x40, func_ov001_0207b764(), count);
        }
        CallVirtualHandlerSlot1(screen + 0x6634, 0);
        func_02001620(screen + 0x6634, 4, 3, 2, 0x209, buffer, GetFieldFont2(), 0x84);
        Text_UploadTileBuffer(screen + 0x6634);
    }
}

#include "nitro/types.h"

typedef void (*ModeHandler)(void *modeState);

typedef struct {
    u32 unk_00;
    u8 modeState[8];
    s32 mode;
    u8 pad_10[0xf8 - 0x10];
    u32 suspended;
} ModeContext;

extern ModeContext *data_ov001_020a04e4;
extern ModeHandler gMessageWindowStateHandlers[];

extern void func_ov001_0207a370(void);

u32 RunActiveModeHandler(void)
{
    ModeContext *context = data_ov001_020a04e4;
    ModeHandler handler;

    if (context->suspended != 0) {
        return 0;
    }
    func_ov001_0207a370();
    handler = gMessageWindowStateHandlers[context->mode];
    if (handler != NULL) {
        handler(context->modeState);
    }
    return 0;
}

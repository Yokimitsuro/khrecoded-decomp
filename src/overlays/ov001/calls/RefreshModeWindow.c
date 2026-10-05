#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 mode;
} ModeState;

typedef struct {
    u32 active;
    ModeState state;
} ModeContext;

extern ModeContext *data_ov001_020a04e4;

extern void FlushBufferAndRunCallback(void *window);

void RefreshModeWindow(int screen)
{
    ModeContext *context = data_ov001_020a04e4;

    if (context != NULL && screen == 0) {
        switch (context->state.mode) {
        case 4:
        case 5:
        case 6:
            FlushBufferAndRunCallback((u8 *)&context->state + 0x94);
            break;
        }
    }
}

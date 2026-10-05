#include "nitro/types.h"

typedef struct SubtitleTextRenderer {
    u8 pad_00[0x44];
    BOOL uploadPending;
    u8 pad_48[0x08];
    s32 penY;
    u8 pad_54[0x0c];
    s32 activeSource;
} SubtitleTextRenderer;

extern void CallVirtualHandlerSlot1(SubtitleTextRenderer *renderer, int arg);

void SubtitleText_BeginDraw(SubtitleTextRenderer *renderer)
{
    renderer->activeSource = 0;
    renderer->penY = 0;
    renderer->uploadPending = TRUE;
    CallVirtualHandlerSlot1(renderer, 0);
}

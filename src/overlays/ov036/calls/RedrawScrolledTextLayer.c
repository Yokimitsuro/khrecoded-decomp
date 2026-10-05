#include "nitro/types.h"

typedef struct ScrolledText {
    s32 state;
    u8 pad_04[0x38];
    u8 textLayer[0x34];
    const u16 *text;
    u8 pad_74[0xe];
    u16 lineSpacing;
    u8 pad_84[0x88];
    s32 *scrollLine;
} ScrolledText;

extern u8 GetNestedModeByte(void *textLayer);
extern void CallVirtualHandlerSlot1(void *textLayer, int arg);
extern void DrawTextAnchored(void *textLayer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback(void *textLayer);

void RedrawScrolledTextLayer(ScrolledText *view)
{
    s32 *scrollLine;
    int y;

    if (view->state != 1) {
        return;
    }
    scrollLine = view->scrollLine;
    y = GetNestedModeByte(view->textLayer);
    y = -(*scrollLine * (y + view->lineSpacing));
    CallVirtualHandlerSlot1(view->textLayer, 1);
    DrawTextAnchored(view->textLayer, 0x11, y + 1, 2, 0x209, view->text);
    DrawTextAnchored(view->textLayer, 0x10, y, 3, 0x209, view->text);
    FlushBufferAndRunCallback(view->textLayer);
}

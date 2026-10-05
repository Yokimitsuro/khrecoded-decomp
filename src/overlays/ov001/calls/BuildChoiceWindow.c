#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct TextFrame {
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    u16 charBase;
    u16 palette;
    u16 hSpace;
    u16 vSpace;
} TextFrame;

typedef struct MessageSet {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct HudContext {
    u8 pad_000[0x9c];
    NNSG2dFont menuFont;
    u8 pad_afterMenuFont[0x1f8 - 0x9c - sizeof(NNSG2dFont)];
    s32 choiceMenuActive;
    u8 choiceWindow[0x34];
    void *choiceLines[4];
} HudContext;

extern const TextFrame data_ov001_0209dc6c;
extern u32 MakePrimaryVramKey_02073634(u32 messageId);
extern void LoadPackedFileView(MessageSet *messages, u32 fileId, int compressed);
extern const void *func_ov027_020ba2c8(MessageSet *messages, int index);
extern int NNSi_G2dFontGetTextWidth(const NNSG2dFont *font, int hSpace, const void *text);
extern void InitTextLayerAt(void *window, int bgLayer, void *charBase, NNSG2dFont *font, TextFrame *frame);
extern void *GetWord20(void *window);
extern void CallVirtualHandlerSlot1(void *window, int color);
extern void DrawTextAnchored(void *window, int x, int y, int color, int flags, const void *text);
extern void *func_02001928(void *window, int selectAsCurrent, int alignFromEnd);
extern void FreePointerIfSet(void **pointer);

void BuildChoiceWindow(HudContext *context)
{
    int maxWidth = 0;
    MessageSet messages;
    TextFrame frame = data_ov001_0209dc6c;
    int i;
    int columns;
    int centerX;

    LoadPackedFileView(&messages, MakePrimaryVramKey_02073634(5), 1);
    for (i = 0; i < 4; i++) {
        int width = NNSi_G2dFontGetTextWidth(&context->menuFont, 1, func_ov027_020ba2c8(&messages, i));
        if (maxWidth < width) {
            maxWidth = width;
        }
    }
    columns = (maxWidth + 7) / 8;
    if (columns > 16) {
        columns = 16;
    }
    if (columns == 0) {
        frame.width = 1;
    } else {
        frame.width = columns;
    }
    InitTextLayerAt(context->choiceWindow, 3, 0, &context->menuFont, &frame);
    context->choiceLines[0] = GetWord20(context->choiceWindow);
    CallVirtualHandlerSlot1(context->choiceWindow, 0xe);
    centerX = columns * 8 / 2;
    DrawTextAnchored(context->choiceWindow, centerX, 3, 8, 0x411, func_ov027_020ba2c8(&messages, 0));
    for (i = 1; i < 4; i++) {
        context->choiceLines[i] = func_02001928(context->choiceWindow, 1, 0);
        CallVirtualHandlerSlot1(context->choiceWindow, 0xe);
        DrawTextAnchored(context->choiceWindow, centerX, 3, 8, 0x411, func_ov027_020ba2c8(&messages, i));
    }
    FreePointerIfSet(&messages.file);
    context->choiceMenuActive = 1;
}

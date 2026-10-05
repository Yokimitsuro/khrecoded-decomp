#include "nitro/types.h"

typedef struct ChoiceList {
    u32 unk_00;
    s32 count;
    u32 unk_08;
    s32 defaultIndex;
} ChoiceList;

typedef struct MessageWindow {
    void *text;
    s32 style;
    s32 loading;
    s32 panel;
    u8 pad_10[0x28];
    s32 width;
    u8 pad_3C[0xC];
    s32 originX;
    s32 originY;
    s32 frameKind;
    u8 pad_54[0x26];
    u16 choiceCount;
    u16 cursor;
    u8 pad_7E[0x2];
    s32 defaultIndex;
    u8 pad_84[0x44];
    s32 isSpecial;
} MessageWindow;

typedef struct MessageContext {
    s32 mode;
    MessageWindow window;
} MessageContext;

typedef struct ModeGraphics {
    s32 ids[11];
} ModeGraphics;

extern MessageContext *data_ov001_020a04e4;
extern const ModeGraphics data_ov001_0209df4c;

extern unsigned int MakePrimaryVramKey(unsigned int slot);
extern unsigned int MakePrimaryVramKey_02071214(unsigned int slot);
extern void *QueueFileLoadRequest(unsigned int key, int loadMode, void *callback, void *userData);
extern void LoadModeBg3Graphics(void);
extern void func_ov001_02078cf8(void);
extern void func_ov001_0207a1d0(MessageWindow *window);
extern void LoadMenuEntryPanel(MessageWindow *window, int panel);
extern void SetTextAndChoices(MessageWindow *window, u16 *text, ChoiceList *choices);
extern void func_ov001_020791e0(MessageWindow *window, int width);
extern void func_ov001_02078e30(MessageWindow *window);

BOOL OpenMessageWindow_0207a504(int mode, void *text, int style, int panel, int originX, int originY, u16 *message,
                                ChoiceList *choices) {
    MessageContext *context = data_ov001_020a04e4;
    ModeGraphics graphics = data_ov001_0209df4c;
    BOOL special;
    MessageWindow *window;

    if (context == NULL) {
        return FALSE;
    }
    context->window.text = text;
    context->window.originX = originX;
    context->window.originY = originY;
    context->window.frameKind = mode == 1 ? 2 : 8;
    special = mode == 5 || mode == 7 || mode == 10;
    window = &context->window;
    window->isSpecial = special ? TRUE : FALSE;
    if (context->window.loading != 0) {
        return FALSE;
    }
    context->window.panel = panel;
    context->window.style = style;
    if (mode != context->mode) {
        if (graphics.ids[mode] != -1) {
            QueueFileLoadRequest(MakePrimaryVramKey(graphics.ids[mode]), 1,
                                          LoadModeBg3Graphics, (void *)mode);
            if (mode == 5 || mode == 10 || mode == 6 || mode == 7) {
                QueueFileLoadRequest(MakePrimaryVramKey_02071214(1), 1, func_ov001_02078cf8, NULL);
            }
            context->window.loading = 1;
        }
    } else if (choices != NULL) {
        QueueFileLoadRequest(MakePrimaryVramKey(4), 1, LoadModeBg3Graphics, (void *)mode);
        context->window.loading = 1;
    }
    context->mode = mode;
    if (context->window.loading != 1) {
        if (panel == 0) {
            func_ov001_0207a1d0(&context->window);
        } else {
            LoadMenuEntryPanel(&context->window, panel);
        }
    }
    SetTextAndChoices(&context->window, message, choices);
    func_ov001_020791e0(&context->window, context->window.width);
    if (choices != NULL) {
        func_ov001_02078e30(&context->window);
        window->cursor = 0;
        window->choiceCount = choices->count;
        window->defaultIndex = choices->defaultIndex;
    }
    return TRUE;
}

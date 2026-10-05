#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_00[4];
    s32 phase;
    u8 pad_08[0x84 - 0x08];
    u64 pageTick;
    u8 pad_8c[0x94 - 0x8c];
    u8 textLayer[4];
} MessageWindow;

typedef struct ModeContext {
    s32 mode;
} ModeContext;

extern ModeContext *data_ov001_020a04e4;

extern u64 OS_GetTick(void);
extern int DrawMessageWindowPage(MessageWindow *window, int arg);
extern int func_ov001_02079a9c(MessageWindow *window);
extern int UpdateMessageWindowText(MessageWindow *window, BOOL fullRedraw);
extern void Text_UploadTileBuffer(void *layer);
extern void *GetSceneTagTracker(void);
extern void FinishMessageWindowPage(MessageWindow *window);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *tracker, void *record);

void UpdateMessageWindow(MessageWindow *window)
{
    ModeContext *context = data_ov001_020a04e4;
    int busy = 0;
    u64 now = OS_GetTick();
    void *tracker;

    if (context->mode == 2 || (u32)(context->mode - 8) <= 1) {
        if (now < window->pageTick + 0x1991b) {
            return;
        }
    }
    switch (window->phase) {
    case 0:
        busy = DrawMessageWindowPage(window, 0);
        break;
    case 2:
        busy = UpdateMessageWindowText(window, 0);
        break;
    case 1:
        busy = func_ov001_02079a9c(window);
        Text_UploadTileBuffer(window->textLayer);
        break;
    }
    if (busy == 0) {
        tracker = GetSceneTagTracker();
        FinishMessageWindowPage(window);
        switch (context->mode) {
        case 5:
        case 10:
            func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x25a));
            return;
        case 7:
            func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x258));
            return;
        case 6:
            func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x259));
            return;
        }
    }
}

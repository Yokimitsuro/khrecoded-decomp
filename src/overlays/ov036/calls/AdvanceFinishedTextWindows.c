#include "nitro/types.h"

typedef struct RecordEntry {
    s32 recordIndex;
    u8 pad_04[0x8];
    u32 flags;
} RecordEntry;

typedef struct TextWindowEntry {
    u8 pad_000[0x4];
    s32 style;
    u8 pad_008[0xa4];
    s32 page;
    s32 pageCount;
    RecordEntry nameRecord;
    u8 pad_0C4[0x4c];
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
    s32 openWindowCount;
    u8 loader[0x1c];
    s32 loaderState;
    u8 pad_6850[0x4c];
    s32 historyEnabled;
} OverlayWork;

extern OverlayWork *gTextWindowResourceTable;
extern int func_ov036_020c280c(TextWindowEntry *window);
extern void SetTimerDuration(TextWindowEntry *window, int state);
extern void SetRecordEntryEnabled(RecordEntry *entry, int enabled);

void AdvanceFinishedTextWindows(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        TextWindowEntry *window = &gTextWindowResourceTable->windows[i];

        if (func_ov036_020c280c(window) == 7) {
            BOOL finished = FALSE;

            if (gTextWindowResourceTable->historyEnabled > 0 && window->page >= window->pageCount - 1
                && gTextWindowResourceTable->loaderState == 1) {
                finished = TRUE;
            }
            if (finished) {
                SetTimerDuration(&gTextWindowResourceTable->windows[i], 0xd);
            } else {
                SetTimerDuration(&gTextWindowResourceTable->windows[i], 8);
                if (gTextWindowResourceTable->windows[i].style != 0xe) {
                    SetRecordEntryEnabled(&gTextWindowResourceTable->windows[i].nameRecord, 1);
                }
            }
        }
    }
}

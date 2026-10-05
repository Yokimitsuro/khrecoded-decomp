#include "nitro/types.h"

typedef struct TextWindowEntry {
    u8 data[0x110];
} TextWindowEntry;

typedef struct HistoryEntry {
    u8 pad_00[0x18];
    void *text;
    u8 pad_1C[0xc];
} HistoryEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x64fc];
    TextWindowEntry windows[3];
    s32 openWindowCount;
    u8 loader[0x1c];
    HistoryEntry history[2];
    s32 historyCount;
} OverlayWork;

typedef void (*TextWindowHandler)(TextWindowEntry *window);

extern OverlayWork *gTextWindowResourceTable;
extern TextWindowHandler gTextWindowStateHandlers[];
extern int func_ov036_020c280c(TextWindowEntry *window);
extern void SetTimerDuration(TextWindowEntry *window, int state);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void MIi_CpuClearFast(int value, void *dst, u32 size);

void CloseAllTextWindows(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        TextWindowEntry *window = &gTextWindowResourceTable->windows[i];

        if (func_ov036_020c280c(window) != 0) {
            TextWindowHandler handler;

            SetTimerDuration(window, 10);
            handler = gTextWindowStateHandlers[func_ov036_020c280c(window)];
            if (handler != NULL) {
                handler(window);
            }
        }
    }
    for (i = 0; i < gTextWindowResourceTable->historyCount; i++) {
        HistoryEntry *entry = &gTextWindowResourceTable->history[i];

        NNSi_FndFreeFromDefaultHeap(entry->text);
        MIi_CpuClearFast(0, entry, sizeof(HistoryEntry));
    }
    gTextWindowResourceTable->historyCount = 0;
}

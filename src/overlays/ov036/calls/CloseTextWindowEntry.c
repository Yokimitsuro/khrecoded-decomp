#include "nitro/types.h"

typedef struct RecordEntry {
    s32 recordIndex;
    u8 pad_04[0x8];
    u32 flags;
} RecordEntry;

typedef struct TextWindowEntry {
    u8 pad_000[0x34];
    void *glyphBuffer;
    u8 pad_038[0x7c];
    RecordEntry nameRecord;
    u8 pad_0C4[0x30];
    RecordEntry bodyRecord;
    u8 pad_104[0x8];
    void *lineBuffer;
} TextWindowEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x682c];
    s32 openWindowCount;
} OverlayWork;

extern OverlayWork *gTextWindowResourceTable;
extern void SetDisplayLayersVisible(TextWindowEntry *config, BOOL enable);
extern void SetRecordEntryEnabled(RecordEntry *entry, int enabled);
extern void func_ov036_020bf63c(TextWindowEntry *window);
extern void func_ov036_020bee60(TextWindowEntry *window);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern void SetTimerDuration(TextWindowEntry *entry, int state);

void CloseTextWindowEntry(TextWindowEntry *window)
{
    SetDisplayLayersVisible(window, FALSE);
    SetRecordEntryEnabled(&window->bodyRecord, 0);
    if (window->nameRecord.recordIndex != -1) {
        SetRecordEntryEnabled(&window->nameRecord, 0);
    }
    func_ov036_020bf63c(window);
    func_ov036_020bee60(window);
    if (window->glyphBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(window->glyphBuffer);
        window->glyphBuffer = NULL;
    }
    if (window->lineBuffer != NULL) {
        NNSi_FndFreeFromDefaultHeap(window->lineBuffer);
        window->lineBuffer = NULL;
    }
    gTextWindowResourceTable->openWindowCount--;
    if (gTextWindowResourceTable->openWindowCount < 0) {
        gTextWindowResourceTable->openWindowCount = 0;
    }
    SetTimerDuration(window, 0);
}

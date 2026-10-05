#include "nitro/types.h"

typedef struct WindowSize {
    s32 width;
    s32 height;
} WindowSize;

typedef struct MessageRequest {
    s32 x;
    s32 y;
    WindowSize *size;
    s32 style;
    u16 *text;
    s32 portraitId;
    s32 portraitPose;
    s32 kind;
} MessageRequest;

typedef struct MessageEntry {
    s32 kind;
    s32 x;
    s32 y;
    s32 width;
    s32 height;
    s32 style;
    u16 *text;
    s32 portraitId;
    s32 portraitPose;
    s32 phase;
} MessageEntry;

typedef struct OverlayWork {
    u8 pad_0000[0x6458];
    s32 phase;
    u8 pad_645c[0x684c - 0x645c];
    MessageEntry messages[2];
    s32 messageCount;
} OverlayWork;

extern OverlayWork *gTextWindowResourceTable;
extern int Utf16Length(u16 *text);
extern u16 *Utf16CopyPadded(u16 *destination, u16 *source, int unitCount);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void PushTextWindowHistory(void);

void QueueMessageWindow(MessageRequest *request)
{
    MessageEntry *entry;
    u16 *text;
    int length;

    gTextWindowResourceTable->phase++;
    gTextWindowResourceTable->phase %= 2;
    entry = &gTextWindowResourceTable->messages[gTextWindowResourceTable->messageCount];
    entry->kind = request->kind;
    entry->x = request->x;
    entry->y = request->y;
    entry->style = request->style;
    entry->text = NULL;
    entry->phase = gTextWindowResourceTable->phase;
    if (entry->kind == 1) {
        entry->portraitId = request->portraitId;
        entry->portraitPose = request->portraitPose;
    } else {
        entry->portraitId = 0;
        entry->portraitPose = 0;
    }
    if (request->size != NULL) {
        entry->width = request->size->width;
        entry->height = request->size->height;
    } else {
        entry->width = 0x80;
        entry->height = 0x60;
    }
    text = request->text;
    if (text != NULL) {
        length = Utf16Length(text);
        entry->text = NNS_FndAllocFromDefaultExpHeapEx((Utf16Length(text) + 1) * 2, -4);
        Utf16CopyPadded(entry->text, request->text, length);
        entry->text[length] = 0;
    }
    gTextWindowResourceTable->messageCount++;
    if (entry->kind != 1) {
        PushTextWindowHistory();
    }
}

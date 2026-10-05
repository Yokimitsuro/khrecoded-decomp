#include "nitro/types.h"

typedef struct TextLayer {
    u8 pad_00[0x34];
} TextLayer;

typedef struct StatusPage {
    u8 pad_000[0x140];
    void *fileData;
    void *resource;
    u8 buffers[0x1c];
    BOOL bgOffsetHookActive;
    u8 pad_168[0x170 - 0x168];
    BOOL unk_170;
    u8 pad_174[0x198 - 0x174];
    TextLayer upperText;
    TextLayer lowerText;
} StatusPage;

extern const char sOv073_OCBGOFSFUNC_020c41a8[];
extern void NotifyBothOrOne(u32 kind, const char *name, int index);
extern BOOL DestroyFndObjectList(TextLayer *layer);
extern void ReleaseListView(StatusPage *page);
extern int ZeroHalfThenFree(void *block);
extern void ReleaseResourceWithBuffers(void **resourceHandle, int unused);
extern void FreeAllocatedBuffers(void *owner);
extern BOOL ReleaseRecordSlot(s32 slot);

void ReleaseStatusPage(void *menu, StatusPage *page)
{
    if (page->bgOffsetHookActive) {
        NotifyBothOrOne(1, sOv073_OCBGOFSFUNC_020c41a8, 0);
        page->bgOffsetHookActive = FALSE;
    }
    DestroyFndObjectList(&page->upperText);
    DestroyFndObjectList(&page->lowerText);
    ReleaseListView(page);
    ZeroHalfThenFree(page->fileData);
    ReleaseResourceWithBuffers(&page->resource, 0xe);
    FreeAllocatedBuffers(page->buffers);
    page->unk_170 = 0;
    ReleaseRecordSlot(1);
}

#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[10];
    u8 pad_b68[0x64];
    u32 activeId;
} EntryList;

extern void *func_ov039_020bc1dc(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern int DrawPromptMessage(void *scene, int headerMessageId, int footerMessageId);
extern void ShowConfirmWindows(void *scene);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void OpenPromptMessage0F(EntryList *list)
{
    u32 selectedId;
    int frameId;
    void *frame;
    void *container;

    container = func_ov039_020bc1dc();
    selectedId = list->entries[list->cursor].id;

    if (IsGlobalPackedBitSet(0x4436) && list->activeId != selectedId) {
        frameId = DrawPromptMessage(list, 0xf, 0x16);
    } else {
        frameId = DrawPromptMessage(list, 0xf, 0x15);
    }
    ShowConfirmWindows(list);
    frame = FindWidgetById(container, frameId);
    SetEntrySlotsVisible(container, frame, TRUE);
}

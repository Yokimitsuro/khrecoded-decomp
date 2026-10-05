#include "nitro/types.h"

typedef struct {
    u32 id;
    u8 pad_004[0x104];
} ListEntry;

typedef struct {
    u32 unk_00;
    int cursor;
    u8 pad_008[0x110];
    ListEntry entries[8];
    u8 pad_958[0x274];
    u32 exclusiveId;
} PanelScene;

extern void *func_ov039_020bc1dc(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern int DrawPromptMessage(PanelScene *scene, int headerMessageId, int footerMessageId);
extern void ShowConfirmWindows(PanelScene *scene);
extern void *FindWidgetById(void *container, int elementId);
extern void SetEntrySlotsVisible(void *container, void *element, BOOL visible);

void OpenEntryPromptForMode(PanelScene *scene, int mode)
{
    int frameId;
    void *frame;
    void *container = func_ov039_020bc1dc();
    u32 id = scene->entries[scene->cursor].id;

    if (mode == 3) {
        if (IsGlobalPackedBitSet(0x4436) && scene->exclusiveId == id) {
            frameId = DrawPromptMessage(scene, 0xf, 0x16);
        } else {
            frameId = DrawPromptMessage(scene, 0xf, 0x15);
        }
    } else {
        frameId = DrawPromptMessage(scene, 0xd, 0x16);
    }
    ShowConfirmWindows(scene);
    frame = FindWidgetById(container, frameId);
    SetEntrySlotsVisible(container, frame, TRUE);
}


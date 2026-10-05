#include "nitro/types.h"

typedef struct MenuScreenEntry {
    u8 pad_00[0x8];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s32 param;
    u32 fileIndex;
} MenuScreenEntry;

typedef struct MenuScreenState {
    u8 pad_00[0x4];
    s32 screenId;
    u8 pad_08[0x4];
    s32 archiveBase;
    u8 pad_10[0x7fa8];
    u16 x;
    u16 y;
    u16 width;
    u16 height;
    s32 param;
} MenuScreenState;

extern MenuScreenState *data_ov023_020b6f84;

extern void *func_ov027_020ba1f8(void *resource);
extern MenuScreenEntry *func_ov023_020b5b8c(void *node, u16 id);
extern void *QueueFileLoadRequest(u32 archiveId, int loadMode, void (*callback)(void *), void *userData);
extern void LoadMenuScreenResource(void *resource);
extern void RequestPanelFallback(void);
extern void SetPanelSessionActive(void);
extern void func_ov027_020ba200(void *resource, int release);

void ApplyMenuScreenEntry(void *resource)
{
    MenuScreenState *state = data_ov023_020b6f84;
    MenuScreenEntry *entry = func_ov023_020b5b8c(func_ov027_020ba1f8(resource), state->screenId);

    if (entry != NULL) {
        state->x = entry->x;
        state->y = entry->y;
        state->width = entry->width << 3;
        state->height = entry->height << 3;
        state->param = entry->param;
        QueueFileLoadRequest(((state->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (entry->fileIndex & 0x1ff),
                                      1, LoadMenuScreenResource, NULL);
    } else {
        state->width = 0;
        state->height = 0;
        state->param = 0;
        RequestPanelFallback();
        SetPanelSessionActive();
    }
    func_ov027_020ba200(resource, 1);
}

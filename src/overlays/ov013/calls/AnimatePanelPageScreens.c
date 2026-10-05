#include "nitro/types.h"

typedef struct PageTable {
    s32 ids[8];
} PageTable;

typedef struct ScreenData {
    u16 width;
    u16 height;
    u16 colorMode;
    u16 format;
    u32 size;
    u16 raw[1];
} ScreenData;

typedef struct ScreenEntry {
    u8 pad_00[0x8];
    ScreenData *screen;
} ScreenEntry;

typedef struct PanelState {
    u8 pad_00[0x6];
    s8 page;
    s8 delay;
    u8 pad_08[0x304 - 0x8];
    u8 resources[1];
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern const PageTable data_ov013_02074ac4;
extern const PageTable data_ov013_02074aa4;
extern const PageTable data_ov013_02074ae4;
extern ScreenEntry *func_ov027_020b8578(void *owner, u16 entryId);
extern void GX_LoadBG1Scr(const void *src, u32 offset, u32 size);

void AnimatePanelPageScreens(void) {
    PageTable bodyIds = data_ov013_02074ac4;
    PageTable headerIds = data_ov013_02074aa4;
    PageTable nextPage = data_ov013_02074ae4;
    int i;
    ScreenEntry *entry;

    if (data_ov013_02074ce0->delay == 0) {
        data_ov013_02074ce0->page = nextPage.ids[data_ov013_02074ce0->page];
        entry = func_ov027_020b8578(data_ov013_02074ce0->resources, bodyIds.ids[data_ov013_02074ce0->page]);
        for (i = 0; i < 10; i++) {
            GX_LoadBG1Scr(&entry->screen->raw[i * 12], (i + 6) * 0x40, 0x18);
        }
        entry = func_ov027_020b8578(data_ov013_02074ce0->resources, headerIds.ids[data_ov013_02074ce0->page]);
        for (i = 0; i < 2; i++) {
            GX_LoadBG1Scr(&entry->screen->raw[i * 7], i * 0x40 + 0x1a, 0xe);
        }
        data_ov013_02074ce0->delay = 2;
    } else {
        data_ov013_02074ce0->delay--;
    }
}

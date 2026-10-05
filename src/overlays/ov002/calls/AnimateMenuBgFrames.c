#include "nitro/types.h"

typedef struct ScreenData {
    u8 pad_00[0xc];
    u16 rawData[1];
} ScreenData;

typedef struct BgEntry {
    u16 entryId;
    u16 pad_02;
    u32 unk_04;
    ScreenData *screen;
} BgEntry;

typedef struct FrameTable {
    s32 values[8];
} FrameTable;

typedef struct MenuContext {
    u8 pad_00[4];
    s8 frame;
    s8 delay;
    u8 pad_06[0x520 - 6];
    u8 bgContainer[0x4c];
} MenuContext;

extern MenuContext *data_ov002_0206c464;
extern const FrameTable data_ov002_0206ad3c;
extern const FrameTable data_ov002_0206ad1c;
extern const FrameTable data_ov002_0206ad5c;

extern BgEntry *func_ov027_020b8578(void *container, int entryId);
extern void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size);

void AnimateMenuBgFrames(void)
{
    FrameTable topEntries;
    FrameTable rowEntries;
    FrameTable nextFrames;
    int i;
    BgEntry *entry;

    topEntries = data_ov002_0206ad3c;
    rowEntries = data_ov002_0206ad1c;
    nextFrames = data_ov002_0206ad5c;
    if (data_ov002_0206c464->delay == 0) {
        data_ov002_0206c464->frame = nextFrames.values[data_ov002_0206c464->frame];
        entry = func_ov027_020b8578(data_ov002_0206c464->bgContainer, (u16)topEntries.values[data_ov002_0206c464->frame]);
        for (i = 0; i < 7; i++) {
            GXS_LoadBG1Scr(entry->screen->rawData + i * 12, (i + 0xd) * 0x40, 0x18);
        }
        entry = func_ov027_020b8578(data_ov002_0206c464->bgContainer, (u16)rowEntries.values[data_ov002_0206c464->frame]);
        for (i = 0; i < 2; i++) {
            GXS_LoadBG1Scr(entry->screen->rawData + i * 12, i * 0x40 + 0x28, 0x18);
        }
        data_ov002_0206c464->delay = 2;
    } else {
        data_ov002_0206c464->delay--;
    }
}

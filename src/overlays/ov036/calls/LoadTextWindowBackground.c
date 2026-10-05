#include "nitro/types.h"

typedef struct BgGraphicsData {
    void *screen;
    void *character;
    void *palette;
} BgGraphicsData;

typedef struct OverlayWork {
    u32 unk_00;
    u32 messageHandle;
    void *archive;
    BgGraphicsData background;
} OverlayWork;

#define REG_DISPCNT (*(vu32 *)0x04000000)

extern OverlayWork *gTextWindowResourceTable;
extern const char sOv036_UiEventuiEventuiP2f_020c38e4[];
extern u32 Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern void *Archive_LoadFile(u32 fileId, u32 mode);
extern void GetBgDataFromArchive(BgGraphicsData *out, void *archive, int screenIndex, int characterIndex,
                                          int paletteIndex);

void LoadTextWindowBackground(void)
{
    gTextWindowResourceTable->messageHandle = Msg_OpenContainerAndReadHeader(sOv036_UiEventuiEventuiP2f_020c38e4, 0xe, FALSE);
    gTextWindowResourceTable->archive =
        Archive_LoadFile((((gTextWindowResourceTable->messageHandle + 0x8000) & 0xfffffc) << 7) | 0x80000000, 0xe);
    GetBgDataFromArchive(&gTextWindowResourceTable->background, gTextWindowResourceTable->archive, 0, 0, 0);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
}

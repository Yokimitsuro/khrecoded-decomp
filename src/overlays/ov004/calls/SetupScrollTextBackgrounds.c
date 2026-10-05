#include "nitro/types.h"

#define REG_WININ      (*(volatile u16 *)0x04000048)
#define REG_WINOUT     (*(volatile u16 *)0x0400004a)
#define REG_WIN0H      (*(volatile u16 *)0x04000040)
#define REG_WIN0V      (*(volatile u16 *)0x04000044)
#define REG_DB_WININ   (*(volatile u16 *)0x04001048)
#define REG_DB_WINOUT  (*(volatile u16 *)0x0400104a)
#define REG_DB_WIN0H   (*(volatile u16 *)0x04001040)
#define REG_DB_WIN0V   (*(volatile u16 *)0x04001044)

#define SCROLL_FILE(work, index) ((((work)->archiveBase + 0x8000) & 0xfffffc) << 7 | 0x80000000 | (index))

typedef struct ScrollScreen {
    u32 activeChar;
    u32 charFile;
    u32 screenFile;
    u8 pad_0c[0x10940 - 0xc];
} ScrollScreen;

typedef struct ScrollTextWork {
    u8 pad_00[0xc];
    u32 archiveBase;
    void *paletteFile;
    ScrollScreen screens[2];
    u8 pad_21294[0x23294 - 0x21294];
    u16 tileMap[32 * 32];
} ScrollTextWork;

typedef struct ScrollTextGlobals {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

typedef struct PaletteData {
    u8 pad_00[0xc];
    void *data;
} PaletteData;

extern ScrollTextGlobals data_ov004_020645a0;

extern u32 func_0202c378(u32 fileId, u32 heap);
extern void *AllocAndRegisterOrFree_0202b540(PaletteData **out, u32 fileId, u32 heap);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int offset, void *data, int size);
extern void *G2_GetBG0CharPtr(void);
extern void *G2S_GetBG0CharPtr(void);
extern void *G2_GetBG0ScrPtr(void);
extern void *G2S_GetBG0ScrPtr(void);
extern void *G2_GetBG1CharPtr(void);
extern void *G2S_GetBG1CharPtr(void);
extern void *G2_GetBG1ScrPtr(void);
extern void *G2S_GetBG1ScrPtr(void);

static inline void SetWindowPlaneMask(volatile u16 *reg, int wnd, BOOL effect)
{
    u32 value = (*reg & ~0x3f) | (u32)wnd;

    if (effect) {
        value |= 0x20;
    }
    *reg = (u16)value;
}

static inline void SetWindow0Bounds(volatile u16 *horizontal, volatile u16 *vertical, int x1, int y1, int x2, int y2)
{
    *horizontal = (u16)(((x1 << 8) & 0xff00) | (x2 & 0xff));
    *vertical = (u16)((y1 << 8) | y2);
}

void SetupScrollTextBackgrounds(void)
{
    PaletteData *palette;
    int row;
    int col;
    u16 tile;

    data_ov004_020645a0.work->screens[0].charFile = func_0202c378(SCROLL_FILE(data_ov004_020645a0.work, 1), 0xe);
    data_ov004_020645a0.work->screens[1].charFile = func_0202c378(SCROLL_FILE(data_ov004_020645a0.work, 0), 0xe);
    data_ov004_020645a0.work->screens[0].screenFile = func_0202c378(SCROLL_FILE(data_ov004_020645a0.work, 2), 0xe);
    data_ov004_020645a0.work->screens[1].screenFile = func_0202c378(SCROLL_FILE(data_ov004_020645a0.work, 3), 0xe);
    data_ov004_020645a0.work->screens[0].activeChar = data_ov004_020645a0.work->screens[0].charFile;
    data_ov004_020645a0.work->screens[1].activeChar = data_ov004_020645a0.work->screens[1].charFile;

    MIi_CpuClearFast(0xffffffff, (u8 *)G2_GetBG0CharPtr() + 0x3000, 0x40);
    MIi_CpuClearFast(0xffffffff, (u8 *)G2S_GetBG0CharPtr() + 0x3000, 0x40);
    MIi_CpuClearFast(0xc000c0, G2_GetBG0ScrPtr(), 0x600);
    MIi_CpuClearFast(0xc000c0, G2S_GetBG0ScrPtr(), 0x600);

    row = 0;
    MIi_CpuClearFast(0, data_ov004_020645a0.work->tileMap, 0x800);
    tile = 0;
    for (; row < 32; row++) {
        for (col = 0; col < 32; col++) {
            data_ov004_020645a0.work->tileMap[row * 32 + col] = tile;
            tile++;
        }
    }

    data_ov004_020645a0.work->paletteFile =
        AllocAndRegisterOrFree_0202b540(&palette, SCROLL_FILE(data_ov004_020645a0.work, 4), 0xe);
    NNS_GfdRegisterNewVramTransferTask(0x11, 0, palette->data, 0x200);
    NNS_GfdRegisterNewVramTransferTask(0x21, 0, palette->data, 0x200);
    NNS_GfdRegisterNewVramTransferTask(0xf, 0, palette->data, 0x200);
    NNS_GfdRegisterNewVramTransferTask(0x1f, 0, palette->data, 0x200);

    MIi_CpuClearFast(0, G2_GetBG1CharPtr(), 0xc000);
    MIi_CpuClearFast(0, G2S_GetBG1CharPtr(), 0xc000);
    MIi_CpuClearFast(0, G2_GetBG1ScrPtr(), 0x800);
    MIi_CpuClearFast(0, G2S_GetBG1ScrPtr(), 0x800);

    SetWindowPlaneMask(&REG_WININ, 0x1f, TRUE);
    SetWindowPlaneMask(&REG_WINOUT, 0x13, TRUE);
    SetWindow0Bounds(&REG_WIN0H, &REG_WIN0V, 0, 0, 0x46, 0xc0);
    SetWindowPlaneMask(&REG_DB_WININ, 0x1f, TRUE);
    SetWindowPlaneMask(&REG_DB_WINOUT, 0x13, TRUE);
    SetWindow0Bounds(&REG_DB_WIN0H, &REG_DB_WIN0V, 0, 0, 0x46, 0xc0);
}






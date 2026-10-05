#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x39];
    u8 page;
    u8 swapped;
    u8 mainScreen;
    u8 pad_3C[0xc];
    int swapCount;
} CaptionStream;

typedef struct {
    u32 unk_00;
    u32 unk_04;
    CaptionStream *captions;
} MovieGlobals;

typedef struct {
    u8 pad_00[0x54];
    void (*onSwap)(void);
} MovieFileBank;

extern MovieGlobals data_ov022_020b7da8;
extern MovieFileBank data_ov022_020b7db4;

#define REG_VCOUNT (*(vu16 *)0x04000006)
#define REG_DISPCNT (*(vu32 *)0x04000000)
#define REG_DISPCNT_SUB (*(vu32 *)0x04001000)

void SwapCaptionPagesOnVBlank(void) {
    CaptionStream *captions;
    u16 line = REG_VCOUNT;

    if (line < 0xa0 || line >= 0x104) {
        return;
    }
    captions = data_ov022_020b7da8.captions;
    if (captions->mainScreen && !captions->swapped) {
        if (captions->page == 0) {
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0xf00;
        } else {
            REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1700;
        }
        captions->page ^= 1;
        captions->swapped = 1;
        captions->swapCount++;
    }
    if (!captions->mainScreen && !captions->swapped) {
        if (captions->page == 0) {
            REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0xf00;
        } else {
            REG_DISPCNT_SUB = (REG_DISPCNT_SUB & ~0x1f00) | 0x1700;
        }
        captions->page ^= 1;
        captions->swapped = 1;
        captions->swapCount++;
    }
    if (data_ov022_020b7db4.onSwap != NULL) {
        data_ov022_020b7db4.onSwap();
    }
}

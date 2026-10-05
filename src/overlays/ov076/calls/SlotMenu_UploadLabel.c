#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x11ee8];
    s16 cursorSlot;
    u8 pad_11EEA[0x491f8 - 0x11eea];
    u16 labelMaps[24][2][0x20];
} SlotMenu;

extern int NNS_GfdRegisterNewVramTransferTask(void *dest, int offset, void *src, int size);
extern void NNS_G2dMapScrToCharText(u16 *dst, int width, int height, int x, int y, int mapW, int tile, int palette);

void SlotMenu_UploadLabel(SlotMenu *menu, int slot, int part, u8 *buffer)
{
    int offset = slot - menu->cursorSlot;
    int tile = (part + (offset + 1) * 3) * 0x1e + 0x100;
    int index;
    int column;
    int row;

    NNS_GfdRegisterNewVramTransferTask((void *)6, tile * 0x40, buffer, 0x780);
    index = part + offset * 3;
    column = 10;
    if (part != 2) {
        column = 8;
    }
    row = slot * 8 + 1 + part * 2;
    NNS_G2dMapScrToCharText(menu->labelMaps[index][0], 0xf, 2, 0, 0, 0x20, tile, 0);
    NNS_GfdRegisterNewVramTransferTask((void *)10, (column + row * 0x20) * 2, menu->labelMaps[index][0], 0x1e);
    NNS_GfdRegisterNewVramTransferTask((void *)10, (column + (row + 1) * 0x20) * 2, menu->labelMaps[index][1], 0x1e);
}

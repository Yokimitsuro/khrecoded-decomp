#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MapIconOffset {
    u8 x;
    u8 y;
    s8 shiftX;
    s8 shiftY;
} MapIconOffset;

typedef struct InputStatus {
    u8 pad_00[8];
    u16 held;
} InputStatus;

typedef struct MatrixMenu {
    u8 pad_00000[7];
    u8 textDirty;
    u8 redraw;
    u8 pad_00009[0x1f];
    s16 cursorX;
    s16 cursorY;
    u8 pad_0002c[8];
    fx32 posX;
    fx32 posY;
    u8 pad_0003c[0x14];
    s32 velocityX;
    s32 velocityY;
    u8 pad_00058[8];
    s32 scroll;
    u8 pad_00064[0xc];
    s32 mapOpen;
    s32 transitionBusy;
    s32 active;
    u8 pad_0007c[0xc];
    s32 pickerOpen;
    u8 pad_0008c[0x4ee0 - 0x8c];
    u8 messages[0x11fac - 0x4ee0];
    const u16 *caption;
    u8 pad_11fb0[0x12dc8 - 0x11fb0];
    s32 dialogBusy;
    u8 pad_12dcc[8];
    u8 *currentNode;
    u8 pad_12dd8[0x131a4 - 0x12dd8];
    void *entryPanel;
    u8 pad_131a8[0x13e64 - 0x131a8];
    u16 pendingUnlocks;
    u8 pad_13e66[0x13ea0 - 0x13e66];
    s32 noticeBusy;
    u8 pad_13ea4[0x13ecc - 0x13ea4];
    int entryHandle;
    u8 pad_13ed0[0x13ee0 - 0x13ed0];
    u8 mapScreen[0x3600];
    u8 pad_174e0[0x174ec - 0x174e0];
    fx32 savedX;
    fx32 savedY;
    u8 pad_174f4[0x17524 - 0x174f4];
    s32 rewardBusy;
} MatrixMenu;

extern const MapIconOffset data_ov075_020d1474[];

extern s32 GetDialogInputMode(MatrixMenu *menu);
extern InputStatus *func_ov039_020bca20(void);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern u16 *UpdateScreenWidgetLayer(int layer);
extern void MIi_CpuClearFast(u32 data, void *dest, u32 size);
extern void SetScreenLayerDirty(int layer);
extern int NNS_GfdRegisterNewVramTransferTask(int command, int offset, void *data, int size);
extern void SetEntrySlotsVisible(void *panel, int handle, int visible);
extern const u16 *func_ov027_020ba2c8(void *messages, int index);
extern void SetSecondaryElementEnabled(int enabled);
extern void ShowEntryHeaderMessage(MatrixMenu *menu, u8 *node);

static inline int GetVisiblePlane(void)
{
    return (*(vu32 *)0x04000000 & 0x1f00) >> 8;
}

static inline void SetVisiblePlane(int plane)
{
    *(vu32 *)0x04000000 = (*(vu32 *)0x04000000 & ~0x1f00) | (plane << 8);
}

void ToggleMatrixMapView(MatrixMenu *menu)
{
    u16 *screen;
    u16 row;
    u16 col;
    u16 tile;
    int kind;
    int index;
    fx32 value;
    const MapIconOffset *entry;

    if (menu->active == 0 || menu->dialogBusy != 0 || menu->transitionBusy != 0
        || menu->rewardBusy != 0 || menu->pickerOpen != 0 || menu->noticeBusy != 0
        || menu->pendingUnlocks != 0 || GetDialogInputMode(menu) != 0) {
        return;
    }
    if (func_ov039_020bca20()->held & 3) {
        return;
    }

    if (menu->mapOpen == 0) {
        PlaySoundEffect(1, 2);
        screen = UpdateScreenWidgetLayer(9);
        menu->mapOpen = 1;
        menu->redraw = 1;
        *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x14;
        SetVisiblePlane(GetVisiblePlane() | 2);
        MIi_CpuClearFast(0, screen, 0x600);
        screen += 100;
        tile = 0xd000;
        for (row = 18; row != 0; row--) {
            for (col = 24; col != 0; col--) {
                *screen++ = ++tile;
            }
            screen += 8;
        }
        kind = menu->currentNode[2];
        if (kind < 3 || kind >= 14) {
            index = 0;
        } else {
            index = kind - 2;
        }
        entry = &data_ov075_020d1474[index];
        value = (menu->cursorX << 16) + (entry->x << 11)
              - (entry->shiftX << 12);
        menu->savedX = value;
        menu->posX = value;
        value = (menu->cursorY << 16) + (entry->y << 11)
              - (entry->shiftY << 12) - 0x8000;
        menu->savedY = value;
        menu->posY = value;
        SetScreenLayerDirty(9);
        NNS_GfdRegisterNewVramTransferTask(5, 0x20, menu->mapScreen, 0x3600);
        SetEntrySlotsVisible(menu->entryPanel, menu->entryHandle, 1);
        menu->caption = func_ov027_020ba2c8(menu->messages, 100);
        menu->textDirty = 1;
        SetSecondaryElementEnabled(1);
        ShowEntryHeaderMessage(menu, menu->currentNode);
        return;
    }

    PlaySoundEffect(1, 3);
    screen = UpdateScreenWidgetLayer(9);
    menu->mapOpen = 0;
    menu->redraw = 1;
    menu->posX = menu->savedX;
    menu->posY = menu->savedY;
    menu->scroll = 0;
    menu->velocityY = 0;
    menu->velocityX = 0;
    *(vu16 *)0x0400000a = (*(vu16 *)0x0400000a & 0x43) | 0x94;
    SetVisiblePlane(GetVisiblePlane() & ~2);
    MIi_CpuClearFast(0, screen, 0x600);
    SetScreenLayerDirty(9);
    SetEntrySlotsVisible(menu->entryPanel, menu->entryHandle, 0);
    menu->caption = func_ov027_020ba2c8(menu->messages, 0x58);
    menu->textDirty = 1;
}

#include "nitro/types.h"

typedef struct DispatchEntry {
    void (*action)(void);
    u8 pad_04[0xc];
} DispatchEntry;

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 disabled : 1;
    u8 dispatchReady : 1;
    u8 slotAEnabled : 1;
    u8 slotBEnabled : 1;
    u8 slotCEnabled : 1;
    u8 slotDEnabled : 1;
    u8 slotATriggered : 1;
    u8 slotBTriggered : 1;
    u8 slotCTriggered : 1;
    u8 slotDTriggered : 1;
    u8 unk_11_2 : 1;
    u8 busy : 1;
    u8 unk_11_4 : 1;
    u8 unk_11_5 : 1;
    u8 unk_11_6 : 1;
    u8 unk_11_7 : 1;
} PanelState;

extern PanelState *data_ov002_0206c460;
extern DispatchEntry gPanelModeExitCallback[];
extern u16 data_02060500;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int OS_GetCpsrIrq(void);
extern void func_020273e8(void);
extern int FS_UnloadOverlayImage_0204f5f0(void *p);
extern void Text_UploadTileBuffer(void *p);

int UpdatePanelState(void) {
    void *rootHeap = NNSi_FndGetCurrentRootHeap();
    int alreadyActive = OS_GetCpsrIrq();

    if (alreadyActive == 0) {
        func_020273e8();
    }
    FS_UnloadOverlayImage_0204f5f0((u8 *)rootHeap + 0x12);

    *(u16 *)((u8 *)rootHeap + 0x12) &= 0xf3fc;
    if ((data_02060500 & 1) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 1;
    }
    if ((data_02060500 & 2) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 2;
    }
    if ((data_02060500 & 0x400) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 0x400;
    }
    if ((data_02060500 & 0x800) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 0x800;
    }

    gPanelModeExitCallback[*(s32 *)((u8 *)rootHeap + 8)].action();

    if (data_ov002_0206c460->disabled) {
        return -2;
    }
    if (data_ov002_0206c460->slotAEnabled && data_ov002_0206c460->slotATriggered) {
        Text_UploadTileBuffer((u8 *)data_ov002_0206c460 + 0x48);
    }
    if (data_ov002_0206c460->slotBEnabled && data_ov002_0206c460->slotBTriggered) {
        Text_UploadTileBuffer((u8 *)data_ov002_0206c460 + 0x7c);
    }
    if (data_ov002_0206c460->slotCEnabled && data_ov002_0206c460->slotCTriggered) {
        Text_UploadTileBuffer((u8 *)data_ov002_0206c460 + 0xb0);
    }
    if (data_ov002_0206c460->slotDEnabled && data_ov002_0206c460->slotDTriggered) {
        Text_UploadTileBuffer((u8 *)data_ov002_0206c460 + 0xe4);
    }
    data_ov002_0206c460->slotATriggered = 0;
    data_ov002_0206c460->slotBTriggered = 0;
    data_ov002_0206c460->slotCTriggered = 0;
    data_ov002_0206c460->slotDTriggered = 0;
    return 0;
}

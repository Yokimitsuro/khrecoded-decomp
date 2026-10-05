#include "nitro/types.h"

typedef struct ManagerDesc {
    u32 key;
    u32 word1;
    u32 word2;
    u32 word3;
} ManagerDesc;

typedef struct PointPair {
    int x;
    int y;
} PointPair;

typedef struct MarkerSlot {
    int handle;
    int value;
} MarkerSlot;

typedef struct MapScreen {
    char pad00[0xc];
    int vramBase;
    char pad10[0x40 - 0x10];
    int state;
    char pad44[0x58 - 0x44];
    char manager[0x648c - 0x58];
    int handles[6];
    MarkerSlot markers[121];
} MapScreen;

extern ManagerDesc data_ov023_020b6eb4;
extern PointPair data_ov023_020b6ea4;
extern char PlayEnabledMenuSound[];

extern void InitObjManagerVariant(void *manager, ManagerDesc *desc);
extern void PXI_Init_0204f020(void *manager, u32 key);
extern int PXI_Init_0204f0c8(void *manager, int type, int flag);
extern void IndexedRecord_SetPair(void *manager, int handle, PointPair *pos);
extern void func_0204f18c(void *manager, int handle, int value);
extern void IndexedRecords_SetFlag2(void *manager, int handle, int value);
extern void IndexedRecords_SetFlag3(void *manager, int handle, int value);
extern void set_engine_alpha_blend(void *manager, int alpha);
extern void Slot_SetMode2Bit(void *manager, int handle, int mode);
extern void SetBank6Word1C(void *manager, int value);
extern void SetupSlotEntry(void *manager, int handle, void *callback, int arg, int mode);
extern void MIi_CpuClear32(int value, void *dest, int size);
extern u32 MakePrimaryVramKey_02071214(int slot);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern BOOL func_ov001_020645c8(int flag);
extern int ReadSessionPackedBits(int offset, int bits);
extern void SelectMenuPalette(MapScreen *screen, int palette);

void InitMapScreen(MapScreen *screen)
{
    ManagerDesc desc = data_ov023_020b6eb4;
    PointPair pos = data_ov023_020b6ea4;
    int i;

    desc.key = ((screen->vramBase + 0x8000) & 0xfffffc) << 7 | 0x80000000;
    InitObjManagerVariant(screen->manager, &desc);
    PXI_Init_0204f020(screen->manager, MakePrimaryVramKey_02071214(10));
    screen->handles[0] = PXI_Init_0204f0c8(screen->manager, 0, 0);
    screen->handles[1] = PXI_Init_0204f0c8(screen->manager, 2, 0);
    screen->handles[2] = PXI_Init_0204f0c8(screen->manager, 4, 0);
    screen->handles[3] = PXI_Init_0204f0c8(screen->manager, 4, 0);
    screen->handles[4] = PXI_Init_0204f0c8(screen->manager, 0x1c, 0);
    screen->handles[5] = PXI_Init_0204f0c8(screen->manager, 1, 1);
    IndexedRecord_SetPair(screen->manager, screen->handles[0], &pos);
    IndexedRecord_SetPair(screen->manager, screen->handles[1], &pos);
    IndexedRecord_SetPair(screen->manager, screen->handles[4], &pos);
    pos.x = 0xc0000;
    pos.y = 0x96000;
    IndexedRecord_SetPair(screen->manager, screen->handles[5], &pos);
    Slot_SetMode2Bit(screen->manager, screen->handles[0], 3);
    Slot_SetMode2Bit(screen->manager, screen->handles[1], 3);
    Slot_SetMode2Bit(screen->manager, screen->handles[2], 3);
    Slot_SetMode2Bit(screen->manager, screen->handles[3], 3);
    Slot_SetMode2Bit(screen->manager, screen->handles[4], 3);
    Slot_SetMode2Bit(screen->manager, screen->handles[5], 0);
    func_0204f18c(screen->manager, screen->handles[0], 1);
    func_0204f18c(screen->manager, screen->handles[1], 1);
    func_0204f18c(screen->manager, screen->handles[2], 1);
    func_0204f18c(screen->manager, screen->handles[3], 1);
    func_0204f18c(screen->manager, screen->handles[4], 0);
    func_0204f18c(screen->manager, screen->handles[5], 0);
    IndexedRecords_SetFlag2(screen->manager, screen->handles[4], 0);
    IndexedRecords_SetFlag2(screen->manager, screen->handles[5], 0);
    if (IsFieldFlag13OrSessionFlagSet()) {
        if (!func_ov001_020645c8(0x360a)) {
            IndexedRecords_SetFlag2(screen->manager, screen->handles[3], 0);
        }
        if (!func_ov001_020645c8(0x3609)) {
            IndexedRecords_SetFlag2(screen->manager, screen->handles[2], 0);
        }
    } else {
        IndexedRecords_SetFlag2(screen->manager, screen->handles[2], 0);
        IndexedRecords_SetFlag2(screen->manager, screen->handles[3], 0);
    }
    IndexedRecords_SetFlag3(screen->manager, screen->handles[4], 1);
    SetBank6Word1C(screen->manager, 1);
    screen->state = 0;
    SetupSlotEntry(screen->manager, screen->handles[4], PlayEnabledMenuSound, 0, 2);
    MIi_CpuClear32(-1, screen->markers, sizeof(screen->markers));
    SelectMenuPalette(screen, ReadSessionPackedBits(0x1a0f, 3));
    for (i = 0; i < 121; i++) {
        screen->markers[i].handle = PXI_Init_0204f0c8(screen->manager, 0, 0);
        screen->markers[i].value = 0;
        Slot_SetMode2Bit(screen->manager, screen->markers[i].handle, 3);
    }
    set_engine_alpha_blend(screen->manager, 8);
}

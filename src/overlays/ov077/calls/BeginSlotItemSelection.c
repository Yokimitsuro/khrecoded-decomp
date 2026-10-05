#include "nitro/types.h"

#define REG_DISPCNT (*(volatile u32 *)0x04000000)
#define REG_BG1CNT (*(volatile u16 *)0x0400000a)
#define REG_WININ (*(volatile u16 *)0x04000048)

typedef struct {
    u8 pad_0000[0x2db4];
    u16 slotRecords[1];
} SaveData;

typedef struct {
    u8 pad_00000[0xc];
    u32 pending;
    u8 pad_00010[4];
    u8 view[4];
    u32 busy;
    u8 pad_0001c[0x7fa8 - 0x1c];
    s32 selectedRecord;
    s16 selectedIndex;
    u8 pad_07fae[2];
    s32 state;
    u8 pad_07fb4[0x11ff8 - 0x7fb4];
    s32 slot;
} MenuWork;

extern SaveData *data_0205fe0c;
extern BOOL func_ov077_020c5c3c(MenuWork *work);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern void func_ov077_020c9138(void *view, int mode);

static inline void G2_SetWnd1InsidePlane(int wnd, BOOL effect)
{
    u32 value = (REG_WININ & ~0x3f00) | (wnd << 8);
    if (effect) {
        value |= 0x20 << 8;
    }
    REG_WININ = (u16)value;
}

void BeginSlotItemSelection(MenuWork *work)
{
    int slot;
    int mode;
    u32 record;

    if (work->busy != 0) {
        return;
    }
    if (work->state != 4) {
        return;
    }
    if (func_ov077_020c5c3c(work)) {
        work->pending = 1;
        PlaySoundEffect(1, 1);
        return;
    }
    REG_BG1CNT = (u16)((REG_BG1CNT & 0x43) | 0x10);
    slot = work->slot;
    if (slot == 0) {
        mode = 3;
        record = data_0205fe0c->slotRecords[0];
    } else if (slot == 1) {
        mode = 5;
        record = data_0205fe0c->slotRecords[1];
    } else {
        mode = 4;
        record = data_0205fe0c->slotRecords[slot];
    }
    if (record == 0xffff) {
        record = (u32)-1;
    }
    work->selectedRecord = record;
    work->selectedIndex = -1;
    G2_SetWnd1InsidePlane(0x18, TRUE);
    func_ov077_020c9138(work->view, mode);
    REG_DISPCNT = (REG_DISPCNT & ~0x1f00) | 0x1f00;
}

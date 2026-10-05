#include "nitro/types.h"

typedef struct MenuEntry {
    u8 pad_00[0x10];
    BOOL highlighted;
    u8 pad_14[0x4];
} MenuEntry;

typedef struct MenuGauge {
    u16 max;
    u16 value;
    u16 pad_04;
} MenuGauge;

typedef struct GaugeMenu {
    u8 pad_00[0x34];
    BOOL empty[0xe];
    MenuEntry entries[3];
    MenuGauge gauges[3];
} GaugeMenu;

typedef struct SessionStateFlags {
    u8 unk_0 : 4;
    u8 bit4 : 1;
    u8 unk_5 : 3;
} SessionStateFlags;

typedef struct Session {
    u8 pad_0000[0x27b6];
    SessionStateFlags stateFlags;
} Session;

extern Session *data_ov001_020a0480;
extern BOOL func_ov001_020645c8(u32 value);
extern void func_ov001_020716e8(int index, int mode);
extern void UploadScreenSlotBlock(int index, int mode);
extern void SetMenuGaugeActive(int index, BOOL enable);

void RefreshMenuGaugeState(GaugeMenu *menu, int index, BOOL force)
{
    MenuEntry *entry = &menu->entries[index];
    MenuGauge *gauge = &menu->gauges[index];
    int threshold = gauge->max * 25 / 100;
    BOOL locked;

    if (gauge->value == 0) {
        if (index == 0 && (func_ov001_020645c8(0x3525) || data_ov001_020a0480->stateFlags.bit4)) {
            locked = TRUE;
        } else {
            locked = FALSE;
        }
        if (!locked) {
            func_ov001_020716e8(index, 2);
            SetMenuGaugeActive(index, FALSE);
        }
        UploadScreenSlotBlock(index, 2);
        menu->empty[index] = TRUE;
        return;
    }
    if (menu->empty[index]) {
        func_ov001_020716e8(index, 0);
        if (index == 0 && menu->entries[0].highlighted) {
            UploadScreenSlotBlock(index, 2);
        } else {
            UploadScreenSlotBlock(index, 0);
        }
        menu->empty[index] = FALSE;
    }
    if (gauge->value > threshold) {
        if (force || entry->highlighted) {
            SetMenuGaugeActive(index, FALSE);
        }
    } else if (force || !entry->highlighted) {
        SetMenuGaugeActive(index, TRUE);
    }
}

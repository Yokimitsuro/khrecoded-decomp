#include "nitro/types.h"

typedef struct AreaMusicEntry {
    int flagValue;
    int overlayId;
} AreaMusicEntry;

typedef struct AreaMusicTable {
    AreaMusicEntry entries[9];
} AreaMusicTable;

typedef struct FieldState {
    u8 pad_00[0x10];
    int overlayId;
    u8 pad_14[4];
    u8 areaIndex;
} FieldState;

extern const AreaMusicTable data_ov001_0209d8f8;
extern FieldState *data_ov001_020a0480;
extern void StoreGlobalArrayEntry(int index, int value);
extern void func_02029f8c(int processor, int overlayId);

void ApplyAreaSoundEntry(int index)
{
    AreaMusicTable table = data_ov001_0209d8f8;

    if (table.entries[index].flagValue != 0) {
        StoreGlobalArrayEntry(7, table.entries[index].flagValue);
    }
    if (table.entries[index].overlayId != -1) {
        data_ov001_020a0480->overlayId = table.entries[index].overlayId;
        func_02029f8c(0, data_ov001_020a0480->overlayId);
    }
    data_ov001_020a0480->areaIndex = index;
}


#include "nitro/types.h"

typedef struct PlayerSlot {
    u8 data[0x30];
} PlayerSlot;

typedef struct PlayerRecords {
    u8 data[0x144];
} PlayerRecords;

extern u8 data_020608c8;
extern PlayerSlot data_020609c0[];
extern PlayerRecords data_02060b50[];
extern void MI_CpuFill8(void *dst, int value, int size);
extern void ResetSlotEntries(void);
extern void LoadLevelTable(void);
extern void ResetParamWord8(void);

void InitPlayerData(void)
{
    int i;

    data_020608c8 = 1;
    for (i = 0; i < 3; i++) {
        MI_CpuFill8(&data_020609c0[i], 0, sizeof(PlayerSlot));
        MI_CpuFill8(&data_02060b50[i], 0, sizeof(PlayerRecords));
    }
    ResetSlotEntries();
    LoadLevelTable();
    ResetParamWord8();
}

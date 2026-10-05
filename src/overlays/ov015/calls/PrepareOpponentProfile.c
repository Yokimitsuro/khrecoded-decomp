#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u8 profile[0x70];
    u8 slotIndex;
    u8 unk_79_0 : 5;
    u8 pending : 1;
    u8 ready : 1;
    u8 unk_79_7 : 1;
    u8 mode : 2;
    u8 unk_7a_2 : 6;
    u8 pad_7b[5];
    u32 slots[4];
} OpponentState;

extern OpponentState *data_ov015_0207e964;
extern unsigned int func_0202a9e4(u16 range);
extern BOOL IsPlayerCardValid(void *card);
extern void InitPanelRecordFromProfile(void *profile, int value);
extern void GenerateRandomProfile(void *profile, BOOL fillSlots);
extern void InvokePanelCallback(void *profile);

void PrepareOpponentProfile(void)
{
    if (data_ov015_0207e964->pending != 1 || data_ov015_0207e964->ready != 1) {
        return;
    }
    switch (data_ov015_0207e964->mode) {
    case 0:
        if (IsPlayerCardValid(data_ov015_0207e964->profile)) {
            InvokePanelCallback(data_ov015_0207e964->profile);
            break;
        }
        data_ov015_0207e964->slots[data_ov015_0207e964->slotIndex] = 0;
        break;
    case 1:
        if (func_0202a9e4(100) < 25) {
            InitPanelRecordFromProfile(data_ov015_0207e964->profile, 0);
        } else {
            GenerateRandomProfile(data_ov015_0207e964->profile, FALSE);
        }
        InvokePanelCallback(data_ov015_0207e964->profile);
        break;
    case 2:
        InitPanelRecordFromProfile(data_ov015_0207e964->profile, 0);
        InvokePanelCallback(data_ov015_0207e964->profile);
        break;
    case 3:
        if (func_0202a9e4(100) < 25) {
            InitPanelRecordFromProfile(data_ov015_0207e964->profile, 1);
        } else {
            GenerateRandomProfile(data_ov015_0207e964->profile, TRUE);
        }
        InvokePanelCallback(data_ov015_0207e964->profile);
        break;
    }
    data_ov015_0207e964->pending = 0;
    data_ov015_0207e964->ready = 0;
}

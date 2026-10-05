#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    s32 slotIndex;
    s32 usedSlotCount;
    u8 pad_50[0x6688 - 0x50];
    BOOL progressFlag;
    u8 pad_668c[0x66c4 - 0x668c];
    u32 unlockFlagA;
    u32 unlockFlagB;
    u8 pad_66cc[0x66e8 - 0x66cc];
    BOOL loadFailed;
} Panel;

extern int PollCardThreadResult(void);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void ClearGlobalPackedBit(int bitIndex);
extern void StartCardWriteFromSlot(int slot);
extern void SetPanelState(Panel *panel, s32 state, u32 param1, u32 param2);

s32 ScanSaveSlots(Panel *panel)
{
    s32 result = -1;

    switch (PollCardThreadResult()) {
    case 3:
        panel->loadFailed = TRUE;
        SetPanelState(panel, 1, 0, 0);
        result = 0xe;
        break;
    case 0:
        if (IsGlobalPackedBitSet(0xbea)) {
            panel->progressFlag = TRUE;
        }
        panel->unlockFlagA |= (u8)(IsGlobalPackedBitSet(0xf4c) != 0);
        panel->unlockFlagB |= (u8)(IsGlobalPackedBitSet(0xf4d) != 0);
    case 4:
        panel->usedSlotCount++;
    case 2:
        if (++panel->slotIndex < 2) {
            StartCardWriteFromSlot(panel->slotIndex);
            break;
        }
        SetPanelState(panel, 0, 0, 30);
        result = 6;
        if (panel->unlockFlagA) {
            SetGlobalPackedBit(0x1150);
        } else {
            ClearGlobalPackedBit(0x1150);
            ClearGlobalPackedBit(0xf4c);
        }
        if (panel->unlockFlagB) {
            SetGlobalPackedBit(0x1151);
        } else {
            ClearGlobalPackedBit(0x1151);
            ClearGlobalPackedBit(0xf4d);
        }
        if (panel->progressFlag) {
            SetGlobalPackedBit(0xbea);
        } else {
            ClearGlobalPackedBit(0xbea);
        }
        break;
    }
    return result;
}

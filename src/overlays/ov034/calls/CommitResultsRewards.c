#include "nitro/types.h"

typedef struct ResultsParams {
    s32 earnedAmount;
    u8 pad_04[0x1e];
    u8 worldId;
    u8 pad_23;
    u8 unlockedRank;
    u8 pad_25[0xc];
    s8 slotLevels[0x24];
    s8 slotIndex;
    u8 pad_56[0x19];
    u8 committed;
} ResultsParams;

typedef struct ResultsScreen {
    ResultsParams *params;
    void *work;
} ResultsScreen;

extern ResultsScreen data_ov034_020c0fa0;
extern void func_ov001_02063b80(void);
extern void func_ov001_020876f4(void);
extern void func_ov001_0206459c(int bitOffset, u32 bitCount, u32 value);
extern void func_ov001_02086e18(void);
extern void func_ov001_02063a80(int index, int amount);
extern void func_ov001_02063130(int level, int flag);
extern void func_ov001_02064dc8(void);

void CommitResultsRewards(void)
{
    func_ov001_02063b80();
    func_ov001_020876f4();
    func_ov001_0206459c(0x3880, 0x660, 0);
    func_ov001_02086e18();
    func_ov001_02063a80(1, data_ov034_020c0fa0.params->earnedAmount);
    func_ov001_02063130(data_ov034_020c0fa0.params->slotLevels[data_ov034_020c0fa0.params->slotIndex] + 1, 1);
    data_ov034_020c0fa0.params->committed = 1;
    func_ov001_02064dc8();
    if (data_ov034_020c0fa0.params->worldId == 0x15 && data_ov034_020c0fa0.params->unlockedRank == 0xd) {
        func_ov001_0206459c(0x380c, 1, 1);
    }
}

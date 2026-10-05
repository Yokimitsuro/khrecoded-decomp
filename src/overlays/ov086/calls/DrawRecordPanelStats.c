#include "nitro/types.h"

typedef struct {
    int values[8];
} InitialValueTable;

typedef struct {
    u8 pad0[0xc];
    u8 handler[0x128];
    int group;
    u8 pad138[0x3c];
    u8 tileTable[4];
} RecordPanel;

extern const InitialValueTable data_ov086_020c220c;
extern int data_ov086_020c2168[];
extern int data_ov086_020c217c[];
extern u32 data_ov086_020c219c[];
extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void SetScreenLayerDirty(int layerId);
extern void func_ov027_020b9e20(void *table, int id);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 flagId);
extern int func_ov086_020bf2b0(int group);
extern int CountUnlockedGroupEntries(int group);
extern int func_ov086_020bf3b4(int group);
extern int CountGroupFlaggedEntries_020bf4a4(int group);
extern int SumUnlockedGroupEntryCounts(int group);
extern int GetHighestSetFlagTier(int group);
extern void func_ov086_020bee2c();

void DrawRecordPanelStats(RecordPanel *panel)
{
    InitialValueTable table = data_ov086_020c220c;
    int group;
    int first;
    int second;

    CallVirtualHandlerSlot1(panel->handler, 0);
    SetScreenLayerDirty(0x18);
    func_ov027_020b9e20(panel->tileTable, 0x19);
    group = panel->group;
    func_ov086_020bee2c(panel, 0, func_ov086_020bf2b0(group), table.values[group]);
    group = panel->group;
    if (group < 5) {
        func_ov086_020bee2c(panel, 1, ReadSessionPackedBits(data_ov086_020c2168[group], 2), 3);
    } else {
        func_ov086_020bee2c(panel, 6, group);
    }
    first = CountUnlockedGroupEntries(panel->group);
    func_ov086_020bee2c(panel, 2, first, func_ov086_020bf3b4(panel->group));
    first = CountGroupFlaggedEntries_020bf4a4(panel->group);
    func_ov086_020bee2c(panel, 3, first, SumUnlockedGroupEntryCounts(panel->group));
    func_ov086_020bee2c(panel, 4, GetHighestSetFlagTier(panel->group));
    first = ReadSessionPackedBits(data_ov086_020c217c[panel->group], 7);
    second = func_ov001_020645c8(data_ov086_020c219c[panel->group]);
    func_ov086_020bee2c(panel, 5, first + 1, second);
}

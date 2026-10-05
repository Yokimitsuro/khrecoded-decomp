#include "nitro/types.h"

typedef struct OverlaySelectionRecord OverlaySelectionRecord;
typedef struct GameState GameState;

extern GameState *data_0205fe0c;

extern void AcquireMapLayout(int reload, int discardCached);
extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);
extern void ComputePlayerStats(GameState *state, OverlaySelectionRecord *record, int param3, int param4);
extern void func_02050a58(void);
extern void ApplySelectionStatScaling(u32 selectionIndex, int kind);
extern void PackSelectionRecordEntry(u32 selectionIndex, int nameId, int entryIndex);

void SetupAllSelectionRecords(void)
{
    AcquireMapLayout(0, 0);
    ComputePlayerStats(data_0205fe0c, GetOverlaySelectionRecord(0), 1, 1);
    func_02050a58();
    ApplySelectionStatScaling(1, 2);
    PackSelectionRecordEntry(1, 2, 0);
    ApplySelectionStatScaling(2, 1);
    PackSelectionRecordEntry(2, 1, 0);
}
